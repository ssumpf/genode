#include <lx_emul.h>


DEFINE_STATIC_KEY_FALSE(force_irqthreads_key);
DEFINE_STATIC_KEY_FALSE(bpf_stats_enabled_key);
DEFINE_STATIC_KEY_FALSE(bpf_master_redirect_enabled_key);
DEFINE_STATIC_KEY_FALSE(memalloc_socks_key);

unsigned long __FIXADDR_TOP = 0xfffff000;

bool arm64_use_ng_mappings = false;


#ifdef __i386__
asmlinkage __wsum csum_partial(const void * buff,int len,__wsum sum)
#else
__wsum csum_partial(const void * buff,int len,__wsum sum)
#endif
{
	lx_emul_trace_and_stop(__func__);
}


#ifdef __arm__
#include <asm/uaccess.h>

unsigned long arm_copy_to_user(void *to, const void *from, unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}

asmlinkage void __div0(void);
asmlinkage void __div0(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-map-ops.h>

void arch_teardown_dma_ops(struct device * dev)
{
	lx_emul_trace(__func__);
}


extern void arm_heavy_mb(void);
void arm_heavy_mb(void)
{
	// FIXME: on Cortex A9 we potentially need to flush L2-cache
	lx_emul_trace(__func__);
}

#else

#include <linux/timekeeper_internal.h>
void update_vsyscall(struct timekeeper * tk)
{
	lx_emul_trace(__func__);
}

#endif



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


#include <linux/rcupdate.h>

void synchronize_rcu(void)
{
	lx_emul_trace(__func__);
}


#include <net/net_namespace.h>

void __init net_ns_init(void)
{
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


#include <linux/usb/hcd.h>

void usb_hcd_synchronize_unlinks(struct usb_device * udev)
{
	lx_emul_trace(__func__);
}


#include <linux/usb.h>

int usb_string(struct usb_device * dev,int index,char * buf,size_t size)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/usb.h>

struct urb * usb_get_from_anchor(struct usb_anchor * anchor)
{
	lx_emul_trace(__func__);
	return NULL;
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


#include <linux/usb.h>

int usb_unlink_urb(struct urb * urb)
{
	lx_emul_trace(__func__);
	return 0;
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


#include <linux/rtnetlink.h>

int rtnl_lock_killable(void)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/rtnetlink.h>

void rtnl_lock(void)
{
	lx_emul_trace(__func__);
}


#include <linux/rtnetlink.h>

int rtnl_is_locked(void)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/rtnetlink.h>

struct sk_buff * rtmsg_ifinfo_build_skb(int type,struct net_device * dev,unsigned int change,u32 event,gfp_t flags,int * new_nsid,int new_ifindex)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/stringhash.h>

unsigned int full_name_hash(const void * salt,const char * name,unsigned int len)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/random.h>

void add_device_randomness(const void * buf,size_t len)
{
	lx_emul_trace(__func__);
}


#include <linux/rtnetlink.h>

void rtnl_unlock(void)
{
	lx_emul_trace(__func__);
}


#include <net/gen_stats.h>

void gnet_stats_basic_sync_init(struct gnet_stats_basic_sync * b)
{
	lx_emul_trace(__func__);
}


#include <net/gen_stats.h>

void gen_kill_estimator(struct net_rate_estimator __rcu ** rate_est)
{
	lx_emul_trace(__func__);
}


#include <asm-generic/softirq_stack.h>

void do_softirq_own_stack(void)
{
	lx_emul_trace(__func__);
}


#include <linux/of_net.h>
#if defined(CONFIG_OF) && defined(CONFIG_NET)
int of_get_mac_address(struct device_node * np,u8 * addr)
{
	lx_emul_trace(__func__);
	return -1;
}
#endif


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


extern void usb_remove_sysfs_dev_files(struct usb_device * udev);
void usb_remove_sysfs_dev_files(struct usb_device * udev)
{
	lx_emul_trace(__func__);
}


extern void usb_remove_sysfs_intf_files(struct usb_interface * intf);
void usb_remove_sysfs_intf_files(struct usb_interface * intf)
{
	lx_emul_trace(__func__);
}


extern void usb_create_sysfs_intf_files(struct usb_interface * intf);
void usb_create_sysfs_intf_files(struct usb_interface * intf)
{
	lx_emul_trace(__func__);
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


extern int usb_create_ep_devs(struct device * parent,struct usb_host_endpoint * endpoint,struct usb_device * udev);
int usb_create_ep_devs(struct device * parent,struct usb_host_endpoint * endpoint,struct usb_device * udev)
{
	lx_emul_trace(__func__);
	return 0;
}


extern void usb_remove_ep_devs(struct usb_host_endpoint * endpoint);
void usb_remove_ep_devs(struct usb_host_endpoint * endpoint)
{
	lx_emul_trace(__func__);
}


extern void usb_disable_interface(struct usb_device * dev,struct usb_interface * intf,bool reset_hardware);
void usb_disable_interface(struct usb_device * dev,struct usb_interface * intf,bool reset_hardware)
{
	lx_emul_trace(__func__);
}


extern int netdev_register_kobject(struct net_device * ndev);
int netdev_register_kobject(struct net_device * ndev)
{
	lx_emul_trace(__func__);
	return 0;
}


extern void netdev_unregister_kobject(struct net_device * ndev);
void netdev_unregister_kobject(struct net_device * ndev)
{
	lx_emul_trace(__func__);
}
