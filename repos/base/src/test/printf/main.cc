/*
 * \brief  Testing 'printf()' with negative integer
 * \author Christian Prochaska
 * \date   2012-04-20
 *
 */

/*
 * Copyright (C) 2012-2013 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#include <base/printf.h>

#include <nova/syscalls.h>

int main(int argc, char **argv)
{
	Nova::debug(reinterpret_cast<Nova::mword_t>(__builtin_return_address(0)));

	Genode::printf("-1 = %d = %ld\n", -1, -1L);

	return 0;
}
