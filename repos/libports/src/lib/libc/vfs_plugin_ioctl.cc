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
	               char const *path, char *buffer, size_t buffer_len)
	{
			Vfs::Vfs_handle *handle = 0;
			typedef Vfs::Directory_service::Open_result Dir_result;
			typedef Vfs::File_io_service::Read_result File_result;

			Dir_result dres = VFS_THREAD_SAFE(root.open(path, O_RDONLY, &handle, alloc));
			if (dres != Dir_result::OPEN_OK) { return false; }

			Vfs::file_size out_count = 0;
			File_result fres = VFS_THREAD_SAFE(handle->fs().complete_read(handle, buffer,
			                                   buffer_len - 1, out_count));
			handle->close();
			buffer[out_count] = 0;

			return fres == File_result::READ_OK;
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

	/* XXX handle ENOTTY? */
	if (request == TIOCSETAW) {
		/* do nothing */
		return 0;
	}

	Util::Ioctl_path const file { dir, "/window_size" };
	bool const read_ok = Util::read_file(alloc, root, file.string(),
	                                     buffer, sizeof(buffer));
	if (!read_ok) { return Libc::Errno(ENOTTY); }

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
		bool const read_ok = Util::read_file(alloc, root, file.string(),
		                                     buffer, sizeof(buffer));
		if (!read_ok) { return Libc::Errno(EINVAL); }

		using Genode::int64_t;

		int64_t size = strtoull(buffer, nullptr, 10);
		if (size > 0 && (Genode::uint64_t)size != ULLONG_MAX) {
			int64_t *disk_size = (int64_t*)argp;
			*disk_size = size;
			return 0;
		}
	}

	return Libc::Errno(EINVAL);
}


int Libc::Vfs_plugin::ioctl(Libc::File_descriptor *fd, int request, char *argp)
{
	/*
	 * Only fds with fd_path set can be used for ioctl.
	 */
	if (!fd->ioctl_path) {

		Util::Ioctl_path const &ioctl_dir = Util::construct_ioctl_path(fd->fd_path);
		if (!ioctl_dir.valid() ||
			!VFS_THREAD_SAFE(_root_dir.directory(ioctl_dir.string()))) {
			return Libc::Errno(EINVAL);
		}

		if (!fd->ioctl_path) { fd->ioctl_path = strdup(ioctl_dir.string()); }
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
	default:
		return Libc::Errno(EINVAL);
	}

	return (*ioctl_func)(this->alloc(), this->root_dir(), fd->ioctl_path,
	                     (unsigned)request, argp);
}
