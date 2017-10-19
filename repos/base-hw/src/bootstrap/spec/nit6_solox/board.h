/*
 * \brief   Nit6 SOLOX specific board definitions
 * \author  Stefan Kalkowski
 * \date    2017-10-18
 */

/*
 * Copyright (C) 2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__BOOTSTRAP__SPEC__NIT6_SOLOX__BOARD_H_
#define _SRC__BOOTSTRAP__SPEC__NIT6_SOLOX__BOARD_H_

#include <drivers/defs/nit6_solox.h>
#include <drivers/uart/imx.h>
#include <hw/spec/arm/cortex_a9.h>
#include <hw/spec/arm/pl310.h>

#include <spec/arm/cortex_a9_actlr.h>
#include <spec/arm/cortex_a9_page_table.h>
#include <spec/arm/cpu.h>
#include <spec/arm/pic.h>

namespace Board {

	using namespace Nit6_solox;

	using L2_cache = Hw::Pl310;
	using Cpu_mmio = Hw::Cortex_a9_mmio<CORTEX_A9_PRIVATE_MEM_BASE>;
	using Serial   = Genode::Imx_uart;

	enum {
		UART_BASE  = UART_1_MMIO_BASE,
		UART_CLOCK = 0, /* dummy value, not used */
	};
}

#endif /* _SRC__BOOTSTRAP__SPEC__NIT6_SOLOX__BOARD_H_ */
