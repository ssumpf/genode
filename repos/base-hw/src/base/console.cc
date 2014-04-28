/*
 * \brief  core console backend
 * \author Martin Stein
 * \date   2011-10-17
 */

/*
 * Copyright (C) 2011-2013 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

/* core includes */
#include <platform_console.h>

/* base includes */
#include <unmanaged_singleton.h>

/**
 * Static object to print log output
 */
Genode::Platform_console * Genode::platform_console()
{
	using namespace Genode;

	return unmanaged_singleton<Platform_console>();
}


/****************************
 ** Genode print functions **
 ****************************/

void Genode::printf(const char *format, ...)
{
	using namespace Genode;

	va_list list;
	va_start(list, format);
	platform_console()->vprintf(format, list);
	va_end(list);
}


void Genode::vprintf(const char *format, va_list list) {
	Genode::platform_console()->vprintf(format, list); }

