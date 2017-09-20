#include <base/log.h>
#include <os/backtrace.h>

extern "C" {
#include <pwd.h>
}
#define WARN_NOT_IMPL Genode::warning(__func__, " not implemented");

extern "C" void collector_func_load(char* name,
                                   void* null_argument_1,
                                   void* null_argument_2,
                                   void *vaddr,
                                   int size,
                                   int zero_argument,
                                   void* null_argument_3)
{ }


int getpwuid_r(uid_t uid, struct passwd *pwd,
                      char *buf, size_t buflen, struct passwd **result)
{
	*result = nullptr;
	return -1;
}

extern "C" void backtrace()
{
	Genode::backtrace();
}
