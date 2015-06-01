/**
 * \brief  Memory barrier
 * \author Sebastian Sumpf
 * \date   2015-06-01
 */

#ifndef _INCLUDE__RISCV__CPU__MEMORY_BARRIER_H_
#define _INCLUDE__RISCV__CPU__MEMORY_BARRIER_H_

namespace Genode {

	static inline void memory_barrier()
	{
		asm volatile ("fence" ::: "memory");
	}
}

#endif /* _INCLUDE__RISCV__CPU__MEMORY_BARRIER_H_ */
