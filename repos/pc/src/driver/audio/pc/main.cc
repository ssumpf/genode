/*
 * \brief  Linux sound driver (Intel HDA)
 * \author Sebastian Sumpf
 * \date   2022-05-04
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <base/component.h>
#include <base/env.h>

#include <lx_emul/init.h>
#include <lx_kit/env.h>
#include <lx_kit/init.h>
#include <lx_kit/initial_config.h>

#include "audio.h"

using namespace Genode;

extern "C" void lx_emul_module_params(void);


extern "C" int lx_emul_acpi_table(const char * const name, void *ctx,
                                  void (*fn) (void *ctx,
                                              unsigned long addr,
                                              unsigned long size))
{
	using namespace Lx_kit;
	using namespace Genode;

	int found = 0;
	env().devices.for_each([&] (Device &d) {
		if (d.name() != name)
		return;

		found = 1;
		d.for_each_io_mem([&] (Device::Io_mem &io_mem) {
			log("Found NHLT: ", Hex(io_mem.addr), " size: ", io_mem.size);
			fn(ctx, io_mem.addr, io_mem.size); });
	});

	return found;
}


struct Main
{
	Env &env;
	Heap heap { env.ram(), env.rm() };

	Signal_handler<Main> scheduler_handler { env.ep(), *this, &Main::handle_scheduler };

	Main(Env & env) : env(env)
	{
		Lx_kit::initialize(env, scheduler_handler);

		lx_emul_module_params();

		genode_audio_init(genode_env_ptr(env),
		                  genode_allocator_ptr(heap));

		lx_emul_start_kernel(nullptr);
	};

	void handle_scheduler()
	{
		Lx_kit::env().scheduler.execute();
	}
};


void Component::construct(Env & env)
{
	static Main main(env);
}
