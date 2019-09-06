/*
 * \brief  VMM device object
 * \author Stefan Kalkowski
 * \date   2019-07-18
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <cpu.h>
#include <device.h>

void Device::handle_memory_access(Cpu & cpu)
{
	using namespace Genode;

	Cpu::State & state = cpu.state();

	struct Iss : Cpu::Esr
	{
		struct Write        : Bitfield<6,  1> {};
		struct Register     : Bitfield<16, 4> {};
		struct Sign_extend  : Bitfield<21, 1> {};
		struct Access_size  : Bitfield<22, 2> {
			enum { BYTE, HALFWORD, WORD, DOUBLEWORD }; };
		struct Valid        : Bitfield<24, 1> {};

		static bool valid(access_t v) {
			return Valid::get(v) && !Sign_extend::get(v); }

		static bool write(access_t v) { return Write::get(v); }
		static unsigned r(access_t v) { return Register::get(v); }
	};

	if (!Iss::valid(state.esr_el2))
		throw Error("Device %s: unknown ESR=%lx",
		            name(), state.esr_el2);

	bool     wr  = Iss::Write::get(state.esr_el2);
	unsigned idx = Iss::Register::get(state.esr_el2);
	uint64_t ipa = (uint64_t)state.hpfar_el2 << 8;
	uint64_t off = ipa - addr() + (state.far_el2 & ((1 << 12) - 1));

	switch (Iss::Access_size::get(state.esr_el2)) {
	case Iss::Access_size::BYTE:
		{
			uint8_t * p = (uint8_t*) &state.r[idx];
			wr ? write(p, off, cpu) : read(p, off, cpu);
			break;
		}
	case Iss::Access_size::HALFWORD:
		{
			uint16_t * p = (uint16_t*) &state.r[idx];
			wr ? write(p, off, cpu) : read(p, off, cpu);
			break;
		}
	case Iss::Access_size::WORD:
		{
			uint32_t * p = (uint32_t*) &state.r[idx];
			wr ? write(p, off, cpu) : read(p, off, cpu);
			break;
		}
	default:
		throw Error("Device %s: invalid alignment", name());
	};
}
