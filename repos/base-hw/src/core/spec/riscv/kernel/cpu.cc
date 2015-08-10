/*
 * \brief   Class for kernel data that is needed to manage a specific CPU
 * \author  Martin Stein
 * \author  Stefan Kalkowski
 * \date    2014-01-14
 */

/*
 * Copyright (C) 2014 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

/* core includes */
#include <kernel/cpu.h>
#include <kernel/pd.h>

using namespace Kernel;

extern int _mt_begin, _mt_end;

struct Mstatus : Genode::Register<64>
{
	enum {
		USER       = 0,
		SUPERVISOR = 1,
		MACHINE    = 3,
		Sv39       = 9,
	};
	struct Ie   : Bitfield<0, 1> { };
	struct Priv : Bitfield<1, 2> { };
	struct Ie1  : Bitfield<3, 1> { };
	struct Priv1 : Bitfield<4, 2> { };
	struct Vm   : Bitfield<17, 5> { };
	struct Mprv : Bitfield<16, 1> { };
};


void Genode::Cpu::init_virt_kernel(Kernel::Pd * pd)
{
	/* read status register */
	Mstatus::access_t mstatus;
	asm volatile ("csrr %0, mstatus\n" : "=r"(mstatus));

	Mstatus::Ie::set(mstatus, 0);                     /* disable interrupts  */
	Mstatus::Priv::set(mstatus, Mstatus::SUPERVISOR); /* set supervisor mode */
	Mstatus::Vm::set(mstatus, Mstatus::Sv39);         /* enable Sv39 paging  */
	Mstatus::Ie1::set(mstatus, 1);
	Mstatus::Priv1::set(mstatus, Mstatus::USER);      /* set user mode */

	asm volatile ("csrw sptbr, %0  \n" /* set page table */
	              "csrw mstatus, %1\n" /* change mode */
	              :
	              : "r" (pd->translation_table()), "r"(mstatus)
	              : "memory");

	PINF("MMU and supervisor mode enabled");
}


void Genode::Cpu::init_phys_kernel()
{
	/* set exception vector */
	asm volatile ("csrw mtvec, %0\n" : : "r"(exception_entry));

	/* copy mode-transition page to exception vector address */
	memcpy((void *)exception_entry, &_mt_begin, (addr_t)&_mt_end - (addr_t)&_mt_begin);
}


Cpu_idle::Cpu_idle(Cpu * const cpu) : Cpu_job(Cpu_priority::MIN, 0)
{
	PDBG("not impl");
}


void Cpu_idle::exception(unsigned const cpu)
{
	PDBG("not impl");
}
