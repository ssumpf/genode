/*
 * \brief  Service providing the 'Terminal_session' interface for a Linux file
 * \author Josef Soentgen
 * \author Sebastian Sumpf
 * \date   2020-07-09
 */

/*
 * Copyright (C) 2020 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__DRIVERS__USB_MODEM__TERMINAL_H_
#define _SRC__DRIVERS__USB_MODEM__TERMINAL_H_

/* Genode includes */
#include <base/attached_ram_dataspace.h>
#include <base/log.h>
#include <os/session_policy.h>
#include <root/component.h>
#include <terminal_session/terminal_session.h>

#include <lx_kit/scheduler.h>

namespace Terminal {
	class Session_component;
	class Root;
}

extern "C" {
	struct usb_class_driver;
}

class Terminal::Session_component : public Genode::Rpc_object<Session, Session_component>
{
	using size_t = Genode::size_t;

	private:

		Genode::Attached_ram_dataspace    _io_buffer;
		Genode::Signal_context_capability _read_avail_sigh { };

		size_t  _data_avail { 0 };
		size_t   _io_buffer_size;

		usb_class_driver *_class_driver;

		static void _run_wdm_task(void *args);

		Lx::Task _task { _run_wdm_task, _class_driver, "wdm_task",
		                 Lx::Task::PRIORITY_1, Lx::scheduler() };

	public:

		Session_component(Genode::Env &env,
		                  Genode::size_t io_buffer_size,
		                  usb_class_driver *class_driver)
		:
			_io_buffer(env.ram(), env.rm(), io_buffer_size),
			_io_buffer_size(io_buffer_size),
			_class_driver(class_driver)
		{
			if (_class_driver == nullptr) {
				Genode::error("No class driver for terminal");
				throw Genode::Service_denied();
			}

			_task.unblock();
			Lx::scheduler().schedule();
		}

		/********************************
		 ** Terminal session interface **
		 ********************************/

		Size size() override { return Size(0, 0); }

		bool avail() override
		{
			return _data_avail > 0;
		}

		Genode::size_t _read(Genode::size_t dst_len)
		{
			Genode::log(__func__, " ", dst_len, " bytes");
			return 0;
		}

		Genode::size_t _write(Genode::size_t num_bytes)
		{
			Genode::log(__func__, " ", num_bytes, " bytes");
			return 0;
		}

		Genode::Dataspace_capability _dataspace()
		{
			return _io_buffer.cap();
		}

		void read_avail_sigh(Genode::Signal_context_capability sigh) override
		{
			Genode::warning(__func__);
			_read_avail_sigh = sigh;
		}

		void connected_sigh(Genode::Signal_context_capability sigh) override
		{
			Genode::Signal_transmitter(sigh).submit();
	}

		void size_changed_sigh(Genode::Signal_context_capability) override { }

		size_t read(void *, size_t) override { return 0; }
		size_t write(void const *, size_t) override { return 0; }
};


class Terminal::Root : public Genode::Root_component<Session_component>
{
	private:

		Genode::Env      &_env;
		usb_class_driver *_class_driver { nullptr };

	protected:

		Session_component *_create_session(const char *args) override
		{
			Genode::size_t const io_buffer_size = 4096ul;
			Genode::log(__func__, ": ", args);
			return new (md_alloc())
			       Session_component(_env, io_buffer_size, _class_driver);
		}

	public:

		/**
		 * Constructor
		 */
		Root(Genode::Env       &env,
		     Genode::Allocator &md_alloc)
		:
			Genode::Root_component<Session_component>(&env.ep().rpc_ep(), &md_alloc),
			_env(env)
		{ }

		void class_driver(usb_class_driver *class_driver) { _class_driver = class_driver; }
};

#endif /* _SRC__DRIVERS__USB_MODEM__TERMINAL_H_ */
