#include <linux/sched/task.h>

#include <linux/init.h>


int __setup_ip_auto_config_setup(char *);
int __initcall_ip_auto_config7(void);

void lx_user_init(void)
{
	printk("%s:%d\n", __func__, __LINE__);
	printk("Configuring as DHCP client ...\n");
	__setup_ip_auto_config_setup("dhcp");
	printk("Starting DHCP client ...\n");
	lx_emul_initcall("__initcall_ip_auto_config7");
}
