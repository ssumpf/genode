/*
 * \brief   CPU, PIC, and timer context of a virtual machine
 * \author  Stefan Kalkowski
 * \date    2015-02-10
 */

/*
 * Copyright (C) 2015-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__SPEC__ARM_64__CPU__VM_STATE_VIRTUALIZATION_H_
#define _INCLUDE__SPEC__ARM_64__CPU__VM_STATE_VIRTUALIZATION_H_

/* Genode includes */
#include <cpu/cpu_state.h>

namespace Genode
{
	/**
	 * CPU context of a virtual machine
	 */
	struct Vm_state;

	using uint128_t = __uint128_t;
}

struct Genode::Vm_state : Genode::Cpu_state
{
	Genode::uint64_t pstate { 0 };
	Genode::uint64_t exception_type { 0 };
	Genode::uint64_t esr_el2 { 0 };

	/** Fpu registers **/
	Genode::uint128_t q[32] { 0 };
	Genode::uint32_t fpcr   { 0 };
	Genode::uint32_t fpsr   { 0 };

	Genode::uint64_t elr_el1  { 0 };
	Genode::uint64_t sp_el1   { 0 };
	Genode::uint32_t spsr_el1 { 0 };
	Genode::uint32_t esr_el1  { 0 };

	Genode::uint64_t sctlr_el1 { 0 };
	Genode::uint64_t actlr_el1 { 0 };
	Genode::uint64_t vbar_el1  { 0 };
	Genode::uint32_t cpacr_el1 { 0 };
	Genode::uint32_t afsr0_el1 { 0 };      /* check */
	Genode::uint32_t afsr1_el1 { 0 };      /* check */
	Genode::uint32_t contextidr_el1 { 0 }; /* check */

	Genode::uint64_t ttbr0_el1 { 0 };
	Genode::uint64_t ttbr1_el1 { 0 };
	Genode::uint64_t tcr_el1   { 0 };
	Genode::uint64_t mair_el1  { 0 };
	Genode::uint64_t amair_el1 { 0 };
	Genode::uint64_t far_el1   { 0 };
	Genode::uint64_t par_el1   { 0 }; /* check */

	Genode::uint64_t tpidrro_el0 { 0 };
	Genode::uint64_t tpidr_el0   { 0 };
	Genode::uint64_t tpidr_el1   { 0 };

	Genode::uint64_t far_el2     { 0 };
	Genode::uint64_t hpfar_el2   { 0 };

#if 0
	/**
	 * Timer related registers
	 */

	Genode::uint32_t timer_ctrl;
	Genode::uint32_t timer_val;
	bool             timer_irq;


	/**
	 * PIC related registers
	 */

	enum { NR_IRQ = 4 };

	Genode::uint32_t gic_hcr;
	Genode::uint32_t gic_vmcr;
	Genode::uint32_t gic_misr;
	Genode::uint32_t gic_apr;
	Genode::uint32_t gic_eisr;
	Genode::uint32_t gic_elrsr0;
	Genode::uint32_t gic_lr[4];
	unsigned         gic_irq;
#endif
};

#endif /* _INCLUDE__SPEC__ARM_64__CPU__VM_STATE_VIRTUALIZATION_H_ */
