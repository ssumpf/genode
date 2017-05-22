/**
 * \brief  Calls supported by machine mode (or SBI interface in RISC-V)
 * \author Sebastian Sumpf
 * \author Martin Stein
 * \author Stefan Kalkowski
 * \date   2015-06-14
 */

/*
 * Copyright (C) 2015-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__LIB__HW__SPEC__RISCV__MACHINE_CALL_H_
#define _SRC__LIB__HW__SPEC__RISCV__MACHINE_CALL_H_

#include <kernel/interface.h>

namespace Hw {
	using Kernel::addr_t;
	using Kernel::Call_arg;
	using Genode::uint64_t;

	/**
	 * SBI calls to machine mode.
	 *
	 * Keep in sync with mode_transition.s.
	 */
	constexpr Call_arg call_id_put_char()      { return 0x100; }
	constexpr Call_arg call_id_set_sys_timer() { return 0x101; }
	constexpr Call_arg call_id_get_sys_timer()  { return 0x102; }

	inline void put_char(uint64_t c) {
		Kernel::call(call_id_put_char(), (Call_arg)c); }

	inline void set_sys_timer(addr_t t) {
		Kernel::call(call_id_set_sys_timer(), (Call_arg)t); }

	inline addr_t get_sys_timer() {
		return Kernel::call(call_id_get_sys_timer()); }
}

#endif /* _SRC__LIB__HW__SPEC__RISCV__MACHINE_CALL_H_ */
