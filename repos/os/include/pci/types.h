/*
 * \brief  PCI basic types
 * \author Stefan Kalkowski
 * \date   2021-12-01
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef __INCLUDE__PCI__TYPES_H__
#define __INCLUDE__PCI__TYPES_H__

#include <base/stdint.h>

namespace Pci {
	using bus_t      = Genode::uint8_t;
	using dev_t      = Genode::uint8_t;
	using func_t     = Genode::uint8_t;
	using irq_line_t = Genode::uint8_t;
	using irq_pin_t  = Genode::uint8_t;
	using vendor_t   = Genode::uint16_t;
	using device_t   = Genode::uint16_t;
	using class_t    = Genode::uint32_t;
}

#endif /* __INCLUDE__PCI__TYPES_H__ */
