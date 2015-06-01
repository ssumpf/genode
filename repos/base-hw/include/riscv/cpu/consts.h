/*
 * \brief  Constants definitions for the RISCV architecture.
 * \author Sebastian Sumpf
 * \date   2015-06-01
 */

/*
 * Copyright (C) 2011-2015 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#ifndef _INCLUDE__RISCV__CPU__CONSTS_H_
#define _INCLUDE__RISCV__CPU__CONSTS_H_

#include <base/stdint.h>

namespace Abi {

	/**
	 * On RISCV a call (or branch) will not change the stack pointer, so we do not
	 * need stack adjustment
	 */
	static constexpr Genode::size_t stack_adjustment() { return 0; }

	/**
	 * Do ABI specific initialization to a freshly created stack
	 */
	inline void init_stack(Genode::addr_t) { }
}

#endif /* _INCLUDE__RISCV__CPU__CONSTS_H_ */
