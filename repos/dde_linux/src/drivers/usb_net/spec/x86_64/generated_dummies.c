/*
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Automatically generated file - do no edit
 * \date   2023-07-05
 */

#include <lx_emul.h>


#include <linux/gfp.h>

struct page * __alloc_pages(gfp_t gfp,unsigned int order,int preferred_nid,nodemask_t * nodemask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cpumask.h>

struct cpumask __cpu_active_mask;


#include <linux/phy.h>

int __devm_mdiobus_register(struct device * dev,struct mii_bus * bus,struct module * owner)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

void __folio_put(struct folio * folio)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irqdomain.h>

struct irq_domain * __irq_domain_add(struct fwnode_handle * fwnode,unsigned int size,irq_hw_number_t hwirq_max,int direct_max,const struct irq_domain_ops * ops,void * host_data)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irqdomain.h>

struct fwnode_handle * __irq_domain_alloc_fwnode(unsigned int type,int id,const char * name,phys_addr_t * pa)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irqdomain.h>

struct irq_desc * __irq_resolve_mapping(struct irq_domain * domain,irq_hw_number_t hwirq,unsigned int * irq)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

int __mdiobus_register(struct mii_bus * bus,struct module * owner)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

void __netdev_watchdog_up(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int __printk_ratelimit(const char * func)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

void __printk_safe_enter(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

void __printk_safe_exit(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/task.h>

void __put_task_struct(struct task_struct * tsk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/pkt_sched.h>

void __qdisc_run(struct Qdisc * q)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/skbuff.h>

void __skb_get_hash(struct sk_buff * skb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmalloc.h>

void * __vmalloc_node_range(unsigned long size,unsigned long align,unsigned long start,unsigned long end,gfp_t gfp_mask,pgprot_t prot,unsigned long vm_flags,int node,const void * caller)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/xdp.h>

int __xdp_rxq_info_reg(struct xdp_rxq_info * xdp_rxq,struct net_device * dev,u32 queue_index,unsigned int napi_id,u32 frag_size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uaccess.h>

unsigned long _copy_to_user(void __user * to,const void * from,unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int _printk_deferred(const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


extern void ack_bad_irq(unsigned int irq);
void ack_bad_irq(unsigned int irq)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/random.h>

void add_device_randomness(const void * buf,size_t len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

int add_uevent_var(struct kobj_uevent_env * env,const char * format,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/async.h>

async_cookie_t async_schedule_node(async_func_t func,void * data,int node)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/async.h>

void async_synchronize_full(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

void bpf_warn_invalid_xdp_action(struct net_device * dev,struct bpf_prog * prog,u32 act)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/bitrev.h>

u8 const byte_rev_table[256] = {};


#include <linux/usb/cdc.h>

int cdc_parse_cdc_header(struct usb_cdc_parsed_header * hdr,struct usb_interface * intf,u8 * buffer,int buflen)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/context_tracking_irq.h>

noinstr void ct_irq_enter(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/context_tracking_irq.h>

noinstr void ct_irq_exit(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern void dev_addr_flush(struct net_device * dev);
void dev_addr_flush(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int dev_addr_init(struct net_device * dev);
int dev_addr_init(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

void dev_addr_mod(struct net_device * dev,unsigned int offset,const void * addr,size_t len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/sch_generic.h>

void dev_deactivate_many(struct list_head * head)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/sch_generic.h>

void dev_init_scheduler(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

void dev_mc_flush(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

void dev_mc_init(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/sch_generic.h>

void dev_shutdown(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

void dev_uc_flush(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

void dev_uc_init(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

struct mii_bus * devm_mdiobus_alloc_size(struct device * dev,int sizeof_priv)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/dst.h>

void dst_release(struct dst_entry * dst)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq.h>

struct irq_chip dummy_irq_chip;


#include <linux/printk.h>

asmlinkage __visible void dump_stack(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ethtool.h>

int ethtool_check_ops(const struct ethtool_ops * ops)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ethtool.h>

u32 ethtool_op_get_link(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ethtool.h>

int ethtool_op_get_ts_info(struct net_device * dev,struct ethtool_ts_info * info)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/capability.h>

bool file_ns_capable(const struct file * file,struct user_namespace * ns,int cap)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcuwait.h>

void finish_rcuwait(struct rcuwait * w)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gfp.h>

void free_pages(unsigned long addr,unsigned int order)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/stringhash.h>

unsigned int full_name_hash(const void * salt,const char * name,unsigned int len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irqdesc.h>

int generic_handle_domain_irq(struct irq_domain * domain,unsigned int hwirq)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mii.h>

int generic_mii_ioctl(struct mii_if_info * mii_if,struct mii_ioctl_data * mii_data,int cmd,unsigned int * duplex_chg_out)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

int genphy_read_status(struct phy_device * phydev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

int genphy_resume(struct phy_device * phydev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gfp.h>

unsigned long get_zeroed_page(gfp_t gfp_mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gfp.h>

bool gfp_pfmemalloc_allowed(gfp_t gfp_mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

struct packet_offload * gro_find_complete_by_type(__be16 type)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

struct packet_offload * gro_find_receive_by_type(__be16 type)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uuid.h>

const u8 guid_index[16] = {};


#include <linux/irq.h>

void handle_simple_irq(struct irq_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/netfilter/nf_conntrack.h>

struct net init_net;


#include <linux/utsname.h>

struct user_namespace init_user_ns;


#include <linux/init.h>

bool initcall_debug;


#include <linux/sched.h>

void __sched io_schedule(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

void io_schedule_finish(int token)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

int io_schedule_prepare(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

long __sched io_schedule_timeout(long timeout)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/swiotlb.h>

struct io_tlb_mem io_tlb_default_mem;


#include <linux/interrupt.h>

int irq_can_set_affinity(unsigned int irq)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irqdomain.h>

unsigned int irq_create_mapping_affinity(struct irq_domain * domain,irq_hw_number_t hwirq,const struct irq_affinity_desc * affinity)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irqdomain.h>

void irq_dispose_mapping(unsigned int virq)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irqdomain.h>

void irq_domain_free_fwnode(struct fwnode_handle * fwnode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irqdomain.h>

void irq_domain_remove(struct irq_domain * domain)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irqdomain.h>

const struct irq_domain_ops irq_domain_simple_ops;


#include <linux/interrupt.h>

int irq_set_affinity(unsigned int irq,const struct cpumask * cpumask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq.h>

void irq_set_chip_and_handler_name(unsigned int irq,const struct irq_chip * chip,irq_flow_handler_t handle,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq_work.h>

void irq_work_tick(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/slab.h>

int kmem_cache_alloc_bulk(struct kmem_cache * s,gfp_t flags,size_t nr,void ** p)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/slab.h>

void * kmem_cache_alloc_lru(struct kmem_cache * cachep,struct list_lru * lru,gfp_t flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/slab.h>

void kmem_cache_free_bulk(struct kmem_cache * s,size_t nr,void ** p)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

int kobject_synth_uevent(struct kobject * kobj,const char * buf,size_t count)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

int kobject_uevent_env(struct kobject * kobj,enum kobject_action action,char * envp_ext[])
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcutree.h>

void kvfree_call_rcu(struct rcu_head * head,rcu_callback_t func)
{
	lx_emul_trace_and_stop(__func__);
}


extern void linkwatch_init_dev(struct net_device * dev);
void linkwatch_init_dev(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

struct pernet_operations __net_initdata loopback_net_ops;


#include <linux/phy.h>

struct mii_bus * mdiobus_alloc_size(size_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

void mdiobus_free(struct mii_bus * bus)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mdio.h>

struct phy_device * mdiobus_get_phy(struct mii_bus * bus,int addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

void mdiobus_unregister(struct mii_bus * bus)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/preempt.h>

void migrate_disable(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/preempt.h>

void migrate_enable(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mii.h>

unsigned int mii_check_media(struct mii_if_info * mii,unsigned int ok_to_print,unsigned int init_media)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mii.h>

void mii_ethtool_get_link_ksettings(struct mii_if_info * mii,struct ethtool_link_ksettings * cmd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mii.h>

void mii_ethtool_gset(struct mii_if_info * mii,struct ethtool_cmd * ecmd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mii.h>

int mii_ethtool_set_link_ksettings(struct mii_if_info * mii,const struct ethtool_link_ksettings * cmd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mii.h>

int mii_link_ok(struct mii_if_info * mii)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mii.h>

int mii_nway_restart(struct mii_if_info * mii)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

void napi_gro_flush(struct napi_struct * napi,bool flush_old)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/net.h>

int net_ratelimit(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/selftests.h>

void net_selftest(struct net_device * ndev,struct ethtool_test * etest,u64 * buf)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/selftests.h>

int net_selftest_get_count(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/selftests.h>

void net_selftest_get_strings(u8 * data)
{
	lx_emul_trace_and_stop(__func__);
}


extern int netdev_register_kobject(struct net_device * ndev);
int netdev_register_kobject(struct net_device * ndev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void netdev_unregister_kobject(struct net_device * ndev);
void netdev_unregister_kobject(struct net_device * ndev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

void netif_carrier_off(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/netdevice.h>

void netif_carrier_on(struct net_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gfp.h>

void * page_frag_alloc_align(struct page_frag_cache * nc,unsigned int fragsz,gfp_t gfp_mask,unsigned int align_mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gfp.h>

void page_frag_free(void * addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/moduleparam.h>

int param_set_copystring(const char * val,const struct kernel_param * kp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

bool parse_option_str(const char * str,const char * option)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

void phy_attached_info(struct phy_device * phydev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

struct phy_device * phy_connect(struct net_device * dev,const char * bus_id,void (* handler)(struct net_device *),phy_interface_t interface)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

int phy_connect_direct(struct net_device * dev,struct phy_device * phydev,void (* handler)(struct net_device *),phy_interface_t interface)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

void phy_disconnect(struct phy_device * phydev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

int phy_do_ioctl_running(struct net_device * dev,struct ifreq * ifr,int cmd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

int phy_ethtool_get_link_ksettings(struct net_device * ndev,struct ethtool_link_ksettings * cmd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

int phy_ethtool_nway_reset(struct net_device * ndev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

int phy_ethtool_set_link_ksettings(struct net_device * ndev,const struct ethtool_link_ksettings * cmd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

struct phy_device * phy_find_first(struct mii_bus * bus)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

void phy_get_pause(struct phy_device * phydev,bool * tx_pause,bool * rx_pause)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

int phy_init_hw(struct phy_device * phydev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

int phy_mii_ioctl(struct phy_device * phydev,struct ifreq * ifr,int cmd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

void phy_print_status(struct phy_device * phydev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

void phy_start(struct phy_device * phydev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

void phy_stop(struct phy_device * phydev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phy.h>

int phy_suspend(struct phy_device * phydev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phylink.h>

int phylink_connect_phy(struct phylink * pl,struct phy_device * phy)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phylink.h>

struct phylink * phylink_create(struct phylink_config * config,struct fwnode_handle * fwnode,phy_interface_t iface,const struct phylink_mac_ops * mac_ops)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phylink.h>

void phylink_destroy(struct phylink * pl)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phylink.h>

void phylink_disconnect_phy(struct phylink * pl)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phylink.h>

void phylink_ethtool_get_pauseparam(struct phylink * pl,struct ethtool_pauseparam * pause)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phylink.h>

int phylink_ethtool_set_pauseparam(struct phylink * pl,struct ethtool_pauseparam * pause)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phylink.h>

void phylink_generic_validate(struct phylink_config * config,unsigned long * supported,struct phylink_link_state * state)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phylink.h>

void phylink_resume(struct phylink * pl)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phylink.h>

void phylink_start(struct phylink * pl)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phylink.h>

void phylink_stop(struct phylink * pl)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/phylink.h>

void phylink_suspend(struct phylink * pl,bool mac_wol)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/refcount.h>

void refcount_warn_saturate(refcount_t * r,enum refcount_saturation_type t)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

void rtmsg_ifinfo(int type,struct net_device * dev,unsigned int change,gfp_t flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

struct sk_buff * rtmsg_ifinfo_build_skb(int type,struct net_device * dev,unsigned int change,u32 event,gfp_t flags,int * new_nsid,int new_ifindex)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

void rtmsg_ifinfo_send(struct sk_buff * skb,struct net_device * dev,gfp_t flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

int rtnl_is_locked(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

void rtnl_lock(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

int rtnl_lock_killable(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rtnetlink.h>

void rtnl_unlock(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/scatterlist.h>

void sg_init_table(struct scatterlist * sgl,unsigned int nents)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/sock.h>

void sk_error_report(struct sock * sk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/smp.h>

void smp_call_function_many(const struct cpumask * mask,smp_call_func_t func,void * info,bool wait)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/smp.h>

int smp_call_function_single(int cpu,smp_call_func_t func,void * info,int wait)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/sock.h>

void sock_edemux(struct sk_buff * skb)
{
	lx_emul_trace_and_stop(__func__);
}


extern void software_node_notify(struct device * dev);
void software_node_notify(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void software_node_notify_remove(struct device * dev);
void software_node_notify_remove(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/jump_label.h>

bool static_key_initialized;


#include <linux/rcupdate.h>

void synchronize_rcu(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/sock.h>

int sysctl_tstamp_allow_data;


#include <linux/tcp.h>

struct sk_buff * tcp_get_timestamping_opt_stats(const struct sock * sk,const struct sk_buff * orig_skb,const struct sk_buff * ack_skb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/timerqueue.h>

bool timerqueue_add(struct timerqueue_head * head,struct timerqueue_node * node)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/timerqueue.h>

bool timerqueue_del(struct timerqueue_head * head,struct timerqueue_node * node)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/timerqueue.h>

struct timerqueue_node * timerqueue_iterate_next(struct timerqueue_node * node)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_clear_halt(struct usb_device * dev,int pipe)
{
	lx_emul_trace_and_stop(__func__);
}


extern int usb_create_ep_devs(struct device * parent,struct usb_host_endpoint * endpoint,struct usb_device * udev);
int usb_create_ep_devs(struct device * parent,struct usb_host_endpoint * endpoint,struct usb_device * udev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int usb_create_sysfs_dev_files(struct usb_device * udev);
int usb_create_sysfs_dev_files(struct usb_device * udev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_create_sysfs_intf_files(struct usb_interface * intf);
void usb_create_sysfs_intf_files(struct usb_interface * intf)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_devio_cleanup(void);
void usb_devio_cleanup(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_disable_device(struct usb_device * dev,int skip_ep0);
void usb_disable_device(struct usb_device * dev,int skip_ep0)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_disable_endpoint(struct usb_device * dev,unsigned int epaddr,bool reset_hardware);
void usb_disable_endpoint(struct usb_device * dev,unsigned int epaddr,bool reset_hardware)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_disable_interface(struct usb_device * dev,struct usb_interface * intf,bool reset_hardware);
void usb_disable_interface(struct usb_device * dev,struct usb_interface * intf,bool reset_hardware)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_enable_endpoint(struct usb_device * dev,struct usb_host_endpoint * ep,bool reset_ep);
void usb_enable_endpoint(struct usb_device * dev,struct usb_host_endpoint * ep,bool reset_ep)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_enable_interface(struct usb_device * dev,struct usb_interface * intf,bool reset_eps);
void usb_enable_interface(struct usb_device * dev,struct usb_interface * intf,bool reset_eps)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_free_streams(struct usb_interface * interface,struct usb_host_endpoint ** eps,unsigned int num_eps,gfp_t mem_flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_get_descriptor(struct usb_device * dev,unsigned char type,unsigned char index,void * buf,int size)
{
	lx_emul_trace_and_stop(__func__);
}


extern int usb_get_device_descriptor(struct usb_device * dev,unsigned int size);
int usb_get_device_descriptor(struct usb_device * dev,unsigned int size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

struct urb * usb_get_from_anchor(struct usb_anchor * anchor)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_get_status(struct usb_device * dev,int recip,int type,int target,void * data)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

struct urb * usb_get_urb(struct urb * urb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb/hcd.h>

int usb_hcd_alloc_bandwidth(struct usb_device * udev,struct usb_host_config * new_config,struct usb_host_interface * cur_alt,struct usb_host_interface * new_alt)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb/hcd.h>

int usb_hcd_find_raw_port_number(struct usb_hcd * hcd,int port1)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb/hcd.h>

void usb_hcd_synchronize_unlinks(struct usb_device * udev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int usb_hub_create_port_device(struct usb_hub * hub,int port1);
int usb_hub_create_port_device(struct usb_hub * hub,int port1)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_hub_remove_port_device(struct usb_hub * hub,int port1);
void usb_hub_remove_port_device(struct usb_hub * hub,int port1)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_interrupt_msg(struct usb_device * usb_dev,unsigned int pipe,void * data,int len,int * actual_length,int timeout)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

extern void usb_major_cleanup(void);
void usb_major_cleanup(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_notify_add_device(struct usb_device * udev);
void usb_notify_add_device(struct usb_device * udev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_notify_remove_device(struct usb_device * udev);
void usb_notify_remove_device(struct usb_device * udev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_remove_ep_devs(struct usb_host_endpoint * endpoint);
void usb_remove_ep_devs(struct usb_host_endpoint * endpoint)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_remove_sysfs_dev_files(struct usb_device * udev);
void usb_remove_sysfs_dev_files(struct usb_device * udev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_remove_sysfs_intf_files(struct usb_interface * intf);
void usb_remove_sysfs_intf_files(struct usb_interface * intf)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_set_configuration(struct usb_device * dev,int configuration)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_set_interface(struct usb_device * dev,int interface,int alternate)
{
	lx_emul_trace_and_stop(__func__);
}


extern int usb_set_isoch_delay(struct usb_device * dev);
int usb_set_isoch_delay(struct usb_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb/ch9.h>

const char * usb_speed_string(enum usb_device_speed speed)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_unlink_urb(struct urb * urb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uuid.h>

const u8 uuid_index[16] = {};


#include <linux/sched/wake_q.h>

void wake_q_add_safe(struct wake_q_head * head,struct task_struct * task)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

int xdp_do_generic_redirect(struct net_device * dev,struct sk_buff * skb,struct xdp_buff * xdp,struct bpf_prog * xdp_prog)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

u32 xdp_master_redirect(struct xdp_buff * xdp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <net/xdp.h>

void xdp_rxq_info_unreg(struct xdp_rxq_info * xdp_rxq)
{
	lx_emul_trace_and_stop(__func__);
}

