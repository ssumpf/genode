/*
 * \brief  Terminal file system
 * \author Christian Prochaska
 * \author Norman Feske
 * \author Christian Helmuth
 * \date   2012-05-23
 */

/*
 * Copyright (C) 2012-2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__VFS__TERMINAL_FILE_SYSTEM_H_
#define _INCLUDE__VFS__TERMINAL_FILE_SYSTEM_H_

/* Genode includes */
#include <base/registry.h>
#include <base/signal.h>
#include <terminal_session/connection.h>
#include <util/xml_generator.h>
#include <vfs/device_file_system.h>
#include <vfs/readonly_value_file_system.h>


namespace Vfs { class Terminal_file_system; }


class Vfs::Terminal_file_system : public Device_file_system
{
	private:

		Terminal_file_system(Terminal_file_system const &);
		Terminal_file_system &operator = (Terminal_file_system const &);

		typedef Genode::String<64> Label;
		Label _label;
		typedef Genode::String<64> Name;
		Label _name;

		Vfs::Env               &_env;
		Io_response_handler    &_io_handler;
		Watch_response_handler &_watch_handler;

		Terminal::Connection _terminal { _env.env(), _label.string() };

		struct Terminal_vfs_file_handle : public Device_vfs_handle
		{
			Terminal::Connection &_terminal;

			Terminal_vfs_file_handle(Directory_service    &ds,
			                    File_io_service      &fs,
			                    Genode::Allocator    &alloc,
			                    Terminal::Connection &terminal,
			                    int flags)
			: Device_vfs_handle(ds, fs, alloc, flags), _terminal(terminal) { }

			Read_result read(char *dst, file_size count, file_size &out_count)
			{
				if (_terminal.avail()) {
					out_count = _terminal.read(dst, count);
					return READ_OK;
				} else {
					return READ_QUEUED;
				}
			}

			Write_result write(char const *buf, file_size buf_size, file_size &out_count)
			{
				out_count = _terminal.write(buf, buf_size);
				return WRITE_OK;
			}

			bool read_ready() { return _terminal.avail(); }
		};

		typedef Genode::Registered<Terminal_vfs_file_handle> Registered_handle;
		typedef Genode::Registry<Registered_handle>          Handle_registry;

		struct Post_signal_hook : Genode::Entrypoint::Post_signal_hook
		{
			Genode::Entrypoint  &_ep;
			Io_response_handler &_io_handler;
			Vfs_handle::Context *_context = nullptr;

			Post_signal_hook(Genode::Entrypoint &ep,
			                 Io_response_handler &io_handler)
			: _ep(ep), _io_handler(io_handler) { }

			void arm(Vfs_handle::Context *context)
			{
				_context = context;
				_ep.schedule_post_signal_hook(this);
			}

			void function() override
			{
				/*
				 * XXX The current implementation executes the post signal hook
				 *     for the last armed context only. When changing this,
				 *     beware that the called handle_io_response() may change
				 *     this object in a signal handler.
				 */

				_io_handler.handle_io_response(_context);
				_context = nullptr;
			}

			private:

				/*
				 * Noncopyable
				 */
				Post_signal_hook(Post_signal_hook const &);
				Post_signal_hook &operator = (Post_signal_hook const &);
		};

		Post_signal_hook _post_signal_hook { _env.env().ep(), _io_handler };

		Handle_registry _handle_registry { };

		Genode::Io_signal_handler<Terminal_file_system> _read_avail_handler {
			_env.env().ep(), *this, &Terminal_file_system::_handle_read_avail };

		void _handle_read_avail()
		{
			_handle_registry.for_each([this] (Registered_handle &h) {
				_post_signal_hook.arm(h.context);
			});
		}

		using Config = Genode::String<256>;
		static Config _dir_config(Genode::Xml_node node)
		{
			char buf[Config::capacity()] { };

			Genode::Xml_generator xml(buf, sizeof(buf), "dir", [&] {

				using Name = Genode::String<64>;
				Name dir_name = node.attribute_value("name", Name(name()));

				xml.attribute("name", Name(".", dir_name));

				xml.node("readonly_value", [&] {
					xml.attribute("name", "window_size");
				});
			});
			return Config(Genode::Cstring(buf));
		}

		using Wsize = Terminal::Session::Size;
		Readonly_value_file_system<Wsize> _window_size_fs {
			_env, "window_size", Wsize(0, 0) };

		Vfs::File_system *create(Vfs::Env &, Genode::Xml_node node) override
		{
			if (node.has_type(Readonly_value_file_system<Wsize>::type_name())) {
				return _window_size_fs.matches(node) ? &_window_size_fs : nullptr;
			}

			return nullptr;
		}

		Genode::Io_signal_handler<Terminal_file_system> _size_changed_handler {
			_env.env().ep(), *this, &Terminal_file_system::_handle_size_changed };

		void _handle_size_changed()
		{
			_window_size_fs.value(_terminal.size());
		}

	public:

		Terminal_file_system(Vfs::Env &env, Genode::Xml_node config)
		:
			Device_file_system(NODE_TYPE_CHAR_DEVICE, name(), config),
			_label(config.attribute_value("label", Label())),
			_name(config.attribute_value("name", Name(name()))),
			_env(env), _io_handler(env.io_handler()),
			_watch_handler(env.watch_handler())
		{
			Device_file_system::construct(env, Genode::Xml_node(_dir_config(config).string()), *this);

			/* register for read-avail notification */
			_terminal.read_avail_sigh(_read_avail_handler);

			/* register for size-change notification */
			_terminal.size_changed_sigh(_size_changed_handler);
			_handle_size_changed();
		}

		static const char *name()   { return "terminal"; }
		char const *type() override { return "terminal"; }

		/*********************************
		 ** Directory service interface **
		 *********************************/

		Open_result open(char const  *path, unsigned flags,
		                 Vfs_handle **out_handle,
		                 Allocator   &alloc) override
		{
			try {
				if (_device_file(path)) {
					*out_handle = new (alloc)
						Registered_handle(_handle_registry, *this, *this,
						                  alloc, _terminal, flags);
					return OPEN_OK;
				} else

				if (_device_dir_file(path)) {
					return Device_file_system::open(path, 0, out_handle, alloc);
				}
			}
			catch (Genode::Out_of_ram)  { return OPEN_ERR_OUT_OF_RAM; }
			catch (Genode::Out_of_caps) { return OPEN_ERR_OUT_OF_CAPS; }

			return OPEN_ERR_UNACCESSIBLE;
		}

		/********************************
		 ** File I/O service interface **
		 ********************************/

		Ftruncate_result ftruncate(Vfs_handle *, file_size) override
		{
			return FTRUNCATE_OK;
		}

		bool check_unblock(Vfs_handle *vfs_handle, bool rd, bool wr, bool) override
		{
			Device_vfs_handle *handle =
				static_cast<Device_vfs_handle*>(vfs_handle);

			if (rd && handle->read_ready()) { return true; }
			if (wr)                         { return true; }

			return false;
		}

		void register_read_ready_sigh(Vfs_handle *,
		                              Signal_context_capability sigh) override
		{
			_terminal.read_avail_sigh(sigh);
		}

};

#endif /* _INCLUDE__VFS__TERMINAL_FILE_SYSTEM_H_ */
