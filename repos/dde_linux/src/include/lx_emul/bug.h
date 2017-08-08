/*
 * \brief  Linux kernel API
 * \author Norman Feske
 * \author Sebastian Sumpf
 * \author Josef Soentgen
 * \date   2014-08-21
 *
 * Based on the prototypes found in the Linux kernel's 'include/'.
 */

/*
 * Copyright (C) 2014-2017 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

/***************
 ** asm/bug.h **
 ***************/

#define WARN_ON(condition) ({ \
	int __ret = !!(condition); \
	if (__ret) lx_printf("[%s] WARN_ON(" #condition ") \n", __func__); \
	__ret; })

#define WARN(condition, fmt, arg...) ({ \
	int __ret = !!(condition); \
	if (__ret) lx_printf("[%s] *WARN* " fmt " \n", __func__ , ##arg); \
	__ret; })

#define BUG() do { \
	lx_printf("BUG: failure at %s:%d/%s()!\n", __FILE__, __LINE__, __func__); \
	while (1); \
} while (0)

#define WARN_ON_ONCE WARN_ON
#define WARN_ONCE    WARN

#define BUG_ON(condition) do { if (condition) BUG(); } while(0)

#define BUILD_BUG_ON_MSG(cond,msg) ({ \
		extern int __attribute__((error(msg))) build_bug(); \
		if (cond) { build_bug(); } })

#define BUILD_BUG() BUILD_BUG_ON_MSG(1,"BUILD_BUG failed")
