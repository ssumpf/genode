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
#include <kernel/thread.h>
#include <kernel/pd.h>
#include <kernel/kernel.h>

using namespace Kernel;


Thread::Thread(unsigned const priority, unsigned const quota,
               char const * const label)
: Thread_base(this), Cpu_job(priority, quota),
  _state(AWAITS_START), _signal_receiver(0),
  _label(label) { }


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
		PWRN("%s -> %s: illigal instruction at ip=%lx", pd_label(), label(), ip);
		break;
	case LOAD_UNALIGNED:
		PWRN("%s -> %s: unaligned load at ip=%lx", pd_label(), label(), ip);
		break;
	case STORE_UNALIGNED:
		PWRN("%s -> %s: unaligned store at ip=%lx", pd_label(), label(), ip);
		break;
	case SUPERVISOR_CALL:
		_call();
		ip += 4;
		break;
	default:
		PDBG("%lx", cpu_exception);
	}
}


addr_t Thread::* Thread::_reg(addr_t const id) const
{
	static addr_t Thread::* const _regs[] = {
		/* [13] */ (addr_t Thread::*)&Thread::sp,
		/* [15] */ (addr_t Thread::*)&Thread::ip,
		/* [18] */ (addr_t Thread::*)&Thread::_fault_pd,
		/* [19] */ (addr_t Thread::*)&Thread::_fault_addr,
		/* [20] */ (addr_t Thread::*)&Thread::_fault_writes,
		/* [21] */ (addr_t Thread::*)&Thread::_fault_signal
	};
	return id < sizeof(_regs)/sizeof(_regs[0]) ? _regs[id] : 0;
}


void Thread::_mmu_exception()
{
	_become_inactive(AWAITS_RESUME);
	_fault_pd     = (addr_t)_pd->platform_pd();
	_fault_signal = (addr_t)_fault.signal_context();
	
	PDBG("not impl");
	//_fault_addr   = Cpu::Cr2::read();

	/**
	 * core should never raise a page-fault,
	 * if this happens print out an error message with debug information
	 */
	if (_pd == Kernel::core_pd())
		PERR("Pagefault in core thread (%s): ip=%p fault=%p",
		     label(), (void*)ip, (void*)_fault_addr);

	_fault.submit();
	return;
}


Thread_event Thread::* Thread::_event(unsigned const id) const
{
	static Thread_event Thread::* _events[] = {
		/* [0] */ &Thread::_fault
	};
	return id < sizeof(_events)/sizeof(_events[0]) ? _events[id] : 0;
}



void Thread::_call_update_pd()
{
	PDBG("not impl");
}

