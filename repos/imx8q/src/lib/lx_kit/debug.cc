/**
 * \brief  Lx_kit backend for Linux kernel' debug functions
 * \author Stefan Kalkowski
 * \date   2021-03-16
 */

#include <base/log.h>
#include <base/sleep.h>
#include <os/backtrace.h>

#include <lx_emul/debug.h>

extern "C" void lx_emul_trace_and_stop(const char * func)
{
	Genode::error("Function ", func, " not implemented yet!");
	Genode::log("Backtrace follows:");
	Genode::backtrace();
	Genode::log("Will sleep forever...");
	Genode::sleep_forever();
}


extern "C" void lx_emul_trace(const char * func)
{
	Genode::warning("Function ", func, " not implemented yet!");
}
