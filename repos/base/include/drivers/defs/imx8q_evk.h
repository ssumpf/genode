/*
 * \brief  MMIO and IRQ definitions for the i.MX8Q EVK board
 * \author Christian Prochaska
 * \date   2019-09-26
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__DRIVERS__DEFS__IMX8Q_EVK_H_
#define _INCLUDE__DRIVERS__DEFS__IMX8Q_EVK_H_

namespace Imx8 {
	enum {
		/* SD host controller */
		SDHC_2_IRQ       = 55,
		SDHC_2_MMIO_BASE = 0x30b50000,
		SDHC_2_MMIO_SIZE = 0x00010000,

		GPIO1_MMIO_BASE = 0x30200000,
		GPIO1_MMIO_SIZE = 0x10000,
		GPIO2_MMIO_BASE = 0x30210000,
		GPIO2_MMIO_SIZE = 0x10000,
		GPIO3_MMIO_BASE = 0x30220000,
		GPIO3_MMIO_SIZE = 0x10000,
		GPIO4_MMIO_BASE = 0x30230000,
		GPIO4_MMIO_SIZE = 0x10000,
		GPIO5_MMIO_BASE = 0x30240000,
		GPIO5_MMIO_SIZE = 0x10000,

		GPIO_COUNT = 5,
		GPIO1_IRQL = 96,
		GPIO1_IRQH = 97,
		GPIO2_IRQL = 98,
		GPIO2_IRQH = 99,
		GPIO3_IRQL = 100,
		GPIO3_IRQH = 101,
		GPIO4_IRQL = 102,
		GPIO4_IRQH = 103,
		GPIO5_IRQL = 104,
		GPIO5_IRQH = 105,

		I2C_1_IRQ  = 67,
		I2C_1_BASE = 0x30a20000,
		I2C_1_SIZE = 0x10000,
	};
};

#endif /* _INCLUDE__DRIVERS__DEFS__IMX8Q_EVK_H_ */
