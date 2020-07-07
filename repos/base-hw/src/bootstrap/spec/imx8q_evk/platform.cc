/*
 * \brief   Platform implementations specific for base-hw and i.MX8Q EVK
 * \author  Stefan Kalkowski
 * \date    2019-06-12
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
: early_ram_regions(Memory_region { ::Board::RAM_BASE, ::Board::RAM_SIZE }),
  late_ram_regions(Memory_region { }),
  core_mmio(Memory_region { ::Board::UART_BASE, ::Board::UART_SIZE },
            Memory_region { ::Board::Cpu_mmio::IRQ_CONTROLLER_DISTR_BASE,
                            ::Board::Cpu_mmio::IRQ_CONTROLLER_DISTR_SIZE },
            Memory_region { ::Board::Cpu_mmio::IRQ_CONTROLLER_REDIST_BASE,
                            ::Board::Cpu_mmio::IRQ_CONTROLLER_REDIST_SIZE })
{
	::Board::Pic pic {};

	static volatile unsigned long iomux_values[][2] {
		// IOMUXC
		{ 0x30330064, 0x6        },
		{ 0x30330140, 0x0        },
		{ 0x30330144, 0x0        },
		{ 0x30330148, 0x0        },
		{ 0x3033014C, 0x0        },
		{ 0x30330150, 0x0        },
		{ 0x30330154, 0x0        },
		{ 0x30330158, 0x0        },
		{ 0x30330180, 0x2        },
		{ 0x30330184, 0x0        },
		{ 0x30330188, 0x0        },
		{ 0x3033018C, 0x0        },
		{ 0x30330190, 0x0        },
		{ 0x30330194, 0x0        },
		{ 0x30330198, 0x0        },
		{ 0x3033019C, 0x0        },
		{ 0x303301A0, 0x0        },
		{ 0x303301A4, 0x0        },
		{ 0x303301A8, 0x0        },
		{ 0x303301AC, 0x0        },
		{ 0x303301BC, 0x0        },
		{ 0x303301C0, 0x0        },
		{ 0x303301C4, 0x0        },
		{ 0x303301C8, 0x0        },
		{ 0x303301E8, 0x0        },
		{ 0x303301EC, 0x0        },
		{ 0x303301FC, 0x1        },
		{ 0x30330200, 0x1        },
		{ 0x3033021C, 0x10       },
		{ 0x30330220, 0x10       },
		{ 0x30330224, 0x10       },
		{ 0x30330228, 0x10       },
		{ 0x3033022C, 0x12       },
		{ 0x30330230, 0x12       },
		{ 0x30330244, 0x0        },
		{ 0x30330248, 0x0        },
		{ 0x3033029C, 0x19       },
		{ 0x303302A4, 0x19       },
		{ 0x303302A8, 0x19       },
		{ 0x303302B0, 0xD6       },
		{ 0x303302C0, 0x4F       },
		{ 0x303302C4, 0x16       },
		{ 0x303302CC, 0x59       },
		{ 0x3033033C, 0x9F       },
		{ 0x30330340, 0xDF       },
		{ 0x30330344, 0xDF       },
		{ 0x30330348, 0xDF       },
		{ 0x3033034C, 0xDF       },
		{ 0x30330350, 0xDF       },
		{ 0x30330368, 0x59       },
		{ 0x30330370, 0x19       },
		{ 0x3033039C, 0x19       },
		{ 0x303303A0, 0x19       },
		{ 0x303303A4, 0x19       },
		{ 0x303303A8, 0xD6       },
		{ 0x303303AC, 0xD6       },
		{ 0x303303B0, 0xD6       },
		{ 0x303303B4, 0xD6       },
		{ 0x303303B8, 0xD6       },
		{ 0x303303BC, 0xD6       },
		{ 0x303303C0, 0xD6       },
		{ 0x303303E8, 0xD6       },
		{ 0x303303EC, 0xD6       },
		{ 0x303303F0, 0xD6       },
		{ 0x303303F4, 0xD6       },
		{ 0x303303F8, 0xD6       },
		{ 0x303303FC, 0xD6       },
		{ 0x30330400, 0xD6       },
		{ 0x30330404, 0xD6       },
		{ 0x30330408, 0xD6       },
		{ 0x3033040C, 0xD6       },
		{ 0x30330410, 0xD6       },
		{ 0x30330414, 0xD6       },
		{ 0x30330424, 0xD6       },
		{ 0x30330428, 0xD6       },
		{ 0x3033042C, 0xD6       },
		{ 0x30330430, 0xD6       },
		{ 0x30330450, 0xD6       },
		{ 0x30330454, 0xD6       },
		{ 0x30330464, 0x49       },
		{ 0x30330468, 0x49       },
		{ 0x3033046C, 0x16       },
		{ 0x30330484, 0x67       },
		{ 0x30330488, 0x67       },
		{ 0x3033048C, 0x67       },
		{ 0x30330490, 0x67       },
		{ 0x30330494, 0x76       },
		{ 0x30330498, 0x76       },
		{ 0x303304AC, 0x49       },
		{ 0x303304B0, 0x49       },
		{ 0x303304C8, 0x1        },
		{ 0x303304CC, 0x4        },
		{ 0x30330500, 0x1        },
		{ 0x30330504, 0x2        },
		{ 0x30340038, 0x49409600 },
		{ 0x30340040, 0x49409200 }
	};

	struct Gpio_reg : Genode::Mmio
	{
		Gpio_reg(Genode::addr_t const mmio_base)
			: Genode::Mmio(mmio_base) { }

		struct Data       : Register<0x0,  32> {};
		struct Dir        : Register<0x4,  32> {};
		struct Int_conf_0 : Register<0xc,  32> {};
		struct Int_conf_1 : Register<0x10, 32> {};
		struct Int_mask   : Register<0x14, 32> {};
		struct Int_stat   : Register<0x18, 32> {};
	};

	struct Ccm_reg : Genode::Mmio
	{
		Ccm_reg(Genode::addr_t const mmio_base)
			: Genode::Mmio(mmio_base) { }

		struct Target_root_0   : Register<0x8000, 32> {};
		struct Target_root_20  : Register<0x8a00, 32> {};
		struct Target_root_21  : Register<0x8a80, 32> {};
		struct Target_root_22  : Register<0x8b00, 32> {};
		struct Target_root_36  : Register<0x9200, 32> {};
		struct Target_root_68  : Register<0xa200, 32> {};
		struct Target_root_118 : Register<0xbb00, 32> {};
		struct Target_root_119 : Register<0xbb80, 32> {};
	};

	struct Pll_reg : Genode::Mmio
	{
		Pll_reg(Genode::addr_t const mmio_base)
			: Genode::Mmio(mmio_base) { }

		struct Pll_video_1_0 : Register<0x10, 32> { };
		struct Pll_video_1_1 : Register<0x14, 32> { };

		struct Pll_arm_0 : Register<0x28,  32> {};
		struct Pll_arm_1 : Register<0x2c,  32> {};
	};

	unsigned num_values = sizeof(iomux_values) / (2*sizeof(unsigned long));
	for (unsigned i = 0; i < num_values; i++)
		*((volatile Genode::uint32_t*)iomux_values[i][0]) = (Genode::uint32_t)iomux_values[i][1];

	/* enable MIPI power domain */
	unsigned long result = 0;
	asm volatile("mov x0, %1  \n"
	             "mov x1, %2  \n"
	             "mov x2, %3  \n"
	             "mov x3, %4  \n"
	             "smc #0      \n"
	             "mov %0, x0  \n"
	             : "=r" (result) : "r" (0xc2000000), "r" (0x3), "r" (0x0), "r" (1)
	                      : "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7",
	                        "x8", "x9", "x10", "x11", "x12", "x13", "x14");

	Ccm_reg ccm(0x30380000);
	Ccm_reg pll(0x30360000);

	/* configure GPIO PIN 13 of GPIO 1 for high voltage */
	Gpio_reg regulator(0x30200000);
	regulator.write<Gpio_reg::Int_conf_0>(0);
	regulator.write<Gpio_reg::Int_conf_1>(0);
	regulator.write<Gpio_reg::Int_mask>(0x1000);
	regulator.write<Gpio_reg::Int_stat>(0xffffffff);
	regulator.write<Gpio_reg::Dir>(0x2328);
	regulator.write<Gpio_reg::Data>(0x9f40);

	ccm.write<Ccm_reg::Target_root_0>(0x14000000);
	pll.write<Pll_reg::Pll_arm_1>(0x4a);

	unsigned long v = pll.read<Pll_reg::Pll_arm_0>();
	pll.write<Pll_reg::Pll_arm_0>(v & 0xffffffe0);
	v = pll.read<Pll_reg::Pll_arm_0>();
	pll.write<Pll_reg::Pll_arm_0>(v | (1<<12));

	while (!(pll.read<Pll_reg::Pll_arm_0>() & (1<<11))) { ; }

	v = pll.read<Pll_reg::Pll_arm_0>();
	pll.write<Pll_reg::Pll_arm_0>(v ^ (1<<12));
	ccm.write<Ccm_reg::Target_root_0>(0x11000000);

	/* MIPI_DSI_ESC_RX_CLK_ROOT = SYSTEM_PLL1_DIV10 */
	ccm.write<Ccm_reg::Target_root_36>(0x12000000);

	/* MIPI_DSI_CORE_CLK_ROOT = SYSTEM_PLL1_DIV3 */
	ccm.write<Ccm_reg::Target_root_118>(0x11000000);

	/* MIPI_DSI_PHY_REF_CLK_ROOT bypass VIDEO_PLL1_CLOCK */
	ccm.write<Ccm_reg::Target_root_119>(0x14000000);


	v = pll.read<Pll_reg::Pll_video_1_0>();
	if (v & (1 << 19)) {
		Genode::log("VIDEO boot: ", Genode::Hex(v));
		v ^= (1 << 19); /* enable PLL */

		while ((pll.read<Pll_reg::Pll_video_1_0>() & (1 << 31)) == 0) { ; }
	}


	pll.write<Pll_reg::Pll_video_1_1>(0x3b);
	v = pll.read<Pll_reg::Pll_video_1_0>();

	Genode::log("INITIAL: ", Genode::Hex(v));
	Genode::log("v: ", Genode::Hex(v));
	v &= ~0x1ful;
	pll.write<Pll_reg::Pll_video_1_0>(v);
	v = pll.read<Pll_reg::Pll_video_1_0>();
	pll.write<Pll_reg::Pll_video_1_0>(v | (1 << 12));
	Genode::log("WAIT");
