/*
 * \brief  Internal nodes of VFS server
 * \author Emery Hemingway
 * \author Christian Helmuth
 * \date   2016-03-29
 */

/*
 * Copyright (C) 2016-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#ifndef _VFS__NODE_H_
#define _VFS__NODE_H_

/* Genode includes */
#include <file_system/node.h>
#include <vfs/file_system.h>
#include <os/path.h>
#include <base/id_space.h>

/* Local includes */
#include "assert.h"

namespace Vfs_server {

	using namespace File_system;
	using namespace Vfs;

	struct Node;
	struct Directory;
	struct File;
	struct Symlink;

	typedef Genode::Id_space<Node> Node_space;

	struct File_io_handler
	{
		virtual void handle_file_io(File &file) = 0;
	};

	/**
	 * Read/write operation incomplete exception
	 *
	 * The operation can be retried later.
	 */
	struct Operation_incomplete { };

	/* Vfs::MAX_PATH is shorter than File_system::MAX_PATH */
	enum { MAX_PATH_LEN = Vfs::MAX_PATH_LEN };

	typedef Genode::Path<MAX_PATH_LEN> Path;

	typedef Genode::Allocator::Out_of_memory Out_of_memory;

	/**
	 * Type trait for determining the node type for a given handle type
	 */
	template<typename T> struct Node_type;
	template<> struct Node_type<Node_handle>    { typedef Node      Type; };
	template<> struct Node_type<Dir_handle>     { typedef Directory Type; };
	template<> struct Node_type<File_handle>    { typedef File      Type; };
	template<> struct Node_type<Symlink_handle> { typedef Symlink   Type; };


	/**
	 * Type trait for determining the handle type for a given node type
	 */
	template<typename T> struct Handle_type;
	template<> struct Handle_type<Node>      { typedef Node_handle    Type; };
	template<> struct Handle_type<Directory> { typedef Dir_handle     Type; };
	template<> struct Handle_type<File>      { typedef File_handle    Type; };
	template<> struct Handle_type<Symlink>   { typedef Symlink_handle Type; };

	/*
	 * Note that the file objects are created at the
	 * VFS in the local node constructors, this is to
	 * ensure that Out_of_metadata is thrown before
	 * the VFS is modified.
	 */
}


struct Vfs_server::Node : File_system::Node_base, Node_space::Element,
                          Vfs::Vfs_handle::Context
{
	Path const _path;
	Mode const  mode;

	Node(Node_space &space, char const *node_path, Mode node_mode)
	:
		Node_space::Element(*this, space),
		_path(node_path), mode(node_mode)
	{ }

	virtual ~Node() { }

	char const *path() { return _path.base(); }

	virtual size_t read(Vfs::File_system&, char*, size_t, seek_off_t) { return 0; }
	virtual size_t write(Vfs::File_system&, char const*, size_t, seek_off_t) { return 0; }
	virtual bool read_ready() { return false; }
	virtual void handle_io_response() { }
};

struct Vfs_server::Symlink : Node
{
	Symlink(Node_space &space,
	        Vfs::File_system &vfs,
	        char       const *link_path,
	        Mode              mode,
	        bool              create)
	: Node(space, link_path, mode)
	{
		if (create)
			assert_symlink(vfs.symlink("", link_path));
	}


	/********************
	 ** Node interface **
	 ********************/

	size_t read(Vfs::File_system &vfs, char *dst, size_t len, seek_off_t seek_offset)
	{
		Vfs::file_size res = 0;
		vfs.readlink(path(), dst, len, res);
		return res;
	}

	size_t write(Vfs::File_system &vfs, char const *src, size_t len, seek_off_t seek_offset)
	{
		/* ensure symlink gets something null-terminated */
		Genode::String<MAX_PATH_LEN> target(Genode::Cstring(src, len));

		if (vfs.symlink(target.string(), path()) == Directory_service::SYMLINK_OK)
			return 0;

		mark_as_updated();
		notify_listeners();
		return target.length();
	}

