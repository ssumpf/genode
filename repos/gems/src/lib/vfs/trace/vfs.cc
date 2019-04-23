
/* Genode includes */
#include <base/attached_rom_dataspace.h>
#include <vfs/dir_file_system.h>
#include <vfs/single_file_system.h>


#include <gems/vfs.h>
#include <util/xml_generator.h>

#include <trace_session/connection.h>

#include "directory_tree.h"
#include "value_file_system.h"

#include <base/debug.h>

namespace Vfs_trace {

	using namespace Vfs;
	using namespace Genode;

	struct File_system;
	class  Local_factory;
	class  Subject;
	struct Subject_factory;
	class  Trace_buffer_file_system;
}


class Vfs_trace::Trace_buffer_file_system : public Single_file_system
{
	private:

		typedef String<32> Config;

		static Config _config(Xml_node node)
		{
			char buf[Config::capacity()] { };

			Xml_generator xml(buf, sizeof(buf), type(), [&] () { });

			return Config(Cstring(buf));
		}

	public:

		Trace_buffer_file_system()
		: Single_file_system(NODE_TYPE_CHAR_DEVICE,
		                     type(), Xml_node(_config(name.string()),
		  _file_name(name) { }

		static char const *type_name() { return "trace_buffer"; }
		char const *type() override { return type_name(); }

};

struct Vfs_trace::Subject_factory : File_system_factory
{
	Vfs::Env                   &_env;
	Value_file_system<bool, 1>  _enabled_fs { _env, "enable", 0u};

	Subject_factory(Vfs::Env &env)
	: _env(env) { }

	Vfs::File_system *create(Vfs::Env &env, Xml_node node) override
	{
		if (node.has_type(Value_file_system<unsigned>::type_name()))
			return _enabled_fs.matches(node)   ? &_enabled_fs : nullptr;

		return nullptr;
	}
};


class Vfs_trace::Subject : private Subject_factory,
                           public  Vfs::Dir_file_system
{
	private:

		typedef String<200> Config;

		Trace::Connection &_trace;
		Trace::Policy_id   _policy;
		Trace::Subject_id  _id;

		Watch_handler<Subject> _enable_handler {
		  _enabled_fs, "/enable",
		  Subject_factory::_env.alloc(),
		  *this, &Subject::_enable_subject };


		static Config _config(Xml_node node)
		{
			char buf[Config::capacity()] { };

			Xml_generator xml(buf, sizeof(buf), "dir", [&] () {
				typedef String<32> Name;
				xml.attribute("name", node.attribute_value("name", Name()));
				xml.node("value", [&] () { xml.attribute("name", "enable"); });
			});

			return Config(Cstring(buf));
		}

		void _setup_and_trace() { }

		/********************
		 ** Watch handlers **
		 ********************/

		enum State { OFF, TRACE, PAUSED } _state { OFF };

		void _enable_subject()
		{
			if (_enabled_fs.value()) {
				switch (_state) {
					case TRACE:  break;
					case OFF:    _setup_and_trace(); break;
					case PAUSED: _trace.resume(_id); break;
				}
				_state = TRACE;
			} else {
				switch (_state) {
					case OFF:    return;
					case PAUSED: return;
					case TRACE:  _trace.pause(_id); _state = PAUSED; return;
				}
			}
		}

	public:

		Subject(Vfs::Env &env, Trace::Connection &trace,
		        Trace::Policy_id policy, Xml_node node)
		: Subject_factory(env),
		  Dir_file_system(env, Xml_node(_config(node).string()), *this),
		  _trace(trace),
		  _policy(policy),
		  _id(node.attribute_value("id", 0u))
		{ }


		static char const *type_name() { return "trace_node"; }
		char const *type() override { return type_name(); }
};


struct Vfs_trace::Local_factory : File_system_factory
{
	Vfs::Env          &_env;

	enum { MAX_SUBJECTS = 32 };
	Trace::Connection  _trace { _env.env(), 32*4096, 64*1024, 0 };
	Trace::Subject_id  _subjects[MAX_SUBJECTS];
	unsigned           _subject_count;
	Trace::Policy_id   _policy_id;

	Directory_tree     _tree { _env.alloc() };

	void _install_null_policy()
	{
		using namespace Genode;
		Constructible<Attached_rom_dataspace> null_policy;

		try {
			null_policy.construct(_env.env(), "null");
			_policy_id = _trace.alloc_policy(null_policy->size());
		} catch (Out_of_caps) { error("out of CAPS"); throw; }
			catch (Out_of_ram)  { error(" out of RAM"); throw; }
			catch (...) {
				error("failed to attach 'null' trace policy."
			        "Please make sure it is provided as a ROM module.");
				throw;
		}

		/* copy policy into trace session */
		void *dst = _env.env().rm().attach(_trace.policy(_policy_id));
		memcpy(dst, null_policy->local_addr<void*>(), null_policy->size());
		_env.env().rm().detach(dst);
	}

	Local_factory(Vfs::Env &env, Xml_node config)
	: _env(env)
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

		for (unsigned i = 0; i < _subject_count; i++) {
			_tree.insert(_trace.subject_info(_subjects[i]), _subjects[i]);
		}

		_install_null_policy();
	}

	Vfs::File_system *create(Vfs::Env&, Xml_node node) override
	{
		PDBG(node);
		if (node.has_type(Subject::type_name()))
			return new (_env.alloc()) Subject(_env, _trace, Trace::Policy_id(), node);

		return nullptr;
	}
};


class Vfs_trace::File_system : private Local_factory,
                               public  Vfs::Dir_file_system
{
	private:

		typedef String<512*1024> Config;

		static char const *_config(Vfs::Env &vfs_env, Directory_tree &tree)
		{
			char *buf = (char *)vfs_env.alloc().alloc(Config::capacity());
			Xml_generator xml(buf, Config::capacity(), "node", [&] () {
				tree.xml(xml);
			});

			PDBG("config: ",(char const *)buf);
			return buf;
		}

	public:

		File_system(Vfs::Env &vfs_env, Genode::Xml_node node)
		: Local_factory(vfs_env, node),
			Vfs::Dir_file_system(vfs_env, Xml_node(_config(vfs_env, _tree)), *this)
		{ }

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
			PDBG("called: ", node);
			try { return new (vfs_env.alloc())
				Vfs_trace::File_system(vfs_env, node); }
			catch (...) { PDBG("ERROR"); }
			return nullptr;
		}
	};

	static Factory factory;
	return &factory;
}
