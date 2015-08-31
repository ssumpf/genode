/* core includes */
#include <kernel/cpu.h>


/*************************
 ** Kernel::Cpu_context **
 *************************/

void Kernel::Cpu_context::_init(size_t const stack_size, addr_t const table)
{
	/*
	 * the stack pointer already contains the stack base address
	 * of all CPU's kernel stacks, on this uni-processor platform
	 * it is sufficient to increase it by the stack's size
	 */
	sp = sp + stack_size;
}
