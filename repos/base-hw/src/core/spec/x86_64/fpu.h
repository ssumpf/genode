/*
 * \brief  x86_64 FPU driver for core
 * \author Adrian-Ken Rueegsegger
 * \author Martin stein
 * \author Reto Buerki
 * \author Stefan Kalkowski
 * \date   2016-01-19
 */

/*
 * Copyright (C) 2016-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _CORE__SPEC__X86_64__FPU_H_
#define _CORE__SPEC__X86_64__FPU_H_

/* Genode includes */
#include <base/stdint.h>
#include <util/misc_math.h>

namespace Genode { class Fpu_context; }

class Genode::Fpu_context
{
	addr_t _fxsave_addr { 0 };
	/*
	 * FXSAVE area providing storage for x87 FPU, MMX, XMM,
	 * and MXCSR registers.
	 *
	 * For further details see Intel SDM Vol. 2A,
	 * 'FXSAVE instruction'.
	 */
	char   _fxsave_area[527];

	public:

		Fpu_context()
		{
			_fxsave_addr = align_addr((addr_t)_fxsave_area, 4);

			unsigned value = 0x1f80;
			asm volatile ("fninit");
			asm volatile ("ldmxcsr %0" : : "m" (value));
		}

		addr_t fpu_context() const { return _fxsave_addr; }
};

#endif /* _CORE__SPEC__X86_64__FPU_H_ */
