#include <linux/sched/task.h>
#include <linux/init.h>

#include "lx_user.h"


struct task_struct *lx_user_new_task(int (*func)(void*), void *args)
{
	int pid = kernel_thread(func, args, CLONE_FS | CLONE_FILES);
	return find_task_by_pid_ns(pid, NULL);
}


void lx_user_destroy_task(struct task_struct *task)
{
	if (task != current) {
		printk("%s: task: %px is not current: %px\n", __func__,
		       task, current);
		return;
	}

	do_exit(0);
}


static int _startup_finished = 0;

int lx_user_startup_complete(void *) { return _startup_finished; }


static struct task_struct *_socket_dispatch_root = NULL;

struct task_struct *lx_socket_dispatch_root(void)
{
	return _socket_dispatch_root;
}



int __setup_ip_auto_config_setup(char *);
int __initcall_ip_auto_config7(void);

void lx_user_init(void)
{
	_socket_dispatch_root = lx_user_new_task(lx_socket_dispatch,
	                                         lx_socket_dispatch_queue());
	_startup_finished = 1;
}
