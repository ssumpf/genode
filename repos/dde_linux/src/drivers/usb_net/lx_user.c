/*
 * \brief  Post kernel activity
 * \author Sebastian Sumpf
 * \date   2023-06-29
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <linux/sched/task.h>
#include <usb_net.h>

struct task_struct *lx_user_new_usb_task(int (*func)(void*), void *args)
{
	int pid = kernel_thread(func, args, CLONE_FS | CLONE_FILES);
	return find_task_by_pid_ns(pid, NULL);
	return NULL;
}


void lx_user_init(void)
{
	lx_user_main_task(NULL);
}
