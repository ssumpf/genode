/*
 * \brief   Kernel backend for execution contexts in userland
 * \author  Sebastian Sumpf
 * \date    2015-06-02
 */

/*
 * Copyright (C) 2015-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
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
	case ECALL_FROM_USER:
		_call();
		ip += 4; /* set to next instruction */
		break;
	case INSTRUCTION_PAGE_FAULT:
	case STORE_PAGE_FAULT:
	case LOAD_PAGE_FAULT:
		_mmu_exception();
		break;
	default:
		Genode::error(*this, ": unhandled exception ", cpu_exception,
		              " at ip=", (void*)ip, " addr=", Genode::Hex(Cpu::sbadaddr()));
		_die();
	}
}


void Thread::_mmu_exception()
{
	_become_inactive(AWAITS_RESTART);
	_fault_pd   = (addr_t)_pd->platform_pd();
	_fault_addr = Cpu::sbadaddr();

	if (_pager) _pager->submit(1);
}


void Thread::_call_update_pd()
{
	Cpu::sfence();
}


void Thread::_call_update_data_region()
{
	Cpu::sfence();
}


void Thread::_call_update_instr_region() { }
