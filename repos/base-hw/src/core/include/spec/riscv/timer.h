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
#include <base/stdint.h>

#include <machine_call.h>

namespace Genode
{
	/**
	 * Timer driver for core
	 */
	class Timer;
}

struct Genode::Timer
{
	private:

		addr_t _timeout = 0;

		addr_t _stime()
		{
			addr_t t;
			asm volatile ("csrr %0, stime\n" : "=r"(t));
			return t;
		}

	public:

		enum {
			SPIKE_TIMER_HZ = 500000,
			MS_TICS        = SPIKE_TIMER_HZ / 1000,
		};

		/**
		 * Start single timeout run
		 *
		 * \param tics  delay of timer interrupt
		 */
		void start_one_shot(unsigned const tics, unsigned /* cpu */)
		{
			_timeout = _stime() + tics;
			Machine::call(Machine::PROGRAM_TIMER, _timeout);
		}

		/**
		 * Translate milliseconds to a native timer value
		 */
		unsigned ms_to_tics(unsigned const ms)
		{
			return ms * MS_TICS;
		}

		/**
		 * Translate native timer value to milliseconds
		 */
		unsigned tics_to_ms(unsigned const tics)
		{
			return tics / MS_TICS;
		}

		/**
		 * Return current native timer value
		 */
		unsigned value(unsigned const)
		{
			addr_t time = _stime();
			return time < _timeout ? _timeout - time : 0;
		}

		static unsigned interrupt_id(int) { return 1; }
};

namespace Kernel { class Timer : public Genode::Timer { }; }

#endif /* _TIMER_H_ */
