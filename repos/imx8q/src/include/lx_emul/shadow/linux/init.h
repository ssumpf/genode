/**
 * \brief  Shadow copy of linux/init.h
 * \author Stefan Kalkowski
 * \date   2021-03-10
 */

#pragma once

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
#undef core_initcall
#undef core_initcall_sync
#undef postcore_initcall
#undef postcore_initcall_sync
#undef arch_initcall
#undef arch_initcall_sync
#undef subsys_initcall
#undef subsys_initcall_sync
#undef fs_initcall
#undef fs_initcall_sync
#undef device_initcall
#undef device_initcall_sync
#undef late_initcall
#undef late_initcall_sync
#undef early_initcall
#undef rootfs_initcall
#undef console_initcall

#define __define_initcall(fn, id) \
	static void __initcall_##fn##id(void)__attribute__((constructor)); \
	static void __initcall_##fn##id() { \
			lx_emul_register_initcall(fn, id); };


#define core_initcall(fn)           __define_initcall(fn, 1)
#define core_initcall_sync(fn)      __define_initcall(fn, 2)
#define postcore_initcall(fn)       __define_initcall(fn, 3)
#define postcore_initcall_sync(fn)  __define_initcall(fn, 4)
#define arch_initcall(fn)           __define_initcall(fn, 5)
#define arch_initcall_sync(fn)      __define_initcall(fn, 6)
#define subsys_initcall(fn)         __define_initcall(fn, 7)
#define subsys_initcall_sync(fn)    __define_initcall(fn, 8)
#define fs_initcall(fn)             __define_initcall(fn, 9)
#define fs_initcall_sync(fn)        __define_initcall(fn, 10)
#define device_initcall(fn)         __define_initcall(fn, 11)
#define device_initcall_sync(fn)    __define_initcall(fn, 12)
#define late_initcall(fn)           __define_initcall(fn, 13)
#define late_initcall_sync(fn)      __define_initcall(fn, 14)
