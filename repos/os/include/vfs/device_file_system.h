/*
 * \brief  File system that hosts a pseudo device
 * \author Josef Soentgen
 * \date   2018-10-16
 */

/*
 * Copyright (C) 2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__VFS__DEVICE_FILE_SYSTEM_H_
#define _INCLUDE__VFS__DEVICE_FILE_SYSTEM_H_

/* Genode includes */
#include <os/path.h>
#include <vfs/dir_file_system.h>
#include <vfs/vfs_handle.h>

namespace Vfs { class Device_file_system; }


class Vfs::Device_file_system : public File_system,
                                public File_system_factory
{
	public:

		enum Node_type {
			NODE_TYPE_CHAR_DEVICE, NODE_TYPE_BLOCK_DEVICE
		};

	private:

		Node_type const _node_type;

		enum { FILENAME_MAX_LEN = 64 };
		char _filename[FILENAME_MAX_LEN];

		enum { PATH_MAX_LEN = 256, };
		using Path = Genode::String<PATH_MAX_LEN>;
		Path _dirname { "/." };

		Genode::Constructible<Vfs::Dir_file_system> _dir_fs { };

	protected:

		struct Device_vfs_handle : Vfs_handle
		{
			using Vfs_handle::Vfs_handle;

			Device_vfs_handle(Directory_service &ds,
			                  File_io_service   &fs,
			                  Genode::Allocator &alloc,
			                  int                status_flags)
			: Vfs_handle(ds, fs, alloc, status_flags) { }

			virtual Read_result read(char *dst, file_size count,
			                         file_size &out_count) = 0;

			virtual Write_result write(char const *, file_size, file_size &)
			{
				return WRITE_ERR_INVALID;
			}

			virtual bool read_ready() = 0;
		};

		struct Device_vfs_root_dir_handle : Device_vfs_handle
		{
			private:

				Node_type   _node_type;
				char const *_filename;

				/*
				 * Noncopyable
				 */
				Device_vfs_root_dir_handle(Device_vfs_root_dir_handle const &);
				Device_vfs_root_dir_handle &operator = (Device_vfs_root_dir_handle const &);

			public:

				Device_vfs_root_dir_handle(Directory_service &ds,
				                      File_io_service   &fs,
				                      Genode::Allocator &alloc,
				                      Node_type node_type,
				                      char const *filename)
				: Device_vfs_handle(ds, fs, alloc, 0),
				  _node_type(node_type),
				  _filename(filename)
				{ }

				char const *name() { return _filename; }

				Read_result read(char *dst, file_size count,
				                 file_size &out_count) override
				{
					out_count = 0;

					if (count < sizeof(Dirent))
						return READ_ERR_INVALID;

					file_size index = seek() / sizeof(Dirent);

					Dirent *out = (Dirent*)dst;

					if (index == 0) {
						out->fileno = (Genode::addr_t)this;
						switch (_node_type) {
						case NODE_TYPE_CHAR_DEVICE:  out->type = DIRENT_TYPE_CHARDEV;  break;
						case NODE_TYPE_BLOCK_DEVICE: out->type = DIRENT_TYPE_BLOCKDEV; break;
						}
						strncpy(out->name, _filename, sizeof(out->name));
					} else {
						out->type = DIRENT_TYPE_END;
					}

					out_count = sizeof(Dirent);

					return READ_OK;
				}

				Write_result write(char const *, file_size, file_size &) override
				{
					return WRITE_ERR_INVALID;
				}

				bool read_ready() override { return true; }
		};

		bool _root(char const *path)
		{
			return (strcmp(path, "") == 0) || (strcmp(path, "/") == 0);
		}

		bool _device_file(char const *path)
		{
			return (strlen(path) == (strlen(_filename) + 1)) &&
			       (strcmp(&path[1], _filename) == 0);
		}

		bool _device_dir(char const *path)
		{
			return (_dirname == path);
		}

		bool _device_dir_file(char const *path)
		{
			Genode::size_t const dlen = _dirname.length() - 1;
			return (strcmp(_dirname.string(), path, dlen) == 0) &&
			       (strlen(path) > dlen);
		}

	public:

		Device_file_system(Node_type node_type, char const *type_name, Xml_node config)
		:
			_node_type(node_type)
		{
			strncpy(_filename, type_name, sizeof(_filename));

			try { config.attribute("name").value(_filename, sizeof(_filename)); }
			catch (...) { }

			// XXX move to better location
			_dirname = Path("/.", (char const*)_filename);
		}

		void construct(Vfs::Env &env, Xml_node config,
		               Vfs::File_system_factory &factory)
		{
			_dir_fs.construct(env, config, factory);
		}

		void destruct() { _dir_fs.destruct(); }

		/*********************************
		 ** Directory-service interface **
		 *********************************/

		Dataspace_capability dataspace(char const *) override {
			return Dataspace_capability(); }

		void release(char const *, Dataspace_capability) override { }

		Open_result open(char const *path, unsigned flags,
		                 Vfs_handle **out_handle,
		                 Allocator   &alloc) override
		{
			return _dir_fs->open(path, flags, out_handle, alloc);
		}

		Stat_result stat(char const *path, Stat &out) override
		{
			out = Stat();
			out.device = (Genode::addr_t)this;

			if (_root(path) || _device_dir(path)) {
				out.mode = STAT_MODE_DIRECTORY;

				return STAT_OK;
			} else if (_device_file(path)) {
				switch (_node_type) {
				case NODE_TYPE_CHAR_DEVICE:  out.mode = STAT_MODE_CHARDEV;  break;
				case NODE_TYPE_BLOCK_DEVICE: out.mode = STAT_MODE_BLOCKDEV; break;
				}
				out.inode = 1;
				return STAT_OK;
			} else if (_device_dir_file(path)) {
				return _dir_fs->stat(path, out);
			}

			return STAT_ERR_NO_ENTRY;
		}

		file_size num_dirent(char const *path) override
		{
			if (_root(path))       { return 1; }
			if (_device_dir(path)) { return _dir_fs->num_dirent(path); }
			return 0;
		}

		bool directory(char const *path) override
		{
			return (_root(path) || _device_dir(path));
		}

		char const *leaf_path(char const *path) override
		{
			return _device_file(path) ? path : 0;
		}

		Opendir_result opendir(char const *path, bool create,
		                       Vfs_handle **out_handle,
		                       Allocator &alloc) override
		{
			if (!_root(path) && !_device_dir(path)) {
				return OPENDIR_ERR_LOOKUP_FAILED;
			}

			if (create) { return OPENDIR_ERR_PERMISSION_DENIED; }

			try {
				if (_root(path)) {
						*out_handle = new (alloc)
							Device_vfs_root_dir_handle(*this, *this, alloc,
							                           _node_type, _filename);
						return OPENDIR_OK;
				} else

				if (_device_dir(path)) {
					return _dir_fs->opendir(path, false, out_handle, alloc);
				}
			}
			catch (Genode::Out_of_ram)  { return OPENDIR_ERR_OUT_OF_RAM; }
			catch (Genode::Out_of_caps) { return OPENDIR_ERR_OUT_OF_CAPS; }

			return OPENDIR_ERR_LOOKUP_FAILED;
		}

		void close(Vfs_handle *handle) override
		{
			if (handle && (&handle->ds() == this))
				destroy(handle->alloc(), handle);
		}

		Watch_result watch(char const      *path,
		                   Vfs_watch_handle **handle,
		                   Allocator        &alloc) override
		{
			return _dir_fs->watch(path, handle, alloc);
		}

		void close(Vfs_watch_handle *handle) override
		{
			_dir_fs->close(handle);
		}

		Unlink_result unlink(char const *) override
		{
			return UNLINK_ERR_NO_PERM;
		}

		Rename_result rename(char const *from, char const *to) override
		{
			if (_device_file(from) || _device_file(to)) {
				return RENAME_ERR_NO_PERM;
			}
			return RENAME_ERR_NO_ENTRY;
		}

		/********************************
		 ** File I/O service interface **
		 ********************************/

		Read_result complete_read(Vfs_handle *vfs_handle, char *dst,
		                          file_size count,
		                          file_size &out_count) override
		{
			Device_vfs_handle *handle =
				static_cast<Device_vfs_handle*>(vfs_handle);
			return handle ? handle->read(dst, count, out_count)
			              : READ_ERR_INVALID;
		}

		Write_result write(Vfs_handle *vfs_handle, char const *src, file_size count,
		                   file_size &out_count) override
		{
			if ((vfs_handle->status_flags() & OPEN_MODE_ACCMODE) == OPEN_MODE_RDONLY) {
				return WRITE_ERR_INVALID;
			}

			Device_vfs_handle *handle =
				static_cast<Device_vfs_handle*>(vfs_handle);
			return handle ? handle->write(src, count, out_count)
			              : WRITE_ERR_INVALID;
		}

		bool read_ready(Vfs_handle *vfs_handle) override
		{
			Device_vfs_handle *handle =
				static_cast<Device_vfs_handle*>(vfs_handle);
			return handle ? handle->read_ready() : false;
		}

		Ftruncate_result ftruncate(Vfs_handle *, file_size) override
		{
			return FTRUNCATE_ERR_NO_PERM;
		}
};

#endif /* _INCLUDE__VFS__DEVICE_FILE_SYSTEM_H_ */
