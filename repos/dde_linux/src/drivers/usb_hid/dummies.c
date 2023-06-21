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


#include <linux/refcount.h>

void refcount_warn_saturate(refcount_t * r,enum refcount_saturation_type t)
{
	lx_emul_trace(__func__);
}


#include <linux/semaphore.h>

int __sched down_interruptible(struct semaphore * sem)
{
	lx_emul_trace(__func__);
	return 0;
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


#include <linux/usb.h>

int usb_string(struct usb_device * dev,int index,char * buf,size_t size)
{
	lx_emul_trace(__func__);
	return 0;
}


extern char * usb_cache_string(struct usb_device * udev,int index);
char * usb_cache_string(struct usb_device * udev,int index)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/usb/hcd.h>

struct usb_hcd * usb_get_hcd(struct usb_hcd * hcd)
{
	lx_emul_trace(__func__);
	return hcd;
}


#include <linux/kernel.h>

bool parse_option_str(const char * str,const char * option)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/semaphore.h>

void __sched up(struct semaphore * sem)
{
	lx_emul_trace(__func__);
}


#include <linux/semaphore.h>

void __sched down(struct semaphore * sem)
{
	lx_emul_trace(__func__);
}


#include <linux/semaphore.h>

int __sched down_trylock(struct semaphore * sem)
{
	lx_emul_trace(__func__);
	return 0;
}


extern void usb_enable_endpoint(struct usb_device * dev,struct usb_host_endpoint * ep,bool reset_ep);
void usb_enable_endpoint(struct usb_device * dev,struct usb_host_endpoint * ep,bool reset_ep)
{
	lx_emul_trace(__func__);
}


extern void software_node_notify(struct device * dev);
void software_node_notify(struct device * dev)
{
	lx_emul_trace(__func__);
}


extern int usb_create_sysfs_dev_files(struct usb_device * udev);
int usb_create_sysfs_dev_files(struct usb_device * udev)
{
	lx_emul_trace(__func__);
	return 0;
}


extern int usb_create_ep_devs(struct device * parent,struct usb_host_endpoint * endpoint,struct usb_device * udev);
int usb_create_ep_devs(struct device * parent,struct usb_host_endpoint * endpoint,struct usb_device * udev)
{
	lx_emul_trace(__func__);
	return 0;
}


extern void usb_notify_add_device(struct usb_device * udev);
void usb_notify_add_device(struct usb_device * udev)
{
	lx_emul_trace(__func__);
}


extern void usb_notify_remove_device(struct usb_device * udev);
void usb_notify_remove_device(struct usb_device * udev)
{
	lx_emul_trace(__func__);
}


extern void usb_create_sysfs_intf_files(struct usb_interface * intf);
void usb_create_sysfs_intf_files(struct usb_interface * intf)
{
	lx_emul_trace(__func__);
}








#if 0
#include <linux/usb.h>

int usb_disabled(void)
{
	lx_emul_trace(__func__);
	return 0;
}
#endif
