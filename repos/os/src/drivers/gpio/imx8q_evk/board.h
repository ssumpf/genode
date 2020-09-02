/*
 * \brief  Gpio driver for the i.MX8 SoCs
 * \author Stefan Kalkowski <stefan.kalkowski@genode-labs.com>
 * \date   2018-02-22
 */

/*
 * Copyright (C) 2020 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _DRIVERS__GPIO__SPEC__IMX8__BOARD_H_
#define _DRIVERS__GPIO__SPEC__IMX8__BOARD_H_

/* Genode includes */
#include <drivers/defs/imx8q_evk.h>

namespace Board {
	using namespace Imx8;

	unsigned long const gpio[][4] {
		{ GPIO1_MMIO_BASE, GPIO1_MMIO_SIZE, GPIO1_IRQL, GPIO1_IRQH },
		{ GPIO2_MMIO_BASE, GPIO2_MMIO_SIZE, GPIO2_IRQL, GPIO2_IRQH },
		{ GPIO3_MMIO_BASE, GPIO3_MMIO_SIZE, GPIO3_IRQL, GPIO3_IRQH },
		{ GPIO4_MMIO_BASE, GPIO4_MMIO_SIZE, GPIO4_IRQL, GPIO4_IRQH },
		{ GPIO5_MMIO_BASE, GPIO5_MMIO_SIZE, GPIO5_IRQL, GPIO5_IRQH },
	};
}

#endif /* _DRIVERS__GPIO__SPEC__IMX8__BOARD_H_ */
