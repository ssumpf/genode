/*
 * \brief  Driver for Nit6 SOLOX devices (clocks, power, etc.)
 * \author Stefan Kalkowski <stefan.kalkowski@genode-labs.com>
 * \date   2018-03-28
 */

/*
 * Copyright (C) 2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <base/attached_io_mem_dataspace.h>
#include <base/component.h>
#include <base/heap.h>
#include <base/log.h>
#include <util/mmio.h>

struct Main
{
	struct Pll : Genode::Attached_io_mem_dataspace, Genode::Mmio
	{
		struct Arm_pll_ctrl             : Register<0x0,   32> { };
		struct Usb1_480mhz_pll_ctrl     : Register<0x10,  32> { };
		struct Usb2_480mhz_pll_ctrl     : Register<0x20,  32> { };
		struct System_pll_ctrl          : Register<0x30,  32> { };
		struct Audio_pll_ctrl           : Register<0x70,  32> { };
		struct Video_pll_ctrl           : Register<0xa0,  32> { };
		struct Enet_pll_control         : Register<0xe0, 32> { };
		struct Pll3_480mhz_divider_ctrl : Register<0xf0, 32> { };
		struct Pll2_528mhz_divider_ctrl : Register<0x100, 32> { };
		struct Miscellaneous1           : Register<0x160, 32> { };
		struct Miscellaneous2           : Register<0x170, 32> { };

		struct Unknown1 : Register<0x1b0, 32> { }; /*00180000*/
		struct Unknown2 : Register<0x210, 32> { }; /*00180000*/


		Pll(Genode::Env &env)
		: Genode::Attached_io_mem_dataspace(env, 0x020c8000, 0x1000),
		  Genode::Mmio((Genode::addr_t)local_addr<void>())
		{
			write<Arm_pll_ctrl>(0x80002042);
			write<Usb1_480mhz_pll_ctrl>(0x80003000);
			write<Usb2_480mhz_pll_ctrl>(0x00000000);
			write<System_pll_ctrl>(0x80002001);
			write<Audio_pll_ctrl>(0x00119006);
			write<Video_pll_ctrl>(0x0000100c);
			write<Enet_pll_control>(0x8030200f);
			write<Pll2_528mhz_divider_ctrl>(0xd058d0db);
			write<Miscellaneous1>(0x0003000a);
			write<Miscellaneous2>(0x00676767);
			write<Unknown1>(0x180000);
			write<Unknown2>(0x180000);
			write<Pll3_480mhz_divider_ctrl>(0xd3d1d08c);
		}
	};


	struct Ccm : Genode::Attached_io_mem_dataspace, Genode::Mmio
	{
		struct Ctrl_divider          : Register<0x04, 32> {};
		struct Bus_clock_divider     : Register<0x14, 32> {};
		struct Bus_clock_mux         : Register<0x18, 32> {};
		struct Serial_clock_mux1     : Register<0x1c, 32> {};
		struct Serial_clock_mux2     : Register<0x20, 32> {};
		struct Ssi1_clock_divider    : Register<0x28, 32> {};
		struct Ssi2_clock_divider    : Register<0x2c, 32> {};
		struct D1_clock_divider      : Register<0x30, 32> {};
		struct Hsc_clock_divider     : Register<0x34, 32> {};
		struct Serial_clock_divider2 : Register<0x38, 32> {};
		struct Ccm_low_power_ctrl    : Register<0x54, 32> {};
		struct Clock_output_source   : Register<0x60, 32> {};
		struct Clock_gating_0        : Register<0x68, 32> {};
		struct Clock_gating_1        : Register<0x6c, 32> {};
		struct Clock_gating_2        : Register<0x70, 32> {};
		struct Clock_gating_3        : Register<0x74, 32> {};
		struct Clock_gating_4        : Register<0x78, 32> {};
		struct Clock_gating_5        : Register<0x7c, 32> {};
		struct Clock_gating_6        : Register<0x80, 32> {};


		Ccm(Genode::Env &env)
		: Genode::Attached_io_mem_dataspace(env, 0x020c4000, 0x1000),
		  Genode::Mmio((Genode::addr_t)local_addr<void>())
		{
			write<Ctrl_divider>(0x00020000);
			write<Bus_clock_mux>(0x00a69114);
			write<Serial_clock_mux1>(0x4510a9c0);
			write<Serial_clock_mux2>(0x13212c06);
			write<Ssi1_clock_divider>(0x00000000);
			write<Ssi2_clock_divider>(0x0004b600);
			write<D1_clock_divider>(0x30074792);
			write<Hsc_clock_divider>(0x00021148);
			write<Serial_clock_divider2>(0x00011153);
			write<Ccm_low_power_ctrl>(0x00000078);
			write<Clock_output_source>(0x0000000e);
			write<Clock_gating_0>(0xf0c0000f);
			write<Clock_gating_1>(0x333c0c00);
			write<Clock_gating_2>(0x0f3f0033);
			write<Clock_gating_3>(0xfff30033);
			write<Clock_gating_4>(0x0000c3fc);
			write<Clock_gating_5>(0x0f030f3f);
			write<Clock_gating_6>(0x000cf000);
		}
	};

	Genode::Env &  env;
	Ccm            ccm  { env };
	Pll            pll  { env };

	Main(Genode::Env & env) : env(env) { }
};


void Component::construct(Genode::Env &env)
{
	Genode::log("--- Nit6 SOLOX platform driver ---");

	static Main main(env);
}
