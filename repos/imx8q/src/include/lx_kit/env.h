/**
 * \brief  Globally available Lx_kit environment, needed in the C-ish lx_emul
 * \author Stefan Kalkowski
 * \date   2021-03-17
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#pragma once

#include <base/env.h>
#include <lx_kit/init.h>

namespace Lx_kit {
	using namespace Genode;

	struct Env;

	/**
	 * Returns the global Env object available
	 *
	 * \param env - pointer to Genode::Env used to construct object initially
	 */
	Env & env(Genode::Env * env = nullptr);
}


struct Lx_kit::Env
{
	Genode::Env  & env;
	Genode::Heap   heap      { env.ram(), env.rm() };
	Initcalls      initcalls { heap                };

	Env(Genode::Env & env) : env(env) { }
};
