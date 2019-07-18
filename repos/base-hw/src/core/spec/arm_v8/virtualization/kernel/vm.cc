/*
 * \brief   Kernel backend for virtual machines
 * \author  Stefan Kalkowski
 * \date    2015-02-10
 */

/*
 * Copyright (C) 2015-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <base/log.h>
#include <hw/assert.h>
#include <cpu/vm_state_virtualization.h>

#include <map_local.h>
#include <platform_pd.h>
#include <kernel/cpu.h>
#include <kernel/vm.h>

namespace Kernel
{
	/**
	 * Kernel private virtualization interrupts, delivered to VM/VMMs
	 */
	struct Vm_irq;
}

using namespace Kernel;

extern "C" void   kernel();
extern     void * kernel_stack;
extern "C" void   hypervisor_enter_vm(addr_t vm, addr_t host,
                                      addr_t guest_table);


static Genode::Vm_state & host_context()
{
	static Genode::Constructible<Genode::Vm_state> host_context;
	if (!host_context.constructed()) {
		host_context.construct();
		host_context->ip        = (addr_t) &kernel;
		host_context->pstate    = 0;
		Cpu::Spsr::Sp::set(host_context->pstate, 1); /* select non-el0 stack pointer */
		Cpu::Spsr::El::set(host_context->pstate, Cpu::Current_el::EL1);
		Cpu::Spsr::F::set(host_context->pstate, 1);
		Cpu::Spsr::I::set(host_context->pstate, 1);
		Cpu::Spsr::A::set(host_context->pstate, 1);
		Cpu::Spsr::D::set(host_context->pstate, 1);
		host_context->fpcr      = Cpu::Fpcr::read();
		host_context->fpsr      = 0;
		host_context->sctlr_el1 = Cpu::Sctlr_el1::read();
		host_context->actlr_el1 = Cpu::Actlr_el1::read();
		host_context->vbar_el1  = Cpu::Vbar_el1::read();
		host_context->cpacr_el1 = Cpu::Cpacr_el1::read();
		host_context->ttbr0_el1 = Cpu::Ttbr0_el1::read();
		host_context->ttbr1_el1 = Cpu::Ttbr1_el1::read();
		host_context->tcr_el1   = Cpu::Tcr_el1::read();
		host_context->mair_el1  = Cpu::Mair::read();
		host_context->amair_el1 = Cpu::Amair_el1::read();
	}
	return *host_context;
}


struct Kernel::Vm_irq : Kernel::Irq
{
	Vm_irq(unsigned const irq)
	:
		Kernel::Irq(irq, cpu_pool().executing_cpu().irq_pool())
	{ }

	/**
	 * A VM interrupt gets injected into the VM scheduled on the current CPU
	 */
	void occurred() override
	{
	Genode::raw("--",__func__);
		Cpu_job & job = cpu_pool().executing_cpu().scheduled_job();
		Vm *vm = dynamic_cast<Vm*>(&job);
		if (!vm)
			Genode::raw("VM timer interrupt while VM is not runnning!");
		else
			vm->inject_irq(_irq_nr);
	}
};

using Vmid_allocator = Genode::Bit_allocator<256>;

static Vmid_allocator &alloc()
{
	static Vmid_allocator * allocator = nullptr;
	if (!allocator) {
		allocator = unmanaged_singleton<Vmid_allocator>();

		/* reserve VM ID 0 for the hypervisor */
		unsigned id = allocator->alloc();
		assert (id == 0);
	}
	return *allocator;
}


Kernel::Vm::Vm(void                   * const state,
               Kernel::Signal_context * const context,
               void                   * const table)
:  Cpu_job(Cpu_priority::MIN, 0),
  _id(alloc().alloc()),
  _state((Genode::Vm_state *)state),
  _context(context),
  _table(table)
{
	affinity(cpu_pool().primary_cpu());
}


Kernel::Vm::~Vm() { alloc().free(_id); }


void Kernel::Vm::exception(Cpu & cpu)
{
	switch (_state->exception_type) {
	case Cpu::IRQ_LEVEL_EL0: [[fallthrough]]
	case Cpu::IRQ_LEVEL_EL1: [[fallthrough]]
	case Cpu::FIQ_LEVEL_EL0: [[fallthrough]]
	case Cpu::FIQ_LEVEL_EL1:
		_interrupt(cpu.id());
		return;
	case Cpu::SYNC_LEVEL_EL0: [[fallthrough]]
	case Cpu::SYNC_LEVEL_EL1:
		break;
	default:
		Genode::raw("Exception vector: ", (void*)_state->exception_type,
		            " not implemented!");
	};
	pause();
	_context->submit(1);
}


void Kernel::Vm::proceed(Cpu & cpu)
{
	/*
	 * the following values have to be enforced by the hypervisor
	 */
	Cpu::Vttbr_el2::access_t vttbr_el2 =
		Cpu::Vttbr_el2::Ba::masked((Cpu::Vttbr_el2::access_t)_table);
	Cpu::Vttbr_el2::Asid::set(vttbr_el2, _id);
	addr_t guest = (addr_t)_state          - 0xffffff8000000000;
	addr_t host  = (addr_t)&host_context() - 0xffffff8000000000;
	host_context().sp_el1 = cpu.stack_start();

	hypervisor_enter_vm(guest, host, vttbr_el2);
}


void Vm::inject_irq(unsigned /*irq*/)
{ 
	Genode::raw("--",__func__);
}
