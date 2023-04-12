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


struct Main
{
	Env &env;
	Heap heap { env.ram(), env.rm() };

	Main(Env & env) : env(env)
	{
		Lx_kit::initialize(env);

		lx_emul_module_params();

		env.exec_static_constructors();

		genode_audio_init(genode_env_ptr(env),
		                  genode_allocator_ptr(heap));

		lx_emul_start_kernel(nullptr);
	};
};


void Component::construct(Env & env)
{
	static Main main(env);
}
