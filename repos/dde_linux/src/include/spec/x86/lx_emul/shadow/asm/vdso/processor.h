/**
 * \brief  Shadow copy of asm/vdso/processor.h
 * \author Alexander Boettcher
 * \date   2022-03-23
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __ASM_VDSO_PROCESSOR_H
#define __ASM_VDSO_PROCESSOR_H

#ifndef __ASSEMBLY__

#include <asm-generic/delay.h>

extern u64 jiffies_64;


static __always_inline void rep_nop(void)
{
	asm volatile("rep; nop" ::: "memory");
}


static __always_inline void cpu_relax(void)
{
	rep_nop();
	/* break busy loop of slchi() in drivers/i2c/algos/i2c-algo-bit.c */
	udelay(1);
	jiffies_64 += 1;
}

#endif /* __ASSEMBLY__ */

#endif /* __ASM_VDSO_PROCESSOR_H */
