#include <lx_emul.h>

#include <linux/interrupt.h>

DEFINE_STATIC_KEY_FALSE(force_irqthreads_key);

#include <linux/uaccess.h>

unsigned long __must_check clear_user(void __user *mem, unsigned long len)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


#include <linux/random.h>

u32 __get_random_u32_below(u32 ceil)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


#include <linux/context_tracking_irq.h>

noinstr void ct_irq_enter(void)
{
	lx_emul_trace(__func__);
}


#include <linux/context_tracking_irq.h>

noinstr void ct_irq_exit(void)
{
	lx_emul_trace(__func__);
}


#include <net/net_namespace.h>

void net_ns_init(void)
{
	lx_emul_trace(__func__);
}


#include <linux/kobject.h>

int kobject_uevent(struct kobject * kobj,enum kobject_action action)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/fs.h>

int register_chrdev_region(dev_t from,unsigned count,const char * name)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
{
	lx_emul_trace(__func__);
}


#include <linux/usb/hcd.h>

void __init usb_init_pool_max(void)
{
	lx_emul_trace(__func__);
}


extern int usb_major_init(void);
int usb_major_init(void)
{
	lx_emul_trace(__func__);
	return 0;
}


extern int __init usb_devio_init(void);
int __init usb_devio_init(void)
{
	lx_emul_trace(__func__);
	return 0;
}





#if 0
#include <linux/usb.h>

int usb_disabled(void)
{
	lx_emul_trace(__func__);
	return 0;
}
#endif
