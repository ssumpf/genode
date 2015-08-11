/*
 * \brief  Serial output driver for core
 * \author Sebastian Sumpf
 * \date   2015-06-02
 */

/*
 * Copyright (C) 2012-2013 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <base/stdint.h>

namespace Genode
{
	/**
	 * Serial output driver for core
	 */
	class Serial
	{
		public:

			/**
			 * Constructor
			 */
			Serial(unsigned) { }
		
			void put_char(char const c)
			{
				enum {
					STDOUT      = 1UL << 56,
					WRITE_CMD   = 1UL << 48,
				};

				register unsigned  syscall   asm("a0") = 1;
				register addr_t    character asm("a1") = c | STDOUT | WRITE_CMD;
				asm volatile ("ecall\n" : : "r"(syscall), "r"(character));
#if 0
				unsigned err = 1;


				addr_t packet = STDOUT | WRITE_CMD | c;
				while (err)
					asm volatile ("csrrw %0, mtohost, %1\n"
					              : "=r" (err) : "r" (packet));

				err = 1;
				packet = 0;
				while (err != 0)
					asm volatile("csrrw %0, mfromhost, %1\n"
					              : "=r" (err) : "r" (packet));
#endif
			}
	};
}

#endif /* _SERIAL_H_ */
