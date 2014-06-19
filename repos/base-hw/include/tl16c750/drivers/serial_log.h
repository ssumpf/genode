/*
 * \brief  Serial output driver specific for the Texas Instruments TL16C750
 * \author Martin Stein
 * \date   2012-04-23
 */

/*
 * Copyright (C) 2012-2013 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#ifndef _INCLUDE__TL16C750__DRIVERS__SERIAL_LOG_H_
#define _INCLUDE__TL16C750__DRIVERS__SERIAL_LOG_H_

/* Genode includes */
#include <board.h>
#include <drivers/uart/tl16c750_base.h>

namespace Genode
{
	/**
	 * Serial output driver specific for the Texas Instruments TL16C750
	 */
	class Serial_log : public Tl16c750_base
	{
		public:

			static constexpr size_t IRQ = Board_base::TL16C750_3_IRQ;

			/**
			 * Constructor
			 *
			 * \param baud_rate  targeted transfer baud-rate
			 */
			Serial_log(unsigned const baud_rate) :
				Tl16c750_base(Board::TL16C750_3_MMIO_BASE,
				              Board::TL16C750_CLOCK, baud_rate)
			{ }
	};
}

#endif /* _INCLUDE__TL16C750__DRIVERS__SERIAL_LOG_H_ */

