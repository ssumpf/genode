/*
 * \brief   Fiasco.OC thread garbage collector
 * \author  Stefan Kalkowski
 * \date    2018-06-12
 */

/*
 * Copyright (C) 2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _CORE__INCLUDE__THREAD_COLLECTOR_H_
#define _CORE__INCLUDE__THREAD_COLLECTOR_H_

#include <base/log.h>
#include <base/thread.h>
#include <base/semaphore.h>
#include <core_env.h>

namespace Fiasco {
#include <l4/sys/ipc.h>
}

namespace Core { class Thread_collector; }


/**
 * The thread collector collects threads to be destroyed and
 * destroys them kernel-wise implicitly by deleting the last reference
 */
struct Core::Thread_collector : Genode::Thread
{
	enum { MAX_THREADS = 256, STACK_SIZE = sizeof(long)*1024 };

	Genode::Lock lock {};
	unsigned                  idx = 0;
	Genode::Native_capability garbage[MAX_THREADS];

	Thread_collector()
	: Genode::Thread(Genode::Cpu_session::Weight::DEFAULT_WEIGHT,
	                 "collector", STACK_SIZE,
	                 Genode::Affinity::Location())
	{ start(); }

	void entry()
	{
		using namespace Fiasco;

		for (;;) {
			l4_ipc_sleep(l4_timeout(L4_IPC_TIMEOUT_NEVER,
			                        l4_timeout_rel(1, 20)));
			{
				Genode::Lock::Guard lock_guard(lock);
				while (idx > 0)
					garbage[--idx] = Genode::Native_capability();
			}
		}
	}

	void add(Genode::Native_capability cap)
	{
		Genode::Lock::Guard lock_guard(lock);

		if (idx == MAX_THREADS) {
			Genode::error("Thread garbage collector's array is full!");
			return;
		}

		garbage[idx++] = cap;
	}
};

#endif /* _CORE__INCLUDE__THREAD_COLLECTOR_H_ */
