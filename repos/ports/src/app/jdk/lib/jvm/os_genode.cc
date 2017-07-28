#include <runtime/os.hpp>

#include <base/log.h>

#define NOT_IMPL Genode::error(__func__, " not implemented ");


/**
 * Memory
 */


julong os::physical_memory()
{
	NOT_IMPL;
	return 0;
}


char* os::pd_attempt_reserve_memory_at(size_t bytes, char* requested_addr)
{
	NOT_IMPL;
	return nullptr;
}


bool os::pd_uncommit_memory(char* addr, size_t size)
{
	NOT_IMPL;
	return false;
}


/**
 * CPU/Thread
 */

void os::get_summary_cpu_info(char* buf, size_t buflen)
{
	NOT_IMPL;
}


/**
 * FS
 */

bool os::dir_is_empty(const char* path)
{
	NOT_IMPL;
	return false;
}


/**
 * Time
 */

jlong os::current_thread_cpu_time()
{
	NOT_IMPL;
	return 0;
}


bool os::supports_vtime()
{
	NOT_IMPL;
	return true;
}


/**
 * Init
 */

jint os::init_2(void)
{
	NOT_IMPL;
	return 0;
}
