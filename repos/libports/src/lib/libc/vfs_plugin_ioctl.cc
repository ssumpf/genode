/*
 * \brief  Libc plugin for using a process-local virtual file system
 * \author Josef Soentgen
 * \date   2018-10-25
 */

/*
 * Copyright (C) 2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <base/env.h>
#include <base/log.h>
#include <file_system/util.h>
#include <vfs/dir_file_system.h>

/* libc includes */
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/disk.h>
#include <sys/soundcard.h>
#include <dlfcn.h>

/* libc plugin interface */
#include <libc-plugin/plugin.h>
#include <vfs_plugin.h>

/* libc-internal includes */
#include "libc_mem_alloc.h"
#include "libc_errno.h"
#include "task.h"


#define VFS_THREAD_SAFE(code) ({ \
	Genode::Lock::Guard g(Libc::vfs_lock()); \
	code; \
})


namespace Util {
	using Ioctl_path = Genode::String<256>;

	inline bool dirname(char const *path, char *dst, size_t len)
	{
		char const *start = File_system::basename(path) - 1;
		size_t const l = (size_t)start - (size_t)path; //XXX UB
		if (l >= len) { return false; }

		Genode::memcpy(dst, path, l);
		dst[len] = 0;
		return true;
	}

	Ioctl_path construct_ioctl_path(char const *path)
	{
		if (!path) { return Ioctl_path(); }

		char dir[128];
		char const *base = File_system::basename(path);
		if (!Util::dirname(path, dir, sizeof (dir))) {
			return Ioctl_path();
		}
		return Ioctl_path((char const*)dir, "/.", base);
	}

	bool read_file(Genode::Allocator &alloc, Vfs::File_system &root,
	               char const *path, char *buf, size_t buf_len)
	{
		Vfs::Vfs_handle *handle = 0;
		typedef Vfs::Directory_service::Open_result Dir_result;
		typedef Vfs::File_io_service::Read_result File_result;

		Dir_result dres = VFS_THREAD_SAFE(root.open(path, O_RDONLY, &handle, alloc));
		if (dres != Dir_result::OPEN_OK) { return false; }

		typedef Vfs::File_io_service::Read_result Result;

		{
			struct Check : Libc::Suspend_functor
			{
				bool             retry { false };

				Vfs::Vfs_handle *handle;
				::size_t         count;

				Check(Vfs::Vfs_handle *handle, ::size_t count)
				: handle(handle), count(count) { }

				bool suspend() override
				{
					retry = !VFS_THREAD_SAFE(handle->fs().queue_read(handle, count));
					return retry;
				}
			} check (handle, buf_len - 1);

			do {
				Libc::suspend(check);
			} while (check.retry);
		}

		Vfs::file_size out_count = 0;
		Result         out_result;

		{
			struct Check : Libc::Suspend_functor
			{
				bool             retry { false };

				Vfs::Vfs_handle *handle;
				void            *buf;
				::size_t         count;
				Vfs::file_size  &out_count;
				Result          &out_result;

				Check(Vfs::Vfs_handle *handle, void *buf, ::size_t count,
					  Vfs::file_size &out_count, Result &out_result)
				: handle(handle), buf(buf), count(count), out_count(out_count),
				  out_result(out_result) { }

				bool suspend() override
				{
					out_result = VFS_THREAD_SAFE(handle->fs().complete_read(handle, (char *)buf,
					                            count, out_count));
					/* suspend me if read is still queued */
					retry = (out_result == Result::READ_QUEUED);
					return retry;
				}
			} check (handle, buf, buf_len - 1, out_count, out_result);

			do {
				Libc::suspend(check);
			} while (check.retry);
		}

		/* wake up threads blocking for 'queue_*()' or 'write()' */
		Libc::resume_all();

		handle->close();
		buf[out_count] = 0;

		return out_result == File_result::READ_OK;
	}
} /* anonymous namespace */


struct Tiocgwinsz
{
	unsigned columns;
	unsigned rows;

