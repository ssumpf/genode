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
				unsigned err = 1;

				while (err)
					asm volatile ("csrrw %0, tohost, %1\n"
					              : "=r" (err) : "r" (c));
			}
	};
}

#endif /* _SERIAL_H_ */
