/*
 * \brief  Timer driver for core
 * \author Martin Stein
 * \date   2012-04-23
 */

/*
 * Copyright (C) 2012-2013 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include <base/printf.h>

namespace Genode
{
	/**
	 * Timer driver for core
	 */
	class Timer;
}

struct Genode::Timer
{
	public:

		/**
		 * Start single timeout run
		 *
		 * \param tics  delay of timer interrupt
		 */
		void start_one_shot(unsigned const tics, unsigned)
		{
			PDBG("not impl");
		}

		/**
		 * Stop the timer from a one-shot run
		 *
		 * \return  last native timer value of the one-shot run
		 */
		unsigned long stop_one_shot()
		{
			PDBG("not impl");
			return 0;
		}

		/**
		 * Translate milliseconds to a native timer value
		 */
		unsigned ms_to_tics(unsigned const ms)
		{
			PDBG("not impl");
			return 0;
		}

		/**
		 * Translate native timer value to milliseconds
		 */
		unsigned tics_to_ms(unsigned const tics)
		{
			PDBG("not impl");
			return 0;
		}

		/**
		 * Return current native timer value
		 */
		unsigned value(unsigned const)
		{
			PDBG("not impl");
			return 0;
		}

		static unsigned interrupt_id(int) { PDBG("not impl"); return  0; }
};

namespace Kernel { class Timer : public Genode::Timer { }; }

#endif /* _TIMER_H_ */
