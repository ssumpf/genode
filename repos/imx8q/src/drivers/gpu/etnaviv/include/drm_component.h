/*
 * \brief  Server-side DRM session component
 * \author Sebastian Sumpf
 * \author Josef Soentgen
 * \date   2021-04-XX
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef __DRM_COMPONENT_H__
#define __DRM_COMPONENT_H__

#include <root/component.h>
#include <gpu/rpc_object.h>
#include <lx_kit/scheduler.h>

namespace Drm {
	using namespace Genode;

	class Root;
	class Session_component;
}


extern "C" int lx_drm_ioctl(unsigned int, unsigned long);
Genode::Ram_dataspace_capability lx_drm_object_dataspace(unsigned long, unsigned long);


class Drm::Session_component : public Session_rpc_object
{
	public:

		enum { CAP_QUOTA = 8, /* XXX */ };

	private:

		Env                               &_env;

		Genode::Mutex _object_mutex { };
		struct Object_request
		{
			Genode::Ram_dataspace_capability cap;
			unsigned long offset;
			unsigned long size;
			bool pending;

			bool request_valid() const { return offset && size; }

			bool request_resolved() const { return !pending; }
		};

		struct Task_args
		{
			Object_request obj;
			Tx::Sink *sink;
		};

		Task_args _task_args {
			.obj = { Genode::Ram_dataspace_capability(), 0, 0, false},
			.sink = tx_sink() };

		Signal_handler<Session_component> _packet_avail { _env.ep(), *this,
			&Session_component::_handle_signal };
		Signal_handler<Session_component> _ready_to_ack { _env.ep(), *this,
			&Session_component::_handle_signal };
		Lx::Task                          _worker { _run, &_task_args,
			"drm_worker", Lx::Task::PRIORITY_2, Lx::scheduler() };

		static void _drm_request(Tx::Sink &sink)
		{
			while (sink.packet_avail() && sink.ready_to_ack()) {
				Packet_descriptor pkt = sink.get_packet();

				void *arg = sink.packet_content(pkt);
				int err = lx_drm_ioctl((unsigned int)pkt.request(), (unsigned long)arg);
				pkt.error(err);
				sink.acknowledge_packet(pkt);
			}
		}

		static void _run(void *task_args)
		{
			Task_args *args = static_cast<Task_args*>(task_args);

			Tx::Sink       &sink = *args->sink;
			Object_request &obj  = args->obj;

			while (true) {
				_drm_request(sink);
				if (obj.request_valid() && !obj.request_resolved()) {
					obj.cap = lx_drm_object_dataspace(obj.offset, obj.size);
					obj.pending = false;
					obj.offset  = 0;
					obj.size =   0;
				}
				Lx::scheduler().current()->block_and_schedule();
			}
		}

		void _handle_signal()
		{
			/* wake up worker */
			_worker.unblock();
			Lx::scheduler().schedule();
		}

	public:

		Session_component(Env &env, Dataspace_capability tx_ds_cap)
		:
		  Session_rpc_object(env.rm(), tx_ds_cap, env.ep().rpc_ep()), _env(env)
		{
			_tx.sigh_packet_avail(_packet_avail);
			_tx.sigh_ready_to_ack(_ready_to_ack);
		}

		Ram_dataspace_capability object_dataspace(unsigned long offset,
		                                          unsigned long size) override
		{
			Genode::Mutex::Guard mutex_guard(_object_mutex);

			Object_request &obj = _task_args.obj;
			obj.pending = true;
			obj.offset  = offset;
			obj.size    = size;

			_worker.unblock();
			Lx::scheduler().schedule();

			Genode::Ram_dataspace_capability cap = obj.cap;
			obj.cap = Genode::Ram_dataspace_capability();

			return cap;
		}
};


class Drm::Root : public Root_component<Drm::Session_component, Multiple_clients>
{
	private:

		Env       &_env;
		Allocator &_alloc;

	protected:

		Session_component *_create_session(char const *args) override
		{
			size_t tx_buf_size =
				Arg_string::find_arg(args, "tx_buf_size").ulong_value(0);

				return new (_alloc) Session_component(_env, _env.ram().alloc(tx_buf_size));
		}

	public:

		Root(Env &env, Allocator &alloc)
		: Root_component<Session_component, Genode::Multiple_clients>(env.ep(), alloc),
			_env(env), _alloc(alloc)
		{ }
};

#endif /* __DRM_COMPONENT_H__ */
