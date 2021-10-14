/*
 * \brief  Minimal file system for GPU session
 * \author Sebastian Sumpf
 * \date   2021-10-14
 *
 * The file system only handles completion signals of the GPU session in order
 * to work from non-EP threads (i.e., pthreads) in libc components. A read
 * returns only in case a completion signal has been delivered since the
 * previous call to read.
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <gpu_session/connection.h>
#include <os/vfs.h>
#include <util/xml_generator.h>
#include <vfs/single_file_system.h>

namespace Vfs_gpu
{
	using namespace Vfs;
	using namespace Genode;

	struct File_system;
}


/*
 * XXX: 'vfs_gpu_connection' to be looked up from libdrm in order to retrieve
 * the GPU connection
 */
static Gpu::Connection *gpu { nullptr };

Gpu::Connection &vfs_gpu_connection()
{
	return *gpu;
}


struct Vfs_gpu::File_system : Single_file_system
{
	struct Gpu_vfs_handle : Single_vfs_handle
	{
		bool             _complete { false };
		Genode::Env     &_env;
		Gpu::Connection &_gpu_session;

		Genode::Io_signal_handler<Gpu_vfs_handle> _completion_sigh {
			_env.ep(), *this, &Gpu_vfs_handle::_handle_completion };

		void _handle_completion()
		{
			_complete = true; 
			io_progress_response();
		}

		Gpu_vfs_handle(Genode::Env &env,
		               Directory_service &ds,
		               File_io_service   &fs,
		               Genode::Allocator &alloc,
		               Gpu::Connection &gpu_session)
		: Single_vfs_handle(ds, fs, alloc, 0),
		  _env(env), _gpu_session(gpu_session)
		{
			_gpu_session.completion_sigh(_completion_sigh);
		}

		Read_result read(char *dst, file_size count,
		                 file_size &out_count) override
		{
			if (!_complete) return READ_QUEUED;

			_complete = false;
			dst[0]    = 1;
			out_count = 1;

			return READ_OK;
		}

		Write_result write(char const *, file_size, file_size &) override
		{
			return WRITE_ERR_IO;
		}

		bool read_ready() override { return _complete; }
	};

	Vfs::Env &_env;
	Gpu::Connection _gpu_session { _env.env() };

	typedef String<32> Config;

	File_system(Vfs::Env &env, Xml_node config)
	:
	  Single_file_system(Node_type::CONTINUOUS_FILE,
	                     type_name(),
	                     Node_rwx::ro(),
	                     config),
	  _env(env)
	{
		gpu = &_gpu_session;
	}

	~File_system() { gpu = nullptr; }

	Open_result open(char const  *path, unsigned,
	                 Vfs::Vfs_handle **out_handle,
	                 Allocator   &alloc) override
	{
		if (!_single_file(path))
			return OPEN_ERR_UNACCESSIBLE;

		try {
			*out_handle = new (alloc)
				Gpu_vfs_handle(_env.env(), *this, *this, alloc, _gpu_session);

			return OPEN_OK;
		}
		catch (Genode::Out_of_ram)  { return OPEN_ERR_OUT_OF_RAM; }
		catch (Genode::Out_of_caps) { return OPEN_ERR_OUT_OF_CAPS; }
	}

	static char const *type_name() { return "gpu"; }
	char const *type() override { return type_name(); }
};


/**************************
 ** VFS plugin interface **
 **************************/

extern "C" Vfs::File_system_factory *vfs_file_system_factory(void)
{
	struct Factory : Vfs::File_system_factory
	{
		Vfs::File_system *create(Vfs::Env &vfs_env,
		                         Genode::Xml_node node) override
		{
			try { return new (vfs_env.alloc())
				Vfs_gpu::File_system(vfs_env, node); }
			catch (...) { Genode::error("could not create 'gpu_fs' "); }
			return nullptr;
		}
	};

	static Factory factory;
	return &factory;
}
