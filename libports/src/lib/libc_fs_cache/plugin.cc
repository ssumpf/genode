/*
 * \brief  Subset of 'libc_fs' plugin with read only cache
 * \author Norman Feske
 * \author Sebastian Sumpf
 * \date   2012-09-18
 */

/*
 * Copyright (C) 2012 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

/* Genode includes */
#include <base/allocator_avl.h>
#include <base/printf.h>
#include <file_system_session/connection.h>
#include <util/avl_tree.h>

/* libc includes */
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

/* libc plugin interface */
#include <libc-plugin/plugin.h>
#include <libc-plugin/fd_alloc.h>

/* libc-internal includes */
#include <libc_mem_alloc.h>


namespace File_system { struct Packet_ref { }; }

namespace {

enum { PATH_MAX_LEN = 256 };


/**
 * Current working directory
 */
struct Cwd
{
	char path[PATH_MAX_LEN];

	Cwd() { Genode::strncpy(path, "/", sizeof(path)); }
};


static Cwd *cwd()
{
	static Cwd cwd_inst;
	return &cwd_inst;
}


struct Canonical_path
{
	char str[PATH_MAX_LEN];

	Canonical_path(char const *pathname)
	{
		/*
		 * If pathname is a relative path, prepend the current working
		 * directory.
		 *
		 * XXX we might consider using Noux' 'Path' class here
		 */
		if (pathname[0] != '/') {
			snprintf(str, sizeof(str), "%s/%s", cwd()->path, pathname);
		} else {
			strncpy(str, pathname, sizeof(str));
		}
	}
};


static File_system::Session *file_system()
{
	static Genode::Allocator_avl tx_buffer_alloc(Genode::env()->heap());
	static File_system::Connection fs(tx_buffer_alloc);
	return &fs;
}


struct Node_handle_guard
{
	File_system::Node_handle handle;

	Node_handle_guard(File_system::Node_handle handle) : handle(handle) { }

	~Node_handle_guard() { file_system()->close(handle); }
};


class Plugin_context : public Libc::Plugin_context,
                       public File_system::Packet_ref
{
	private:

		enum Type { TYPE_FILE, TYPE_DIR, TYPE_SYMLINK };

		Type                     _type;
		File_system::Node_handle _node_handle;
		off_t                    _seek_offset;
		char                     _path[PATH_MAX_LEN];

	public:

		bool in_flight;

		Plugin_context(File_system::File_handle handle, char *path)
		: _type(TYPE_FILE), _node_handle(handle), _seek_offset(0), in_flight(false)
		{
			size_t len = Genode::strlen(path);
			Genode::memcpy(_path, path, len);
			_path[len] = 0;
		}

		Plugin_context(File_system::Dir_handle handle)
		: _type(TYPE_DIR), _node_handle(handle), _seek_offset(0), in_flight(false)
		{ }

		Plugin_context(File_system::Symlink_handle handle)
		: _type(TYPE_SYMLINK), _node_handle(handle), _seek_offset(0), 
		  in_flight(false) { }

		File_system::Node_handle node_handle() const { return _node_handle; }

		/**
		 * Return seek offset if handle is in non-append mode
		 */
		off_t seek_offset() const { return _seek_offset; }

		/**
		 * Set seek offset, switch to non-append mode
		 */
		void seek_offset(size_t seek_offset) { _seek_offset = seek_offset; }

		/**
		 * Advance current seek position by 'incr' number of bytes
		 *
		 * This function has no effect if the handle is in append mode.
		 */
		void advance_seek_offset(size_t incr)
		{
			_seek_offset += incr;
		}

		/**
		 * Return canonical path of this context
		 */
		char *path() { return _path; }
};


static void obtain_stat_for_node(File_system::Node_handle node_handle,
                                 struct stat *buf)
{
	if (!buf)
		return;

	File_system::Status status = file_system()->status(node_handle);

	/*
	 * Translate status information to 'struct stat' format
	 */
	memset(buf, 0, sizeof(struct stat));
	buf->st_size = status.size;