	bool read_ready() override { return true; }
};


class Vfs_server::File : public Node
{
	private:

		File_io_handler &_file_io_handler;

		Vfs::Vfs_handle *_handle;
		char const      *_leaf_path; /* offset pointer to Node::_path */

		bool _notify_read_ready = false;

		enum class Op_state {
			IDLE, READ_QUEUED
		} op_state = Op_state::IDLE;

	public:

		File(Node_space        &space,
		     Vfs::File_system  &vfs,
		     Genode::Allocator &alloc,
		     File_io_handler   &file_io_handler,
		     char       const  *file_path,
		     Mode               fs_mode,
		     bool               create)
		:
			Node(space, file_path, fs_mode),
			_file_io_handler(file_io_handler)
		{
			unsigned vfs_mode =
				(fs_mode-1) | (create ? Vfs::Directory_service::OPEN_MODE_CREATE : 0);

			assert_open(vfs.open(file_path, vfs_mode, &_handle, alloc));
			_leaf_path       = vfs.leaf_path(path());
			_handle->context = this;
		}

		~File() { _handle->ds().close(_handle); }

		void truncate(file_size_t size)
		{
			assert_truncate(_handle->fs().ftruncate(_handle, size));
			mark_as_updated();
		}

		void notify_read_ready(bool requested)
		{
			if (requested)
				_handle->fs().notify_read_ready(_handle);
			_notify_read_ready = requested;
		}

		bool notify_read_ready() const { return _notify_read_ready; }


		/********************
		 ** Node interface **
		 ********************/

		size_t read(Vfs::File_system&, char *dst, size_t len,
		            seek_off_t seek_offset) override
		{
			if (seek_offset == SEEK_TAIL) {
				typedef Directory_service::Stat_result Result;
				Vfs::Directory_service::Stat st;

				/* if stat fails, try and see if the VFS will seek to the end */
				seek_offset = (_handle->ds().stat(_leaf_path, st) == Result::STAT_OK) ?
					((len < st.size) ? (st.size - len) : 0) : SEEK_TAIL;
			}

			_handle->seek(seek_offset);

			typedef Vfs::File_io_service::Read_result Result;

			Vfs::file_size out_count  = 0;
			Result         out_result = Result::READ_OK;

			switch (op_state) {
			case Op_state::IDLE:

				if (!_handle->fs().queue_read(_handle, dst, len, out_result, out_count))
					throw Operation_incomplete();

				switch (out_result) {
				case Result::READ_OK:
					op_state = Op_state::IDLE;
					return out_count;

				case Result::READ_ERR_WOULD_BLOCK:
				case Result::READ_ERR_AGAIN:
				case Result::READ_ERR_INTERRUPT:
					op_state = Op_state::IDLE;
					throw Operation_incomplete();

				case Result::READ_ERR_IO:
				case Result::READ_ERR_INVALID:
					op_state = Op_state::IDLE;
					/* FIXME revise error handling */
					return 0;

				case Result::READ_QUEUED:
					op_state = Op_state::READ_QUEUED;
					break;
				}
				/* fall through */

			case Op_state::READ_QUEUED:
				out_result = _handle->fs().complete_read(_handle, dst, len, out_count);
				switch (out_result) {
				case Result::READ_OK:
					op_state = Op_state::IDLE;
					return out_count;

				case Result::READ_ERR_WOULD_BLOCK:
				case Result::READ_ERR_AGAIN:
				case Result::READ_ERR_INTERRUPT:
					op_state = Op_state::IDLE;
					throw Operation_incomplete();

				case Result::READ_ERR_IO:
				case Result::READ_ERR_INVALID:
					op_state = Op_state::IDLE;
					/* FIXME revise error handling */
					return 0;

				case Result::READ_QUEUED:
					op_state = Op_state::READ_QUEUED;
					throw Operation_incomplete();
				}
				break;
			}

			return 0;
		}

