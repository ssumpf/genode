/**
 * \brief  Lx_kit backend for Linux kernel initialization
 * \author Stefan Kalkowski
 * \date   2021-03-10
 */

#include <base/log.h>

#include <lx_kit/env.h>
#include <lx_kit/init.h>
#include <lx_emul/init.h>

#include <lx_kit/malloc.h>
#include <lx_kit/timer.h>
#include <lx_kit/irq.h>
#include <lx_kit/scheduler.h>
#include <lx_kit/work.h>

namespace Lx_kit { class Initcalls; }


void Lx_kit::Initcalls::add(int (*initcall)(void), unsigned int prio) {
	_call_list.insert(new (_heap) E(prio, initcall)); }


void Lx_kit::Initcalls::execute_in_order()
{
	enum Initcall_prios { PURE = 0, LATE_SYNC = 14, MAX };

	for (unsigned i = PURE; i < MAX; i++) {
		for (E * entry = _call_list.first(); entry; entry = entry->next()) {
			if (entry->prio == i) {
				Genode::log("Call: ", entry->call);
				entry->call();
				Genode::log("Call: ", entry->call, " done");
			}
		}
	}
}


static unsigned long _jiffies;


static void _run_linux(void *args)
{
	Lx_kit::Env &kit_env = *reinterpret_cast<Lx_kit::Env*>(args);

	lx_emul_init_kernel();

	kit_env.initcalls.execute_in_order();
	if (lx_emul_start_kernel()) {
		Genode::error(__func__, ": lx_emul_start_kernel failed");
	}

	while (1) {
		Lx::scheduler().current()->block_and_schedule();
	}
}


void Lx_kit::initialize(Genode::Env & env, Genode::Allocator &alloc)
{
	static Genode::Constructible<Lx::Task> _linux { };


	Lx_kit::Env & kit_env = Lx_kit::env(&env);
	env.exec_static_constructors();

	Lx::malloc_init(env, alloc);
	Lx::scheduler(&env);
	Lx::Irq::irq(&env.ep(), &alloc);
	unsigned hz = 250; // XXX
	Lx::timer(&env, &env.ep(), &alloc,
                     &_jiffies, &hz);
	Lx::Work::work_queue(&alloc);

	_linux.construct(_run_linux, reinterpret_cast<void*>(&kit_env),
	                 "linux", Lx::Task::PRIORITY_0, Lx::scheduler());

	Lx::scheduler().schedule();
}


extern "C" void lx_emul_register_initcall(int (*initcall)(void), int prio)
{
	Genode::error(__func__, ": ", initcall);
	Lx_kit::env().initcalls.add(initcall, prio);
}