//XXX: must WORK! while (!(pll.read<Pll_reg::Pll_video_1_0>() & (1<<11))) { ; }
	Genode::log("WAIT done");

	v = pll.read<Pll_reg::Pll_video_1_0>();
	pll.write<Pll_reg::Pll_video_1_0>(v ^ (1<<12));

	Genode::log("FINAL: ", Genode::Hex(pll.read<Pll_reg::Pll_video_1_0>()));

	/* MIPI_DSI_PHY_REF_CLK_ROOT = VIDEO_PLL1_CLOCK */
	ccm.write<Ccm_reg::Target_root_119>(0x17000000);

	v = ccm.read<Ccm_reg::Target_root_21>();
	Genode::log("APB: ", Genode::Hex(v));
	v = ccm.read<Ccm_reg::Target_root_20>();
	Genode::log("AXI: ", Genode::Hex(v));
	v = ccm.read<Ccm_reg::Target_root_22>();
	Genode::log("RTRM: ", Genode::Hex(v));
	v = ccm.read<Ccm_reg::Target_root_68>();
	Genode::log("DTRC: ", Genode::Hex(v));
}


void Board::Cpu::wake_up_all_cpus(void * ip)
{
	enum Function_id { CPU_ON = 0xC4000003 };

	unsigned long result = 0;
	for (unsigned i = 1; i < NR_OF_CPUS; i++) {
		asm volatile("mov x0, %1  \n"
		             "mov x1, %2  \n"
		             "mov x2, %3  \n"
		             "mov x3, %2  \n"
		             "smc #0      \n"
		             "mov %0, x0  \n"
		             : "=r" (result) : "r" (CPU_ON), "r" (i), "r" (ip)
		                      : "x0", "x1", "x2", "x3", "x4", "x5", "x6", "x7",
		                        "x8", "x9", "x10", "x11", "x12", "x13", "x14");
	}
}
