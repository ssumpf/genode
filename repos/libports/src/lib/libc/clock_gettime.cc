/*
 * \brief  C-library back end
 * \author Christian Prochaska
 * \date   2010-05-19
 */

/*
 * Copyright (C) 2010-2013 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

/* Libc includes */
#include <sys/time.h>

#include "task.h"


namespace Libc {
extern time_t read_rtc();
}


extern "C" __attribute__((weak))
int clock_gettime(clockid_t clk_id, struct timespec *tp)
{
	if (!tp) return 0;

	static bool read_rtc = false;
	static time_t rtc = 0;

	if (!read_rtc) {
		rtc = Libc::read_rtc();
		read_rtc = true;
	}

	unsigned long time = Libc::current_time();

	tp->tv_sec  = rtc + time/1000;
	tp->tv_nsec = (time % 1000) * (1000*1000);

	return 0;
}
