/*
 * \brief  VMM cpu object
 * \author Stefan Kalkowski
 * \date   2019-07-18
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */
#include <cpu.h>
#include <vmm.h>

Cpu::System_register::Iss::access_t
Cpu::System_register::Iss::value(unsigned op0, unsigned crn, unsigned op1,
                                 unsigned crm, unsigned op2)
{
	access_t v = 0;
	Crn::set(v, crn);
	Crm::set(v, crm);
	Opcode0::set(v, op0);
	Opcode1::set(v, op1);
	Opcode2::set(v, op2);
	return v;
};


Cpu::System_register::Iss::access_t
Cpu::System_register::Iss::mask_encoding(access_t v)
{
	return Crm::masked(v) |
	       Crn::masked(v) |
	       Opcode1::masked(v) |
	       Opcode2::masked(v) |
	       Opcode0::masked(v);
}


Cpu::System_register::System_register(unsigned         op0,
                                      unsigned         crn,
                                      unsigned         op1,
                                      unsigned         crm,
                                      unsigned         op2,
                                      const char     * name,
                                      bool             writeable,
                                      Genode::uint64_t State::*r,
                                      Genode::addr_t   v,
                                      Genode::Avl_tree<System_register> & tree,
                                      State                     & state)
: _encoding(Iss::value(op0, crn, op1, crm, op2)),
  _name(name),
  _writeable(writeable),
  _r(r),
  _init_value(v)
{
	tree.insert(this);
	write(state, init_value());
}


bool Cpu::_handle_sys_reg()
{
	using Iss = System_register::Iss;

	Iss::access_t v = _state.esr_el2;
	System_register * reg = _reg_tree.first();
	if (reg) reg = reg->find_by_encoding(Iss::mask_encoding(v));

	if (!reg) {
		Genode::error("unknown system register access @ ip=", _state.ip, ":");
		Genode::error(Iss::Direction::get(v) ? "read" : "write",
		              ": "
		              "op0",  Iss::Opcode0::get(v), " "
		              "op1",  Iss::Opcode1::get(v), " "
		              "r",    Iss::Register::get(v),   " "
		              "crn",  Iss::Crn::get(v),        " "
		              "crm",  Iss::Crm::get(v), " ",
		              "op2",  Iss::Opcode2::get(v));
		return false;
	}

	if (Iss::Direction::get(v)) { /* read access  */
		_state.r[Iss::Register::get(v)] = reg->read(_state);
	} else {                      /* write access */
		if (!reg->writeable()) {
			Genode::error("writing to system register ",
			              reg->name(), " not allowed!");
			return false;
		}
		reg->write(_state, _state.r[Iss::Register::get(v)]);
	}
	_state.ip += sizeof(Genode::uint32_t);
	return true;
}


void Cpu::_handle_wfi()
{
	if (_state.esr_el2 & 1)
		throw Exception("WFE not implemented yet");

	wait_for_interrupt();
	// XXX prepare generic timer
	_state.ip += sizeof(Genode::uint32_t);
}


void Cpu::_handle_sync()
{
	/* check device number*/
	switch (Esr::Ec::get(_state.esr_el2)) {
	case Esr::Ec::HVC:
		_vmm.handle_hyper_call();
		break;
	case Esr::Ec::MRS_MSR:
		_handle_sys_reg();
		break;
	case Esr::Ec::DA:
		_vmm.handle_data_abort((Genode::uint64_t)_state.hpfar_el2 << 8);
		break;
	case Esr::Ec::WFI:
		_handle_wfi();
		return;
	default:
		throw Exception("Unknown trap: %x",
		                Esr::Ec::get(_state.esr_el2));
	};
}


void Cpu::dump()
{
	using namespace Genode;

	auto lambda = [] (addr_t exc) {
		switch (exc) {
		case AARCH64_SYNC:   return "aarch64 sync";
		case AARCH64_IRQ:    return "aarch64 irq";
		case AARCH64_FIQ:    return "aarch64 fiq";
		case AARCH64_SERROR: return "aarch64 serr";
		case AARCH32_SYNC:   return "aarch32 sync";
		case AARCH32_IRQ:    return "aarch32 irq";
		case AARCH32_FIQ:    return "aarch32 fiq";
		case AARCH32_SERROR: return "aarch32 serr";
		default:             return "unknown";
		};
	};

	log("VM state (", _active ? "active" : "inactive", ") :");
	for (unsigned i = 0; i < 31; i++) {
		log("  r", i, "         = ",
		    Hex(_state.r[i], Hex::PREFIX, Hex::PAD));
	}
	log("  sp         = ", Hex(_state.sp,      Hex::PREFIX, Hex::PAD));
	log("  ip         = ", Hex(_state.ip,      Hex::PREFIX, Hex::PAD));
	log("  sp_el1     = ", Hex(_state.sp_el1,  Hex::PREFIX, Hex::PAD));
	log("  elr_el1    = ", Hex(_state.elr_el1, Hex::PREFIX, Hex::PAD));
	log("  pstate     = ", Hex(_state.pstate,  Hex::PREFIX, Hex::PAD));
	log("  exception  = ", _state.exception_type, " (",
	                       lambda(_state.exception_type), ")");
}


Cpu::Cpu(Vmm                     & vmm,
         Genode::Vm_connection   & vm,
         Genode::Env             & env,
         Genode::Heap            & heap,
         Genode::Vm_handler_base & handler,
         Genode::addr_t            ip,
         Genode::addr_t            dtb)
: _vmm(vmm),
  _vm(vm),
  _heap(heap),
  _vcpu_id(_vm.create_vcpu(heap, env, handler)),
  _state(*((State*)env.rm().attach(_vm.cpu_state(_vcpu_id)))),
  _sr_mdscr(2, 0, 0, 2, 2, "MDSCR_EL1", true, &State::mdscr_el1, 0x0, _reg_tree, _state)
{
	Genode::memset((void*)&_state, 0, sizeof(Genode::Vm_state));

	_state.r[0]   = dtb;
	_state.ip     = ip;
	_state.pstate = 0b1111000101; /* el1 mode and IRQs disabled */

	// XXX initialize GIC cpu interface and Timer
}