	if (status.is_directory())
		buf->st_mode |= S_IFDIR;
	else if (status.is_symlink())
		buf->st_mode |= S_IFLNK;
	else
		buf->st_mode |= S_IFREG;

	struct tm tm;
	memset(&tm, 0, sizeof(struct tm));

	buf->st_mtime = mktime(&tm);
}


static inline Plugin_context *context(Libc::File_descriptor *fd)
{
	return fd->context ? static_cast<Plugin_context *>(fd->context) : 0;
}


static void wait_for_acknowledgement(File_system::Session::Tx::Source &source)
{
	::File_system::Packet_descriptor packet = source.get_acked_packet();
	static_cast<Plugin_context *>(packet.ref())->in_flight = false;

	source.release_packet(packet);
}


static void collect_acknowledgements(File_system::Session::Tx::Source &source)
{
	while (source.ack_avail())
		wait_for_acknowledgement(source);
}


/**
 * Local read function
 */
static ssize_t _read(Libc::File_descriptor *fd, void *buf, ::size_t count)
{
	File_system::Session::Tx::Source &source = *file_system()->tx();

	size_t const max_packet_size = source.bulk_buffer_size() / 2;

	size_t remaining_count = count;

	while (remaining_count) {

		collect_acknowledgements(source);

		size_t curr_packet_size = Genode::min(remaining_count, max_packet_size);

		/*
		 * XXX handle 'Packet_alloc_failed' exception'
		 */
		File_system::Packet_descriptor
			packet(source.alloc_packet(curr_packet_size),
			       static_cast<File_system::Packet_ref *>(context(fd)),
			       context(fd)->node_handle(),
			       File_system::Packet_descriptor::READ,
			       curr_packet_size,
			       context(fd)->seek_offset());

		/* mark context as having an operation in flight */
		context(fd)->in_flight = true;

		/* pass packet to server side */
		source.submit_packet(packet);

		do {
			packet = source.get_acked_packet();
			static_cast<Plugin_context *>(packet.ref())->in_flight = false;
		} while (context(fd)->in_flight);

		context(fd)->in_flight = false;

		/*
		 * XXX check if acked packet belongs to request,
		 *     needed for thread safety
		 */

		size_t read_num_bytes = Genode::min(packet.length(), curr_packet_size);

		/* copy-out payload into destination buffer */
		memcpy(buf, source.packet_content(packet), read_num_bytes);

		source.release_packet(packet);

		/* prepare next iteration */
		context(fd)->advance_seek_offset(read_num_bytes);
		buf = (void *)((Genode::addr_t)buf + read_num_bytes);
		remaining_count -= read_num_bytes;

		/*
		 * If we received less bytes than requested, we reached the end
		 * of the file.
		 */
		if (read_num_bytes < curr_packet_size)
			break;
	}

	return count - remaining_count;
}
} /* end namespace */


namespace Genode
{

	/**
	 * Simple AVL based read-only file cache, with
	 *
	 * XXX: Add file replacement
	 */
	class File_cache : public Allocator_avl
	{
		private:

			enum { CACHE_SIZE = 1024 * 1024 };

			/**
			 * Cache entry
			 */
			class Entry : public Avl_node<Entry>
			{
				private:

					Plugin_context *_ctx; 
					int             _ref;  /* reference count */
					void           *_base; /* base address of file */
					struct stat     _buf;  /* stat buf of file */

				public:

					Entry (Plugin_context *ctx)
					: _ctx(ctx), _ref(0) { }

					~Entry() { }

					bool higher(Entry *e)
					{
						/* we use the path as AVL index */
						return strcmp(e->_ctx->path(), _ctx->path()) > 0;
					}

					/**
					 * Find entry by path
					 */
					Entry const *find(char const *path) const
					{
						int higher = strcmp(path, _ctx->path()) > 0;
						if (!higher)
							return this;

						Entry *e = Avl_node<Entry>::child(higher);
						return e ? e->find(path) : 0;
					}