	Tiocgwinsz() : columns(0), rows(0) { }
	Tiocgwinsz(unsigned c, unsigned r) : columns(c), rows(r) { }

	static Tiocgwinsz parse(char const *buffer)
	{
		char *end = NULL;

		long cols = strtol(buffer, &end, 10);
		if (cols == -1) { return Tiocgwinsz(); }
		if ('x' == *end) { end++; }
		long rows = strtol(end, NULL, 10);
		if (rows == -1) { return Tiocgwinsz(); }

		return Tiocgwinsz { (unsigned)cols, (unsigned)rows };
	}
};


static int terminal_ioctl(Genode::Allocator &alloc, Vfs::File_system &root,
                           char const *dir, unsigned request, char *argp)
{
	if (!argp) { return Libc::Errno(EINVAL); }

	char buffer[4096];

	Util::Ioctl_path const file { dir, "/window_size" };
	if (!Util::read_file(alloc, root, file.string(),
	                     buffer, sizeof(buffer))) {
		return Libc::Errno(ENOTTY);
	}

	if (request == TIOCSETAW) {
		/* do nothing */
		return 0;
	} else

	if (request == TIOCGWINSZ) {

		Tiocgwinsz size = Tiocgwinsz::parse(buffer);

		::winsize *winsize = (::winsize *)argp;
		winsize->ws_col = size.columns;
		winsize->ws_row = size.rows;

		return 0;
	} else

	if (request == TIOCGETA) {

		::termios *termios = (::termios *)argp;

		termios->c_iflag = 0;
		termios->c_oflag = 0;
		termios->c_cflag = 0;
		/*
		 * Set 'ECHO' flag, needed by libreadline. Otherwise, echoing
		 * user input doesn't work in bash.
		 */
		termios->c_lflag = ECHO;
		::memset(termios->c_cc, _POSIX_VDISABLE, sizeof(termios->c_cc));
		termios->c_ispeed = 0;
		termios->c_ospeed = 0;

		return 0;
	}

	return Libc::Errno(EINVAL);
}


static int block_ioctl(Genode::Allocator &alloc, Vfs::File_system &root,
                       char const *dir, unsigned request, char *argp)
{
	char buffer[4096];

	if (request == DIOCGMEDIASIZE && argp) {

		Util::Ioctl_path const file { dir, "/media_size" };
		if (!Util::read_file(alloc, root, file.string(),
		                     buffer, sizeof(buffer))) {
			return Libc::Errno(EINVAL);
		}

		using Genode::int64_t;

		int64_t size = strtoull(buffer, NULL, 10);
		if (size > 0 && (Genode::uint64_t)size != ULLONG_MAX) {
			int64_t *disk_size = (int64_t*)argp;
			*disk_size = size;
			return 0;
		}
	}

	return Libc::Errno(EINVAL);
}


