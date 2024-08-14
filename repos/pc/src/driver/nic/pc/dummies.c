/*
 * \brief  Dummy definitions of Linux Kernel functions - handled manually
 * \author Christian Helmuth
 * \date   2023-05-22
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

#include <asm/preempt.h>
#include <asm/smp.h>

struct smp_ops smp_ops = { };
EXPORT_SYMBOL_GPL(smp_ops);

#include <linux/pgtable.h>

pteval_t __default_kernel_pte_mask __read_mostly = ~0;

#include <linux/sysfs.h>

const struct attribute_group dev_attr_physical_location_group = {};

#include <linux/sysfs.h>

int sysfs_add_file_to_group(struct kobject * kobj,const struct attribute * attr,const char * group)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/sysfs.h>

int sysfs_create_link_nowarn(struct kobject * kobj,struct kobject * target,const char * name)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/proc_ns.h>

int proc_alloc_inum(unsigned int * inum)
{
	*inum = 1; /* according to linux/proc_ns.h without CONFIG_PROC_FS */
	return 0;
}

#include <linux/sysctl.h>

void __init __register_sysctl_init(const char * path,struct ctl_table * table,const char * table_name,size_t table_size)
{
	lx_emul_trace(__func__);
}

#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
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

#include <linux/acpi.h>

void acpi_device_notify(struct device * dev)
{
	lx_emul_trace(__func__);
}

extern bool dev_add_physical_location(struct device * dev);
bool dev_add_physical_location(struct device * dev)
{
	lx_emul_trace(__func__);
	return false;
}

#include <linux/kobject.h>

int kobject_uevent(struct kobject * kobj,enum kobject_action action)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/filter.h>

void bpf_prog_change_xdp(struct bpf_prog *prev_prog, struct bpf_prog *prog)
{
	lx_emul_trace(__func__);
}

#include <linux/jump_label.h>

DEFINE_STATIC_KEY_FALSE(memalloc_socks_key);
DEFINE_STATIC_KEY_FALSE(bpf_stats_enabled_key);
DEFINE_STATIC_KEY_FALSE(bpf_master_redirect_enabled_key);
EXPORT_SYMBOL_GPL(bpf_master_redirect_enabled_key);

#include <linux/percpu-defs.h>

DEFINE_PER_CPU_READ_MOSTLY(cpumask_var_t, cpu_sibling_map);
EXPORT_PER_CPU_SYMBOL(cpu_sibling_map);

#include <linux/netdevice.h>

int __init dev_proc_init(void)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/iommu.h>

int iommu_device_use_default_domain(struct device * dev)
{
	lx_emul_trace(__func__);
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

#include <linux/stringhash.h>

unsigned int full_name_hash(const void * salt,const char * name,unsigned int len)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <net/gen_stats.h>

void gnet_stats_basic_sync_init(struct gnet_stats_basic_sync * b)
{
	lx_emul_trace(__func__);
}

#include <linux/pm_qos.h>

void cpu_latency_qos_add_request(struct pm_qos_request * req,s32 value)
{
	lx_emul_trace(__func__);
}

#include <linux/pm_qos.h>

void cpu_latency_qos_update_request(struct pm_qos_request *req, s32 new_value)
{
	lx_emul_trace(__func__);
}

#include <linux/netdevice.h>

void netdev_rss_key_fill(void * buffer, size_t len)
{
	lx_emul_trace(__func__);
}

#include <linux/pci.h>

int pci_write_config_word(const struct pci_dev *dev, int where, u16 val)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/pci.h>

int pci_enable_device_mem(struct pci_dev *dev)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/pci.h>

int pci_request_selected_regions(struct pci_dev *dev, int, const char *res_name)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/pci.h>

int pci_request_selected_regions_exclusive(struct pci_dev *dev, int, const char *res_name)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/pci.h>

int pci_enable_msi(struct pci_dev *dev)
{
	lx_emul_trace(__func__);
	return -ENOSYS;
}

#include <linux/pci.h>

void pci_restore_state(struct pci_dev *dev)
{
	lx_emul_trace(__func__);
}

#include <linux/pci.h>

int pci_save_state(struct pci_dev *dev)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/pci.h>

void pci_disable_device(struct pci_dev *dev)
{
	lx_emul_trace(__func__);
}

#include <linux/pci.h>

void pci_disable_msi(struct pci_dev *dev)
{
	lx_emul_trace(__func__);
}

#include <linux/pci.h>

int pci_enable_msix_range(struct pci_dev *dev, struct msix_entry *entries, int minvec, int maxvec)
{
	lx_emul_trace(__func__);
	return -ENOSYS;
}

#include <linux/pci.h>

void pci_disable_msix(struct pci_dev *dev)
{
	lx_emul_trace(__func__);
}

#include <linux/pci.h>

int pci_disable_link_state_locked(struct pci_dev *dev, int state)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/pci.h>

int pci_enable_wake(struct pci_dev *pci_dev, pci_power_t state, bool enable)
{
	lx_emul_trace(__func__);
	return -EINVAL;
}

#include <linux/pci.h>

void pci_clear_master(struct pci_dev *dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pci.h>

int pcim_set_mwi(struct pci_dev * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/iommu.h>

void iommu_device_unuse_default_domain(struct device * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/pci.h>

int pcim_iomap_regions(struct pci_dev * pdev,int mask,const char * name)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/firmware.h>

int request_firmware(const struct firmware ** firmware_p,const char * name,struct device * device)
{
	lx_emul_trace(__func__);
	return -1;
}


#include <linux/net.h>

int net_ratelimit(void)
{
	lx_emul_trace(__func__);
	/* suppress */
	return 0;
}

#include <net/dst.h>

void dst_release(struct dst_entry * dst)
{
	lx_emul_trace(__func__);
}

#include <linux/property.h>

int software_node_notify(struct device * dev,unsigned long action)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/gpio/consumer.h>

struct gpio_desc * devm_gpiod_get_optional(struct device * dev, const char * con_id, enum gpiod_flags flags)
{
	lx_emul_trace(__func__);
	return NULL;
}

#include <linux/gpio/consumer.h>

struct gpio_desc * __must_check gpiod_get_optional(struct device * dev,const char * con_id,enum gpiod_flags flags)
{
	lx_emul_trace(__func__);
	return NULL;
}

#include <linux/clk.h>

struct clk *devm_clk_get_optional_enabled(struct device *dev, const char *id)
{
	return NULL;
}

#include <linux/pinctrl/devinfo.h>

int pinctrl_bind_pins(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/pinctrl/devinfo.h>

int pinctrl_init_done(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}