					/**
					 * Accessors
					 */
					struct stat const *stat_buf() const { return &_buf; }
					struct stat *stat() { return &_buf; }
					void   base(void *base) { _base = base; }
					void  *base() const { return _base; }
					Plugin_context *context() const { return _ctx; }
			};

			/**
			 * AVL tree containing cache entries
			 */
			class Entry_tree : public Avl_tree<Entry>
			{
				public:
	
					Entry const *find(char const *path) const {
						return first() ? first()->find(path) : 0; }
			};


			addr_t     _base;  /* base address of cache */
			size_t     _size;  /* size of cache */
			Entry_tree _cache; /* cache */

			/**
			 * Return true if file is in cache
			 */
			Entry const *_hit(char const *path) const
			{ return _cache.find(path); }

			/**
			 * Private mmap
			 */
			void _mmap(Entry *e, Libc::File_descriptor *fd)
			{
				void *addr;
				size_t size = e->stat_buf()->st_size;

				if (!alloc(size, &addr))
					throw -1;

				if (_read(fd, addr, size) < 0) {
					free(addr, size);
					throw -2;
				}

				e->base(addr);
			}

		public:

			class Caching_failed : public Exception { };

			/**
			 * Constructor
			 */
			File_cache(size_t cache_size = CACHE_SIZE)
			: Allocator_avl(env()->heap()), _size(cache_size)
			{
				Ram_dataspace_capability ds_cap = env()->ram_session()->alloc(_size);
				_base      = (addr_t)env()->rm_session()->attach(ds_cap);
				add_range(_base, _size);
			}

			/**
			 * Try to cache a context for given 'fd'
			 */
			void cache_context(Plugin_context *context, Libc::File_descriptor *fd)
			{
				Entry *e = new(env()->heap()) Entry(context);

				/* stat file */
				if (stat(context->path(), e->stat()) != 0) {
					destroy(env()->heap(), e);
					throw Caching_failed();
				}

				/* map file */
				try {
					_mmap(e, fd);
				} catch (...) {
					destroy(env()->heap(), e);
					throw Caching_failed();
				}
				_cache.insert(e);
			}

			/**
			 * Return address if context is mapped in cache,
			 * 0 otherwise
			 */
			void *mmap(Plugin_context *context)
			{
				Entry const *e;
				if ((e = _hit(context->path())))
					return e->base();

				return 0;
			}

			/**
			 * Return true if addr belongs to a cached file
			 */
			bool munmap(void *addr)
			{
				addr_t a = (addr_t)addr;
				return (a > _base && a < _base + _size) ? true : false;
			}

			/**
			 * Open and cache file if possbile
			 */
			Plugin_context *open(char const *pathname)
			{
				Canonical_path path(pathname);
				Entry const *e;
				if ((e  = _hit(path.str)))
					return e->context();

				/*
				 * Determine directory path that contains the node to open
				 */
				unsigned last_slash = 0;
				for (unsigned i = 0; path.str[i]; i++)
					if (path.str[i] == '/')
						last_slash = i;

				char dir_path[256] = "/";
				if (last_slash > 0)
					Genode::strncpy(dir_path, path.str,
					                Genode::min(sizeof(dir_path), last_slash + 1));

				/*
				 * Determine base name
				 */
				char const *basename = path.str + last_slash + 1;

				/*
				 * Open directory that contains the file to be opened/created
				 */
				File_system::Dir_handle const dir_handle =
				    file_system()->dir(dir_path, false);

				Node_handle_guard guard(dir_handle);

				File_system::File_handle handle;
				handle = file_system()->file(dir_handle, basename,
				                             File_system::READ_ONLY, false);

				return new (Genode::env()->heap())
				            Plugin_context(handle, path.str);
			}

			/**
			 * Return if file is in cache
			 */
			bool close(Plugin_context *context)
			{
				return _hit(context->path());
			}

