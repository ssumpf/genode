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
	if (is_irq()) {
		PDBG("IRQ %u", irq());
		return;
	}

	switch(cpu_exception) {
	case INSTRUCTION_UNALIGNED:
		PWRN("%s -> %s: unaligned instruction at ip=%lx", pd_label(), label(), ip);
		break;
	case INSTRUCTION_ILLEGAL:
		PWRN("%s -> %s: illigal instruction at ip=%lx ra=%lx", pd_label(), label(), ip, ra);
		break;
	case LOAD_UNALIGNED:
		PWRN("%s -> %s: unaligned load at ip=%lx", pd_label(), label(), ip);
		break;
	case STORE_UNALIGNED:
		PWRN("%s -> %s: unaligned store at ip=%lx", pd_label(), label(), ip);
		break;
	case SUPERVISOR_CALL:
		PWRN("system call %lu", a0);
		_call();
		ip += 4;
		break;
	case INSTRUCTION_PAGE_FAULT:
	case STORE_PAGE_FAULT:
	case LOAD_PAGE_FAULT:
		_mmu_exception();
		break;
	default:
		PDBG("%lx", cpu_exception);
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

