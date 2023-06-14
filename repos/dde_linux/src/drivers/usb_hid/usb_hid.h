/*
 * \brief  C/C++ interface for this driver
 * \author Sebastian Sumpf
 * \date   2023-06-29
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <genode_c_api/usb_client.h>

#ifdef __cplusplus
extern "C" {
#endif


void *lx_emul_usb_client_register_device(genode_usb_client_handle_t handle, char const *label);
void  lx_emul_usb_client_unregister_device(genode_usb_client_handle_t handle, void *data);

struct task_struct;

int                 lx_user_main_task(void *);
struct task_struct *lx_user_new_usb_task(int (*func)(void*), void *args);
void                lx_user_destroy_usb_task(struct task_struct*);

void lx_led_state_update(bool capslock, bool numlock, bool scrlock);


#ifdef __cplusplus
} /* extern "C" */
#endif


