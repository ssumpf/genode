#include <base/log.h>

#define WARN_NOT_IMPL Genode::warning(__func__, " not implemented");

extern "C" void collector_func_load(char* name,
                                   void* null_argument_1,
                                   void* null_argument_2,
                                   void *vaddr,
                                   int size,
                                   int zero_argument,
                                   void* null_argument_3)
{
	WARN_NOT_IMPL;
}
