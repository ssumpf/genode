/**
 * \brief  Lx_emul support to debug Linux kernel ports
 * \author Stefan Kalkowski
 * \date   2021-03-16
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((noreturn)) void lx_emul_trace_and_stop(const char * func);

void lx_emul_trace(const char * func);

#ifdef __cplusplus
}
#endif

