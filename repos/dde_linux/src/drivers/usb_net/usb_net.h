/*
 * \brief  C/C++ interface for this driver
 * \author Sebastian Sumpf
 * \date   2023-07-11
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul/usb_client.h>

#ifdef __cplusplus
extern "C" {
#endif

struct task_struct;

int                 lx_user_main_task(void *);
struct task_struct *lx_user_new_usb_task(int (*func)(void*), void *args);


#ifdef __cplusplus
} /* extern "C" */
#endif


