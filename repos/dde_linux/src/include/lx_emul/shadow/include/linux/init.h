/*
 * \brief  Shadow copy of linux/init.h
 * \author Stefan Kalkowski
 * \date   2021-03-10
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#ifndef _LX_EMUL__SHADOW__LINUX__INIT_H_
#define _LX_EMUL__SHADOW__LINUX__INIT_H_

#include_next <linux/init.h>
#include      <lx_emul/init.h>

/**
 * We have to re-define certain initcall macros, because the original function
 * puts all initcalls into the .init section that is not exported by our
 * linker script.
 * Instead, we define ctor functions that register the initcalls and their
 * priority in our lx_emul environment.
 */
#undef ___define_initcall
#undef __define_initcall

#define __define_initcall(fn, id) \
	static void __initcall_##fn##id(void) { \
		lx_emul_register_initcall(fn, __func__); } \
	void * __initptr_##fn##id = __initcall_##fn##id;

#undef __setup

#define __setup(str, fn) \
	int __setup_##fn(char * string) { return fn(string); }

#endif /* _LX_EMUL__SHADOW__LINUX__INIT_H_ */
