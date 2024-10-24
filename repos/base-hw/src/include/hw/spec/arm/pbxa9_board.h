/*
 * \brief   Pbxa9 specific board definitions
 * \author  Stefan Kalkowski
 * \date    2019-05-16
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__INCLUDE__HW__SPEC__ARM__PBXA9_BOARD_H_
#define _SRC__INCLUDE__HW__SPEC__ARM__PBXA9_BOARD_H_

#include <drivers/defs/pbxa9.h>
#include <drivers/uart/pl011.h>
#include <hw/spec/arm/boot_info.h>
#include <hw/spec/arm/cortex_a9.h>
#include <hw/spec/arm/pl310.h>

namespace Hw::Pbxa9_board {

	using namespace Pbxa9;

	using L2_cache = Hw::Pl310;
	using Cpu_mmio = Hw::Cortex_a9_mmio<CORTEX_A9_PRIVATE_MEM_BASE>;
	using Serial   = Genode::Pl011_uart;

	enum {
		UART_BASE  = PL011_0_MMIO_BASE,
		UART_CLOCK = PL011_0_CLOCK,
		NR_OF_CPUS = 1,
	};
}

#endif /* _SRC__INCLUDE__HW__SPEC__ARM__PBXA9_BOARD_H_ */
