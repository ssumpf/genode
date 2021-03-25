/**
 * \brief  Lx_emul support for printing in Linux kernel ports
 * \author Josef Soentgen
 * \date   2021-03-22
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

void lx_emul_printf(char const *, ...) __attribute__((format(printf, 1, 2)));
void lx_emul_vprintf(char const *, va_list);
int  lx_emul_vsnprintf(char *dst, unsigned long size, const char *format, va_list args);

#ifdef __cplusplus
}
#endif

