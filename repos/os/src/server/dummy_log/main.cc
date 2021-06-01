/*
 * \brief  Server that writes log messages into the void
 * \author Josef Soentgen
 * \date   2021-06-01
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <base/attached_rom_dataspace.h>
#include <base/component.h>
#include <base/heap.h>
#include <base/heap.h>
#include <base/log.h>
#include <log_session/log_session.h>
#include <os/session_policy.h>
#include <root/component.h>


namespace Dummy_log {

	using namespace Genode;

	class Session_component;
	class Root_component;
}


class Dummy_log::Session_component : public Genode::Rpc_object<Genode::Log_session>
{
	public:

		Session_component() { }

		~Session_component() { }


		/*****************
		 ** Log session **
		 *****************/

		void write(Log_session::String const &msg) override
		{
			using namespace Genode;

			if (!msg.valid_string()) {
				Genode::error("received corrupted string");
				return;
			}
		}
};


class Dummy_log::Root_component : public Genode::Root_component<Dummy_log::Session_component>
{
	protected:

		Session_component *_create_session(const char *) override
		{
			try {
				return new (md_alloc()) Session_component();
			} catch (...) { }

			throw Service_denied();
		}

	public:

		/**
		 * Constructor
		 */
		Root_component(Genode::Env &env, Genode::Allocator &md_alloc)
		:
			Genode::Root_component<Session_component>(&env.ep().rpc_ep(), &md_alloc)
		{
			env.parent().announce(env.ep().manage(*this));
		}

};


void Component::construct(Genode::Env &env)
{
	static Genode::Sliced_heap sliced_heap { env.ram(), env.rm() };
	static Dummy_log::Root_component root { env, sliced_heap };
}
