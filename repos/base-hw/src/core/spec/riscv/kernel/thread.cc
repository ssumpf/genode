/*
 * \brief   Kernel backend for execution contexts in userland
 * \author  Martin Stein
 * \author  Stefan Kalkowski
 * \date    2013-11-11
 */

/*
 * Copyright (C) 2013 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

/* core includes */
#include <kernel/pd.h>
#include <kernel/thread.h>

using namespace Kernel;

void Kernel::Thread::_init() { }

void Thread::exception(unsigned const cpu)
{
	if (is_irq())
		return;

	switch(cpu_exception) {
	case SUPERVISOR_CALL:
		_call();
		ip += 4; /* set to next instruction */
		break;
	case INSTRUCTION_PAGE_FAULT:
	case STORE_PAGE_FAULT:
	case LOAD_PAGE_FAULT:
		_mmu_exception();
		break;
	default:
		PWRN("%s -> %s: unhandled exception %lu at ip=%lx addr=%lx",
		     pd_label(), label(), cpu_exception, ip, Cpu::sbadaddr());
		_stop();
	}
}


void Thread::_mmu_exception()
{
	_become_inactive(AWAITS_RESUME);
	_fault_pd     = (addr_t)_pd->platform_pd();
	_fault_signal = (addr_t)_fault.signal_context();
	_fault_addr   = Cpu::sbadaddr();

	_fault.submit();
}


void Thread::_call_update_pd()
{
	asm volatile ("sfence.vm");
}

