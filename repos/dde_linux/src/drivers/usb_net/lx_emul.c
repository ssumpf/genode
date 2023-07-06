#include <lx_emul.h>


pteval_t __default_kernel_pte_mask __read_mostly = ~0;

struct device_type usb_if_device_type = {
	.name = "usb_interface"
};

struct usb_driver usbfs_driver = {
	.name = "usbfs"
};

const struct attribute_group *usb_device_groups[] = { };


#include <linux/slab.h>

struct kmem_cache * kmem_cache_create_usercopy(const char * name,
                                               unsigned int size,
                                               unsigned int align,
                                               slab_flags_t flags,
                                               unsigned int useroffset,
                                               unsigned int usersize,
                                               void (* ctor)(void *))
{
	return kmem_cache_create(name, size, align, flags, ctor);
}


#include <net/net_namespace.h>

int register_pernet_subsys(struct pernet_operations *ops)
{
	if (ops->init)
		ops->init(&init_net);
	
	return 0;
}


int register_pernet_device(struct pernet_operations *ops)
{
	return register_pernet_subsys(ops);
}


#include <linux/netdevice.h>

void netif_carrier_on(struct net_device *dev)
{
	dev->state &= ~(1 << __LINK_STATE_NOCARRIER);
	printk("%s:%d TODO implement link state change\n", __func__, __LINE__);
//	if (dev->session_component)
//		reinterpret_cast<Linux_network_session_base*>(dev->session_component)->
//			link_state(true);
}


void netif_carrier_off(struct net_device *dev)
{
	dev->state |= 1 << __LINK_STATE_NOCARRIER;
	printk("%s:%d TODO implement link state change\n", __func__, __LINE__);
//	if (dev->session_component)
//		reinterpret_cast<Linux_network_session_base*>(dev->session_component)->
//			link_state(false);
}

#include <linux/rcutree.h>

/*
 * taken from src/lib/wifi/lx_emul.c
 */
void kvfree_call_rcu(struct rcu_head * head, rcu_callback_t func)
{
	void *ptr = (void *) head - (unsigned long) func;
	kvfree(ptr);
}


#include <linux/gfp.h>

unsigned long get_zeroed_page(gfp_t gfp_mask)
{
	return (unsigned long)kzalloc(PAGE_SIZE, GFP_KERNEL);
}


void free_pages(unsigned long addr,unsigned int order)
{
	kfree((void *)addr);
}