		size_t write(Vfs::File_system&, char const *src, size_t len,
		             seek_off_t seek_offset) override
		{
			Vfs::file_size res = 0;

			if (seek_offset == SEEK_TAIL) {
				typedef Directory_service::Stat_result Result;
				Vfs::Directory_service::Stat st;

				/* if stat fails, try and see if the VFS will seek to the end */
				seek_offset = (_handle->ds().stat(_leaf_path, st) == Result::STAT_OK) ?
					st.size : SEEK_TAIL;
			}

			_handle->seek(seek_offset);
			_handle->fs().write(_handle, src, len, res);
			if (res)
				mark_as_updated();
			return res;
		}

		bool read_ready() override { return _handle->fs().read_ready(_handle); }

		void handle_io_response() override
		{
			_file_io_handler.handle_file_io(*this);
		}
};


struct Vfs_server::Directory : Node
{
	Directory(Node_space &space, Vfs::File_system &vfs, char const *dir_path, bool create)
	: Node(space, dir_path, READ_ONLY)
	{
		if (create)
			assert_mkdir(vfs.mkdir(dir_path, 0));
	}

	Node_space::Id file(Node_space        &space,
	                    Vfs::File_system  &vfs,
	                    Genode::Allocator &alloc,
	                    File_io_handler   &file_io_handler,
	                    char        const *file_path,
	                    Mode               mode,
	                    bool               create)
	{
		Path subpath(file_path, path());
		char const *path_str = subpath.base();

		File *file;
		try {
			file = new (alloc)
			       File(space, vfs, alloc, file_io_handler, path_str, mode, create);
		} catch (Out_of_memory) { throw Out_of_metadata(); }

		if (create)
			mark_as_updated();
		return file->id();
	}

	Node_space::Id symlink(Node_space        &space,
	                       Vfs::File_system  &vfs,
	                       Genode::Allocator &alloc,
	                       char        const *link_path,
	                       Mode               mode,
	                       bool               create)
	{
		Path subpath(link_path, path());
		char const *path_str = subpath.base();

		if (!create) {
			Vfs::file_size out;
			assert_readlink(vfs.readlink(path_str, nullptr, 0, out));
		}

		Symlink *link;
		try { link = new (alloc) Symlink(space, vfs, path_str, mode, create); }
		catch (Out_of_memory) { throw Out_of_metadata(); }
		if (create)
			mark_as_updated();
		return link->id();
	}


	/********************
	 ** Node interface **
	 ********************/

	size_t read(Vfs::File_system &vfs, char *dst, size_t len, seek_off_t seek_offset)
	{
		Directory_service::Dirent vfs_dirent;
		size_t blocksize = sizeof(File_system::Directory_entry);

		unsigned index = (seek_offset / blocksize);

		size_t remains = len;

		while (remains >= blocksize) {
			if (vfs.dirent(path(), index++, vfs_dirent)
				!= Vfs::Directory_service::DIRENT_OK)
				return len - remains;

			File_system::Directory_entry *fs_dirent = (Directory_entry *)dst;
			fs_dirent->inode = vfs_dirent.fileno;
			switch (vfs_dirent.type) {
			case Vfs::Directory_service::DIRENT_TYPE_DIRECTORY:
				fs_dirent->type = File_system::Directory_entry::TYPE_DIRECTORY;
				break;
			case Vfs::Directory_service::DIRENT_TYPE_SYMLINK:
				fs_dirent->type = File_system::Directory_entry::TYPE_SYMLINK;
				break;
			case Vfs::Directory_service::DIRENT_TYPE_FILE:
			default:
				fs_dirent->type = File_system::Directory_entry::TYPE_FILE;
				break;
			}
			strncpy(fs_dirent->name, vfs_dirent.name, MAX_NAME_LEN);

			remains -= blocksize;
			dst += blocksize;
		}
		return len - remains;
	}

	bool read_ready() override { return true; }
};

#endif /* _VFS__NODE_H_ */
