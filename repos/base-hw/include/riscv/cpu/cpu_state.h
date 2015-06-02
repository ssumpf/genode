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
	addr_t sp;
	addr_t ip;
};

#endif /* _INCLUDE__RISCV__CPU__CPU_STATE_H_ */
