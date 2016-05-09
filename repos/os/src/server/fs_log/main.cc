/*
 * \brief  Server that writes log messages to a file system.
 * \author Emery Hemingway
 * \date   2015-05-13
 */

/*
 * Copyright (C) 2015-2016 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

/* Genode includes */
#include <os/path.h>
#include <file_system_session/connection.h>
#include <file_system/util.h>
#include <root/component.h>
#include <os/server.h>
#include <os/session_policy.h>
#include <base/printf.h>

/* Local includes */
#include "session.h"

namespace Fs_log {

	using namespace Genode;
	using namespace File_system;

	class  Root_component;
	struct Main;

	enum {
		PACKET_SIZE = Log_session::String::MAX_SIZE,
		 QUEUE_SIZE = File_system::Session::TX_QUEUE_SIZE,
		TX_BUF_SIZE = PACKET_SIZE * (QUEUE_SIZE+2)
	};

	typedef Genode::Path<File_system::MAX_PATH_LEN> Path;

}


class Fs_log::Root_component :
	public Genode::Root_component<Fs_log::Session_component>
{
	private:

		Allocator_avl            _write_alloc;
		File_system::Connection  _fs;

	protected:

		Session_component *_create_session(const char *args)
		{
			using namespace File_system;

			size_t ram_quota = Arg_string::find_arg(args, "ram_quota").ulong_value(0);
			if (ram_quota < sizeof(Session_component))
				throw Root::Quota_exceeded();

			typedef Genode::Path<128> Label_path;
			Label_path dir_path;
			char file_name[MAX_NAME_LEN];

			Session_label session_label(args);
			char const *label_str = session_label.string();
			char const *label_prefix = "";
			bool truncate = false;

			try {
				Session_policy policy(session_label);
				truncate = policy.attribute_value("truncate", truncate);
				bool merge = policy.attribute_value("merge", false);

				/* only a match on 'label_prefix' can be merged */
				if (merge && policy.has_type("policy")
				 && (!(policy.has_attribute("label")
				    || policy.has_attribute("label_suffix"))))
				{
					/*
					 * split the label between what will be the log file
					 * and what will be prepended to messages in the file
					 */
					size_t offset = policy.attribute("label_prefix").value_size();
					for (size_t i = offset; i < session_label.length()-4; ++i) {
						if (strcmp(label_str+i, " -> ", 4))
							continue;

						label_prefix = label_str+i+4;
						{
							char tmp[128];
							strncpy(tmp, label_str, min(sizeof(tmp), i+1));
							dir_path = path_from_label<Label_path>(tmp);
						}
						break;
					}
					if (dir_path == "/")
						dir_path = path_from_label<Label_path>(label_str);

				} else if (!policy.has_type("default-policy")) {
					dir_path = path_from_label<Label_path>(label_str);
				}

			} catch (Session_policy::No_policy_defined) {
				dir_path = path_from_label<Label_path>(label_str);
			}

			if (dir_path == "/") {
				strncpy(file_name, "log", sizeof(file_name));
				label_prefix = label_str;
			} else {
				dir_path.append(".log");
				strncpy(file_name, dir_path.last_element(), sizeof(file_name));
				dir_path.strip_last_element();
				dir_path.remove_trailing('/');
			}

			try {

				Dir_handle   dir_handle = ensure_dir(_fs, dir_path.base());
				Handle_guard dir_guard(_fs, dir_handle);
				File_handle  handle;

				try {
					handle = _fs.file(dir_handle, file_name,
					                  File_system::WRITE_ONLY, false);

					/* don't truncate at every new child session */
					if (truncate && (strcmp(label_prefix, "") == 0))
						_fs.truncate(handle, 0);

				} catch (File_system::Lookup_failed) {
					handle = _fs.file(dir_handle, file_name,
					                  File_system::WRITE_ONLY, true);
				}

				return new (md_alloc()) Session_component(_fs, handle, label_prefix);

			} catch (Permission_denied) {
				dir_path.append("/"); dir_path.append(file_name);
				PERR("%s: permission denied", dir_path.base());

			} catch (No_space) {
				PERR("file system out of space");

			} catch (Out_of_metadata) {
				PERR("file system server out of metadata");

			} catch (Invalid_name) {
				dir_path.append("/"); dir_path.append(file_name);
				PERR("%s: invalid path", dir_path.base());

			} catch (Name_too_long) {
				dir_path.append("/"); dir_path.append(file_name);
				PERR("%s: name too long", dir_path.base());

			} catch (...) {
				dir_path.append("/"); dir_path.append(file_name);
				PERR("cannot open log file %s", dir_path.base());
				throw;
			}

			throw Root::Unavailable();
		}

	public:

		/**
		 * Constructor
		 */
		Root_component(Server::Entrypoint &ep, Allocator &alloc)
		:
			Genode::Root_component<Session_component>(&ep.rpc_ep(), &alloc),
			_write_alloc(env()->heap()),
			_fs(_write_alloc, TX_BUF_SIZE)
		{
			/* fill the ack queue with packets so sessions never need to alloc */
			File_system::Session::Tx::Source &source = *_fs.tx();
			for (int i = 0; i < QUEUE_SIZE; ++i)
				source.submit_packet(source.alloc_packet(PACKET_SIZE));
		}

};

struct Fs_log::Main
{
	Server::Entrypoint &ep;

	Sliced_heap sliced_heap = { env()->ram_session(), env()->rm_session() };

	Root_component root { ep, sliced_heap };

	Main(Server::Entrypoint &ep)
	: ep(ep)
	{ Genode::env()->parent()->announce(ep.manage(root)); }
};


/************
 ** Server **
 ************/

namespace Server {

	char const* name() { return "fs_log_ep"; }

	size_t stack_size() { return 3*512*sizeof(long); }

	void construct(Entrypoint &ep) { static Fs_log::Main inst(ep); }

}
