#include <lx_emul.h>


DEFINE_STATIC_KEY_FALSE(force_irqthreads_key);
DEFINE_STATIC_KEY_FALSE(bpf_stats_enabled_key);
DEFINE_STATIC_KEY_FALSE(bpf_master_redirect_enabled_key);
DEFINE_STATIC_KEY_FALSE(memalloc_socks_key);

__wsum csum_partial(const void * buff,int len,__wsum sum)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>
#include <linux/jump_label.h> /* for DEFINE_STATIC_KEY_FALSE */

void bpf_prog_change_xdp(struct bpf_prog *prev_prog, struct bpf_prog *prog)
{
	lx_emul_trace(__func__);
}


#include <linux/rcutree.h>

void synchronize_rcu_expedited(void)
{
	lx_emul_trace(__func__);
}


#include <linux/timekeeper_internal.h>
void update_vsyscall(struct timekeeper * tk)
{
	lx_emul_trace(__func__);
}


#include <net/net_namespace.h>

void __init net_ns_init(void)
{
	printk("%s:%d NET_NS_INIT\n", __func__, __LINE__);
	lx_emul_trace(__func__);
}


#include <linux/kobject.h>

int kobject_uevent(struct kobject * kobj,enum kobject_action action)
{
	lx_emul_trace(__func__);
	return 0;
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


void usb_kill_urb(struct urb * urb)
{
	lx_emul_trace(__func__);
}


#include <linux/usb/hcd.h>

struct usb_hcd * usb_get_hcd(struct usb_hcd * hcd)
{
	lx_emul_trace(__func__);
	return hcd;
}


#include <linux/usb/hcd.h>

void usb_put_hcd(struct usb_hcd * hcd)
{
	lx_emul_trace(__func__);
}


extern int __init netdev_kobject_init(void);
int __init netdev_kobject_init(void)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/netdevice.h>

void dev_add_offload(struct packet_offload * po)
{
	lx_emul_trace(__func__);
}


#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
{
	lx_emul_trace(__func__);
}


#include <linux/kernel.h>

bool parse_option_str(const char * str,const char * option)
{
	lx_emul_trace(__func__);
	return false;
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


extern void software_node_notify_remove(struct device * dev);
void software_node_notify_remove(struct device * dev)
{
	lx_emul_trace(__func__);
}


extern int usb_create_sysfs_dev_files(struct usb_device * udev);
int usb_create_sysfs_dev_files(struct usb_device * udev)
{
	lx_emul_trace(__func__);
	return 0;
}

extern void usb_create_sysfs_intf_files(struct usb_interface * intf);
void usb_create_sysfs_intf_files(struct usb_interface * intf)
{
	lx_emul_trace(__func__);
}
