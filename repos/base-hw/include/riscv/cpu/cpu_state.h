/**
 * \brief  CPU state
 * \author Sebastian Sumpf
 * \date   2015-06-01
 */

#ifndef _INCLUDE__RISCV__CPU__CPU_STATE_H_
#define _INCLUDE__RISCV__CPU__CPU_STATE_H_

#include <base/stdint.h>

namespace Genode {
	struct Cpu_state;
}

struct Genode::Cpu_state
{
	addr_t sp  = 0;
	addr_t ip  = 0;
	addr_t ra  = 0;
	addr_t s0  = 0;
	addr_t s1  = 0;
	addr_t s2  = 0;
	addr_t s3  = 0;
	addr_t s4  = 0;
	addr_t s5  = 0;
	addr_t s6  = 0;
	addr_t s7  = 0;
	addr_t s8  = 0;
	addr_t s9  = 0;
	addr_t s10 = 0;
	addr_t s11 = 0;
	addr_t tp  = 0;
	addr_t v0  = 0;
	addr_t v1  = 0;
	addr_t a0  = 0;
	addr_t a1  = 0;
	addr_t a2  = 0;
	addr_t a3  = 0;
	addr_t a4  = 0;
	addr_t a5  = 0;
	addr_t a6  = 0;
	addr_t a7  = 0;
	addr_t t0  = 0;
	addr_t t1  = 0;
	addr_t t2  = 0;
	addr_t t3  = 0;
	addr_t t4  = 0;
	addr_t gp  = 0;
};

#endif /* _INCLUDE__RISCV__CPU__CPU_STATE_H_ */
