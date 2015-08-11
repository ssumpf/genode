#include <kernel/cpu.h>

extern int _mt_begin, _mt_end;

extern "C" void setup_riscv_exception_vector()
{
	using namespace Genode;

	/* set exception vector */
	asm volatile ("csrw mtvec, %0\n" : : "r"(Cpu::exception_entry));

	/* copy mode-transition page to exception vector address */
	memcpy((void *)Cpu::exception_entry,
	       &_mt_begin, (addr_t)&_mt_end - (addr_t)&_mt_begin);
}
