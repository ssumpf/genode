/*
 * \brief  Linux emulation environment specific to this driver - VBT IO_MEM
 * \author Alexander Boettcher
 * \date   2022-01-21
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */


#include <base/log.h>
#include <lx_kit/env.h>
#include <base/attached_io_mem_dataspace.h>


extern "C" void * lx_emul_vbt_io_mem_map(unsigned long offset, unsigned long size);
extern "C" void * lx_emul_vbt_io_mem_map(unsigned long offset, unsigned long size)
{
	using namespace Genode;

	static Constructible<Attached_io_mem_dataspace> opregion;

	addr_t paddr = offset & ~0xfffUL;
	addr_t psize = size + (offset & 0xfff);

	if (opregion.constructed()) {
		error("unexpected reconstruction of ACPI opregion for VBT");
		return nullptr;
	}

	try {
		opregion.construct(Lx_kit::env().env, paddr, psize);
		return opregion->local_addr<char>() + (offset & 0xfff);
	} catch (...) {
		error("exception during ACPI opregion for VBT");
	}

	return nullptr;
}
