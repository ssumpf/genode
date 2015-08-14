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

#include <machine_call.h>

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

				Machine::call(Machine::PUT_CHAR,  c | STDOUT | WRITE_CMD);
			}
	};
}

#endif /* _SERIAL_H_ */
