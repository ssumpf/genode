#include <linux/printk.h>

void lx_user_init(void)
{
	printk("%s:%d\n", __func__, __LINE__);
}