			/**
			 * Stat file
			 */
			int stat(const char *pathname, struct stat *buf)
			{
				Canonical_path path(pathname);
				Entry const *e;
				if ((e  = _hit(path.str))) {
					Genode::memcpy(buf, e->stat_buf(), sizeof(struct stat));
					return 0;
				}
	
				try {
					File_system::Node_handle const node_handle =
						file_system()->node(path.str);
					Node_handle_guard guard(node_handle);
	
					obtain_stat_for_node(node_handle, buf);
					return 0;
				}
				catch (File_system::Lookup_failed) {
					PERR("lookup failed");
					errno = ENOENT;
				}
				return -1;
			}

			/**
			 * Instance of File_cache
			 */
			static File_cache *f()
			{
				static File_cache _f;
				return &_f;
			}
	};
}


namespace {

/**
 * Libc plugin
 */
class Plugin : public Libc::Plugin
{
	public:

		bool in_flight;

		bool supports_open(const char *pathname, int flags) {
			return true; }

		bool supports_stat(const char *path) {
			return true; }

		bool supports_mmap() { return true; }

		Libc::File_descriptor *open(const char *pathname, int flags)
		{
			Canonical_path path(pathname);

			/*
			 * Probe for an existing directory to open
			 */
			try {
				File_system::Dir_handle const handle =
					file_system()->dir(path.str, false);

				Plugin_context *context = new (Genode::env()->heap())
				                               Plugin_context(handle);

				return Libc::file_descriptor_allocator()->alloc(this, context);
			} catch (File_system::Lookup_failed) { }

			Libc::File_descriptor *fd = 0;
			try {
				Plugin_context *context = Genode::File_cache::f()->open(path.str);
				fd = Libc::file_descriptor_allocator()->alloc(this, context);
				Genode::File_cache::f()->cache_context(context, fd);
			}
			catch (File_system::Lookup_failed) {
				PERR("open(%s) lookup failed", pathname); 
				return 0;
			}
			catch (Genode::File_cache::Caching_failed) { }

			return fd;
		}

		int close(Libc::File_descriptor *fd)
		{
			/* wait for the completion of all operations of the context */
			while (context(fd)->in_flight)
				wait_for_acknowledgement(*file_system()->tx());

			/* close if not in cache */
			if (!Genode::File_cache::f()->close(context(fd))) {
				file_system()->close(context(fd)->node_handle());
				Genode::destroy(Genode::env()->heap(), context(fd));
			}

			Libc::file_descriptor_allocator()->free(fd);

			return 0;
		}


		int stat(const char *pathname, struct stat *buf)
		{
			return Genode::File_cache::f()->stat(pathname, buf);
		}

		void *mmap(void *addr_in, ::size_t length, int prot, int flags,
		           Libc::File_descriptor *fd, ::off_t offset)
		{
			if (prot != PROT_READ) {
				PERR("mmap for prot=%x not supported", prot);
				errno = EACCES;
				return (void *)-1;
			}

			if (addr_in != 0) {
				PERR("mmap for predefined address not supported");
				errno = EINVAL;
				return (void *)-1;
			}

			void *addr;
			if ((addr = Genode::File_cache::f()->mmap(context(fd))))
				return (void *)((off_t)addr + offset);


			addr = Libc::mem_alloc()->alloc(length, PAGE_SHIFT);
			if (addr == (void *)-1) {
				errno = ENOMEM;
				return (void *)-1;
			}

			context(fd)->seek_offset(offset);
			if (_read(fd, addr, length) < 0) {
				PERR("mmap could not obtain file content");
				::munmap(addr, length);
				errno = EACCES;
				return (void *)-1;
			}

			return addr;
		}

		int munmap(void *addr, ::size_t)
		{
			if (!Genode::File_cache::f()->munmap(addr))
				Libc::mem_alloc()->free(addr);
			return 0;
		}

};
} /* unnamed namespace */


void __attribute__((constructor)) init_libc_fs_cache(void)
{
	PDBG("using the libc_fs_cache plugin");
	static Plugin plugin;
}