static int audio_ioctl(Genode::Allocator &alloc, Vfs::File_system &root,
                       char const *dir, unsigned request, char *argp)
{
	char buffer[4096];

	/*
	 * Normally used to request the number of channels, we just check if
	 * if number is equal to the available number.
	 */
	if (request == SNDCTL_DSP_CHANNELS && argp) {

		Util::Ioctl_path const file { dir, "/channels" };
		if (!Util::read_file(alloc, root, file.string(),
		                     buffer, sizeof(buffer))) {
			return Libc::Errno(EINVAL);
		}

		int const num_channels   = *(int const*)argp;
		int const avail_channels = atoi(buffer);
		if (num_channels != avail_channels) {
			return Libc::Errno(ENOTSUP);
		}

		return 0;
	} else

	if (request == SNDCTL_DSP_SAMPLESIZE && argp) {

		int const fmt = *(int const*)argp;
		/* only support format currently */
		return fmt == AFMT_S16_LE ? 0 : Libc::Errno(ENOTSUP);
	} else

	if (request == SNDCTL_DSP_SPEED && argp) {

		Util::Ioctl_path const file { dir, "/sample_rate" };
		if (!Util::read_file(alloc, root, file.string(),
		                     buffer, sizeof(buffer))) {
			return Libc::Errno(EINVAL);
		}

		int const speed = *(int const*)argp;
		int const rate  = atoi(buffer);

		return speed == rate ? 0 : Libc::Errno(ENOTSUP);
	} else

	if (request == SNDCTL_DSP_SETFRAGMENT && argp) {

		int frag_size = 0, frag_size_log2 = 0;
		{
			Util::Ioctl_path const file { dir, "/frag_size" };
			if (!Util::read_file(alloc, root, file.string(),
			                     buffer, sizeof(buffer))) {
				return Libc::Errno(EINVAL);
			}
			frag_size = atoi(buffer);
		}

		if (frag_size > 0) {
			frag_size_log2 = Genode::log2(frag_size);
		}

		/* XXX total */
		int total = 0;
		{
			Util::Ioctl_path const file { dir, "/queue_size" };
			if (!Util::read_file(alloc, root, file.string(),
			                     buffer, sizeof(buffer))) {
				return Libc::Errno(EINVAL);
			}
			total = atoi(buffer);
		}

		if (!total || !frag_size_log2) {
			return Libc::Errno(ENOTSUP);
		}

		*argp = ((unsigned)total << 16)|frag_size_log2;
		return 0;
	} else

	if (request == SNDCTL_DSP_POST) {
		/* do nothing, buffer will be drained eventually */
		return 0;
	} else

	if (request == SNDCTL_DSP_GETOSPACE && argp) {

		int frag_size = 0;
		{
			Util::Ioctl_path const file { dir, "/frag_size" };
			if (!Util::read_file(alloc, root, file.string(),
			                     buffer, sizeof(buffer))) {
				return Libc::Errno(EINVAL);
			}
			frag_size = atoi(buffer);
		}

		int frag_avail = 0;
		{
			Util::Ioctl_path const file { dir, "/frag_avail" };
			if (!Util::read_file(alloc, root, file.string(),
			                     buffer, sizeof(buffer))) {
				return Libc::Errno(EINVAL);
			}
			frag_avail = atoi(buffer);
		}

		if (!frag_avail || !frag_size) {
			return Libc::Errno(ENOTSUP);
		}

		audio_buf_info *bi = (audio_buf_info*)argp;
		bi->fragments = frag_avail;
		bi->fragsize  = frag_size;
		bi->bytes     = frag_size * frag_avail;

		return 0;
	}

	return Libc::Errno(EINVAL);
}


int Libc::Vfs_plugin::ioctl(Libc::File_descriptor *fd, int request, char *argp)
{
	if (!fd->ioctl_path) {

		/* only fd's with an fd_path can be used for ioctl requests */
		Util::Ioctl_path const &ioctl_dir = Util::construct_ioctl_path(fd->fd_path);
		if (!ioctl_dir.valid() ||
			!VFS_THREAD_SAFE(_root_dir.directory(ioctl_dir.string()))) {
			return Libc::Errno(EINVAL);
		}

		fd->ioctl_path = strdup(ioctl_dir.string());
	}

	typedef int(*ioctl_func_t)(Genode::Allocator&, Vfs::File_system&,
	                           char const*, unsigned, char*);
	ioctl_func_t ioctl_func = nullptr;

	switch (request) {
	case TIOCGWINSZ:
	case TIOCGETA:
	case TIOCSETAW:
		ioctl_func = terminal_ioctl;
		break;
	case DIOCGMEDIASIZE:
		ioctl_func = block_ioctl;
		break;
	case SNDCTL_DSP_CHANNELS:
	case SNDCTL_DSP_SAMPLESIZE:
	case SNDCTL_DSP_SPEED:
	case SNDCTL_DSP_SETFRAGMENT:
	case SNDCTL_DSP_POST:
	case SNDCTL_DSP_GETOSPACE:
		ioctl_func = audio_ioctl;
		break;
	default:
		return Libc::Errno(EINVAL);
	}

	return (*ioctl_func)(this->alloc(), this->root_dir(), fd->ioctl_path,
	                     (unsigned)request, argp);
}
