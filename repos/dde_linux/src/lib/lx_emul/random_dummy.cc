/*
 * \brief  Dummy source of randomness in lx_emul
 * \author Josef Soentgen
 * \date   2023-06-13
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

/* base/include */
#include <base/log.h>
#include <base/fixed_stdint.h>
#include <util/string.h>

/* dde_linux/src/include */
#include <lx_emul/random.h>


using namespace Genode;

#define DUMMY_WARNING(fn) \
	do { warning(fn, " dummy implementation used, returning 0(s)"); } while (0)

void lx_emul_random_gen_bytes(void          *dst,
                              unsigned long  nr_of_bytes)
{
	/* validate arguments */
	if (dst == nullptr || nr_of_bytes == 0) {
		error(__func__, " called with invalid args!");
		return;
	}

	DUMMY_WARNING(__func__);
	memset(dst, 0, nr_of_bytes);
}


genode_uint32_t lx_emul_random_gen_u32()
{
	DUMMY_WARNING(__func__);
	return 0;
}


genode_uint64_t lx_emul_random_gen_u64()
{
	DUMMY_WARNING(__func__);
	return 0;
}

#undef DUMMY_WARNING
