/*
 * \brief   Platform implementations specific for base-hw and VIRT Qemu
 * \author  Alexander Boettcher
 * \date    2019-07-11
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <platform.h>

/**
 * Leave out the first page (being 0x0) from bootstraps RAM allocator,
 * some code does not feel happy with addresses being zero
 */
Bootstrap::Platform::Board::Board()
: early_ram_regions(Memory_region { ::Board::RAM_BASE + 0x1000,
                                    ::Board::RAM_SIZE - 0x1000 }),
  late_ram_regions(Memory_region { ::Board::RAM_BASE, 0x1000 }),
  core_mmio(Memory_region { ::Board::UART_BASE, ::Board::UART_SIZE },
            Memory_region { ::Board::Cpu_mmio::IRQ_CONTROLLER_DISTR_BASE,
                            ::Board::Cpu_mmio::IRQ_CONTROLLER_DISTR_SIZE },
            Memory_region { ::Board::Cpu_mmio::IRQ_CONTROLLER_VT_CTRL_BASE,
                            ::Board::Cpu_mmio::IRQ_CONTROLLER_VT_CTRL_SIZE },
            Memory_region { ::Board::Cpu_mmio::IRQ_CONTROLLER_CPU_BASE,
                            ::Board::Cpu_mmio::IRQ_CONTROLLER_CPU_SIZE }) {}
