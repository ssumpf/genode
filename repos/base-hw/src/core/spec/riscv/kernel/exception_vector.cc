#include <kernel/cpu.h>

extern int _machine_begin, _machine_end;

extern "C" void setup_riscv_exception_vector()
{
	using namespace Genode;

	/* retrieve exception vector */
	addr_t vector;
	asm volatile ("csrr %0, mtvec\n" : "=r"(vector));

	/* copy  machine mode exception vector */
	memcpy((void *)vector,
	       &_machine_begin, (addr_t)&_machine_end - (addr_t)&_machine_begin);
}
