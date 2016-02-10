#ifndef _MACHINE_CALL_H_
#define _MACHINE_CALL_H_

#include <base/stdint.h>

namespace Machine {

	/**
	 * SBI calls to machine.
	 * Keep in sync with mode_transition.s.
	 */
	enum Call {
		PUT_CHAR      = 0x100,
		SET_SYS_TIMER = 0x101,
		IS_USER_MODE  = 0x102,
	};

	inline Genode::addr_t call(Call const number, Genode::addr_t const arg0)
	{
		register Genode::addr_t a0 asm("a0") = number;;
		register Genode::addr_t a1 asm("a1") = arg0;

		asm volatile ("ecall\n" : "+r"(a0) : "r"(a1));
		return a0;
	}
}

#endif /* _MACHINE_CALL_H_ */
