/*
 * \brief   Platform implementations specific for x86
 * \author  Norman Feske
 * \author  Reto Buerki
 * \date    2013-04-05
 *
 * XXX dimension allocators according to the available physical memory
 */

/*
 * Copyright (C) 2013-2015 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

/* core includes */
#include <platform.h>
#include <board.h>
#include <cpu.h>

using namespace Genode;

Cpu::User_context::User_context() { PDBG("not impl"); }


Native_region * Platform::_ram_regions(unsigned const i)
{
	PDBG("not impl");
	static Native_region _regions[] =
	{
	};
	return i < sizeof(_regions)/sizeof(_regions[0]) ? &_regions[i] : 0;
}


Native_region * Platform::_core_only_mmio_regions(unsigned const i)
{
	PDBG("not impl");
	static Native_region _regions[] =
	{
	};
	return i < sizeof(_regions)/sizeof(_regions[0]) ? &_regions[i] : 0;
}


void Platform::_init_io_port_alloc()
{
	PDBG("not impl");
}


void Platform::_init_io_mem_alloc()
{
	PDBG("not impl");
}


long Platform::irq(long const user_irq)
{
	PDBG("not impl");
	return 0;
}
