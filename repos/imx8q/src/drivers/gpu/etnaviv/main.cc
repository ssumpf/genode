/*
 * \brief  i.MX8 GPU driver Linux port
 * \author Josef Soentgen
 * \date   2021-03-08
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <base/component.h>
#include <lx_kit/init.h>

namespace Gpu {
	using namespace Genode;
	struct Main;
}


struct Gpu::Main
{
	Env & env;

	Heap  heap { env.ram(), env.rm() };

	Main(Env & env) : env(env)
	{
		Lx_kit::initialize(env, heap);
	}
};


void Component::construct(Genode::Env &env)
{
	static Gpu::Main main(env);
}
