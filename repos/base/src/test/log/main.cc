/*
 * \brief  Testing 'Genode::log()' and LOG session
 * \author Christian Prochaska
 * \date   2012-04-20
 *
 */

/*
 * Copyright (C) 2012-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <base/component.h>
#include <base/log.h>
#include <log_session/connection.h>

#include <libc/component.h>
#include <time.h>

char const *get_time()
{
	static char buffer[32];

	char const *p = "<invalid date>";
	Libc::with_libc([&] {
		struct timespec ts;
		if (clock_gettime(CLOCK_MONOTONIC, &ts)) { Genode::log("1"); return; }
	
		struct tm *tm = localtime((time_t*)&ts.tv_sec);
		if (!tm) { Genode::log("2");return; }

		mktime(tm);

		size_t const n = strftime(buffer, sizeof(buffer), "%F %H:%M:%S", tm);
		if (n > 0 && n < sizeof(buffer)) { p = buffer; }
	}); /* Libc::with_libc */

	return p;
}


void Libc::Component::construct(Libc::Env &)
{
	char const *t = get_time();
	Genode::log("time: ", t);
}
