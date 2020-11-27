/*
 * \brief  Fiasco.OC pager framework
 * \author Norman Feske
 * \author Christian Helmuth
 * \author Stefan Kalkowski
 * \date   2006-07-14
 */

/*
 * Copyright (C) 2006-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <base/env.h>
#include <base/log.h>

/* core includes */
#include <pager.h>

/* base-internal includes */
#include <base/internal/native_thread.h>

/* Fiasco.OC includes */
#include <foc/syscall.h>

using namespace Genode;


void Pager_entrypoint::entry()
{
	bool reply_pending = false;
	while (1) {

		if (reply_pending)
			_pager.reply_and_wait_for_fault();
		else
			_pager.wait_for_fault();

		reply_pending = false;

		apply(_pager.badge(), [&] (Pager_object *obj) {

			/* the pager_object might be destroyed, while we got the message */
			if (!obj) {
				warning("no pager object found!");
				return;
			}

			switch (_pager.msg_type()) {

			case Ipc_pager::PAGEFAULT:
			case Ipc_pager::EXCEPTION:
				{
					if (_pager.exception()) {
						Mutex::Guard guard(obj->state.mutex);
						_pager.get_regs(obj->state.state);
						obj->state.exceptions++;
						obj->state.in_exception = true;
						obj->submit_exception_signal();
						return;
					}

					/* handle request */
					if (obj->pager(_pager)) {
						/* could not resolv - leave thread in pagefault */
						warning("page-fault, ", *obj,
						        " ip=", Hex(_pager.fault_ip()),
						        " pf-addr=", Hex(_pager.fault_addr()));
					} else {
						_pager.set_reply_dst(Native_thread(obj->badge()));
						reply_pending = true;
						return;
					}
					break;
				}

			case Ipc_pager::WAKE_UP:
				{
					/*
					 * We got a request from one of cores region-manager sessions
					 * to answer the pending page fault of a resolved region-manager
					 * client, or to resume a previously paused thread. Hence, we
					 * have to send a reply to the specified thread and answer the
					 * call.
					 */

					/* send reply to the caller */
					_pager.set_reply_dst(Native_thread());
					_pager.acknowledge_wakeup();

					{
						Mutex::Guard guard(obj->state.mutex);
						/* revert exception flag */
						obj->state.in_exception = false;
						/* set new register contents */
						_pager.set_regs(obj->state.state);
					}

					/* send wake up message to requested thread */
					_pager.set_reply_dst(Native_thread(obj->badge()));
					_pager.acknowledge_exception();
					break;
				}

			/*
			 * Handle exceptions that are artificially generated by the pause
			 * function of the CPU service.
			 */
			case Ipc_pager::PAUSE:
				{
					Mutex::Guard guard(obj->state.mutex);
					_pager.get_regs(obj->state.state);
					obj->state.exceptions++;
					obj->state.in_exception = true;

					/*
					 * It might occur that the thread raises an exception,
					 * after it already got resumed by the cpu_session, in
					 * that case we unblock it immediately.
					 */
					if (!obj->state.paused) {
						_pager.set_reply_dst(Native_thread(obj->badge()));
						reply_pending = true;
					}
					break;
				}

			default:
				error("got unknown message type ", Hex(_pager.msg_type()));
			}
		});
	};
}


void Pager_entrypoint::dissolve(Pager_object &obj)
{
	/* cleanup at cap session */
	_cap_factory.free(obj.Object_pool<Pager_object>::Entry::cap());

	remove(&obj);
}


Pager_capability Pager_entrypoint::manage(Pager_object &obj)
{
	using namespace Foc;

	Native_capability cap(_cap_factory.alloc(Thread::_thread_cap));

	/* add server object to object pool */
	obj.cap(cap);
	insert(&obj);

	/* return capability that uses the object id as badge */
	return reinterpret_cap_cast<Pager_object>(cap);
}
