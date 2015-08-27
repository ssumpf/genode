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
#include <assert.h>
#include <kernel/cpu.h>
#include <kernel/pd.h>

using namespace Kernel;

extern Genode::addr_t _mt_client_context_ptr;

struct Mstatus : Genode::Register<64>
{
	enum {
		USER       = 0,
		SUPERVISOR = 1,
		MACHINE    = 3,
		Sv39       = 9,
	};
	struct Ie    : Bitfield<0, 1> { };
	struct Priv  : Bitfield<1, 2> { };
	struct Ie1   : Bitfield<3, 1> { };
	struct Priv1 : Bitfield<4, 2> { };
	struct Vm    : Bitfield<17, 5> { };
	struct Mprv  : Bitfield<16, 1> { };
};


void Genode::Cpu::init_virt_kernel(Kernel::Pd * pd)
{
	/* read status register */
	Mstatus::access_t mstatus;
	asm volatile ("csrr %0, mstatus\n" : "=r"(mstatus));

	Mstatus::Vm::set(mstatus, Mstatus::Sv39);         /* enable Sv39 paging  */
	Mstatus::Ie1::set(mstatus, 1);
	Mstatus::Priv1::set(mstatus, Mstatus::USER);      /* set user mode */

	asm volatile ("csrw sasid,   %0\n" /* address space id */
	              "csrw sptbr,   %1\n" /* set page table */
	              "csrw mstatus, %2\n" /* change mode */
	              :
	              : "r" (pd->asid), "r" (pd->translation_table()), "r"(mstatus)
	              : "memory");

	/* set exception vector */
	asm volatile ("csrw stvec, %0" : : "r"(exception_entry));

	/* set _mt_client_context_ptr address */
	addr_t context_addr = (addr_t)&_mt_client_context_ptr;
	context_addr = exception_entry | (context_addr & 0xfff);
	asm volatile ("csrw sscratch, %0" : : "r"(context_addr));

	Mstatus::Ie::set(mstatus, 0);                     /* disable interrupts  */
	Mstatus::Priv::set(mstatus, Mstatus::SUPERVISOR); /* set supervisor mode */
	asm volatile ("csrw mstatus, %0\n" : : "r"(mstatus));

	PINF("MMU and supervisor mode enabled");
}


void Genode::Cpu::init_phys_kernel()
{
	PDBG("called");
}


Cpu_idle::Cpu_idle(Cpu * const cpu) : Cpu_job(Cpu_priority::MIN, 0)
{
	Cpu_job::cpu(cpu);
	cpu_exception = RESET;
	ip = (addr_t)&_main;
	sp = (addr_t)&_stack[stack_size];
	init_thread((addr_t)core_pd()->translation_table(), core_pd()->asid);
}


void Cpu_idle::exception(unsigned const cpu)
{
	if (is_irq()) {
		_interrupt(cpu);
		return;
	} else if (cpu_exception == RESET) return;

	assert(0);
}
