/**
 * \brief  Lx_emul support to register Linux kernel initialization
 * \author Stefan Kalkowski
 * \date   2021-03-10
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void lx_emul_register_initcall(int (*initcall)(void), int prio);

int lx_emul_init_kernel(void);
int lx_emul_start_kernel(void);

#ifdef __cplusplus
}
#endif
