#include <stdio.h>

extern "C" void test_shared_lib_func()
{
	fprintf(stderr, "test_shared_lib_func(): hello\n");
}
