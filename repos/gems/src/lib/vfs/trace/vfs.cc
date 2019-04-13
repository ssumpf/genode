
/* Genode includes */
#include <vfs/dir_file_system.h>
#include <vfs/single_file_system.h>

#include <gems/vfs.h>
#include <util/xml_generator.h>

#include <trace_session/connection.h>

#include "directory_tree.h"

#include <base/debug.h>

namespace Vfs_trace {

	using namespace Vfs;
	using namespace Genode;

	struct File_system;
	class  Local_factory;
	struct  Content;

}

struct Vfs_trace::Content : Vfs::Single_file_system
{
	Vfs::Env          &_vfs_env;
	Trace::Connection  _trace { _vfs_env.env(), 10*4096, 32*1024, 0 };
	enum { MAX_SUBJECTS = 32 };
	Trace::Subject_id  _subjects[MAX_SUBJECTS];
	unsigned           _subject_count;

	unsigned char  _buf[1024*1024];
	unsigned long  _buf_len = 0;

	struct Vfs_handle : Single_vfs_handle
	{
		unsigned char  *_buf     = nullptr;
		unsigned long   _buf_len = 0;

		Vfs_handle(Directory_service &ds,
		           File_io_service   &fs,
		           Genode::Allocator &alloc,
		           unsigned char     *buf,
		           unsigned long      buf_len)
		: Single_vfs_handle(ds, fs, alloc, 0),
		  _buf(buf), _buf_len(buf_len)  { }


		Read_result read(char *dst, file_size count,
		                 file_size &out_count) override
		{
			file_size const max_size = _buf_len;
			file_size const read_offset = seek();
			file_size const end_offset = min(count + read_offset, max_size);
			out_count = 0;

			if (read_offset > end_offset)
				return READ_OK;

			file_size const num_bytes = end_offset - read_offset;
			memcpy(dst, _buf + read_offset, num_bytes);
			out_count = num_bytes;

			return READ_OK;
		}

		Write_result write(char const *, file_size,
		                   file_size &out_count) override
		{
			out_count = 0;
			return WRITE_ERR_INVALID;
		}

		bool read_ready() override { return true; }
	};

	Content(Vfs::Env &env)
	: Single_file_system(NODE_TYPE_FILE, type_name(), Xml_node("<trace_out/>")),
	  _vfs_env(env)
	{

		bool success = false;
		while (!success) {
			try {
				_subject_count = _trace.subjects(_subjects, MAX_SUBJECTS);
				success = true;
			} catch(Genode::Out_of_ram) {
				_trace.upgrade_ram(4096);
				success = false;
			}
		}

		Directory_tree dir { _vfs_env.alloc()};

		for (unsigned i = 0; i < _subject_count; i++) {
			Trace::Subject_info info = _trace.subject_info(_subjects[i]);
			PDBG("subject: ", info.session_label());
			dir.insert(info, _subjects[i]);
			PDBG("return");
		}

		PDBG("subject count: ", _subject_count);
		return;

		unsigned char *buf = _buf;

		for (unsigned i = 0; i < _subject_count; i++) {
			Trace::Subject_info info = _trace.subject_info(_subjects[i]);
			int written = Genode::snprintf((char *)buf, 1024*1024 - _buf_len, "%s %s: %s ex: %lld\n",
			                               info.session_label().string(),
			                               info.thread_name().string(),
			                               Trace::Subject_info::state_name(info.state()),
			                               info.execution_time().value);
			buf += written;
			_buf_len += written;
		}
		_buf[_buf_len++] = 0;

		Genode::log((char const *)_buf);
	}

	static char const *type_name() { return "trace_out"; }
	char const *type() override { return type_name(); }


	Open_result open(char const  *path, unsigned,
	                 Vfs::Vfs_handle **out_handle,
	                 Allocator   &alloc) override
	{
		if (!_single_file(path))
			return OPEN_ERR_UNACCESSIBLE;

		PDBG("OPEN: ", path);
		*out_handle = new (alloc) Vfs_handle(*this, *this, alloc, _buf, _buf_len);
		return OPEN_OK;
	}
};


struct Vfs_trace::Local_factory : File_system_factory
{
	Vfs::Env &_env;
	Content   _content { _env };

	Local_factory(Vfs::Env &env, Xml_node config)
	: _env(env)
	{ }

	Vfs::File_system *create(Vfs::Env&, Xml_node node) override
	{
		PDBG(node);
		if (node.has_type(Content::type_name()))
			return &_content;

		return nullptr;
	}
};

class Vfs_trace::File_system : private Local_factory,
                               public Vfs::Dir_file_system
{
	private:


		typedef String<200> Config;

		static Config _config(Xml_node node)
		{
			char buf[Config::capacity()] { };
			PDBG("node: ", node);
			Xml_generator xml(buf, sizeof(buf), "node", [&] () {
				xml.node("trace_out", [&] () {});
				xml.node("dir", [&] () {
					xml.attribute("name", "test");
					xml.node("dir", [&] () {
						xml.attribute("name", "level2");
					});
				});
				xml.node("dir", [&] () {
					xml.attribute("name", "test");
					xml.node("dir", [&] () {
						xml.attribute("name", "level3");
					});
				});
			});
			PDBG("config: ", Config(Cstring(buf)));
			return Config(Cstring(buf));
		}

	public:


		File_system(Vfs::Env &vfs_env, Genode::Xml_node node)
		:
			Local_factory(vfs_env, node),
			Vfs::Dir_file_system(vfs_env, Xml_node(_config(node).string()), *this)
		{ 
			unlink("test/level2/");
		}

		char const *type() override { PDBG("CALLED"); return "trace"; }

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
			PDBG("called");
			try { return new (vfs_env.alloc())
				Vfs_trace::File_system(vfs_env, node); }
			catch (...) { PDBG("ERROR"); }
			return nullptr;
		}
	};

	static Factory factory;
	return &factory;
}
