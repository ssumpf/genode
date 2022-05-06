#include <lx_emul.h>

#include <linux/acpi.h>

void acpi_put_table(struct acpi_table_header *table)
{
	lx_emul_trace(__func__);
}


bool acpi_driver_match_device(struct device * dev,const struct device_driver * drv)
{
	lx_emul_trace(__func__);
	return false;
}


int acpi_platform_notify(struct device * dev,enum kobject_action action)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <acpi/acpi_bus.h>

bool is_acpi_device_node(const struct fwnode_handle * fwnode)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/kernel.h>

bool parse_option_str(const char * str,const char * option)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/cpuhotplug.h>

int __cpuhp_setup_state(enum cpuhp_state state,const char * name,bool invoke,int (* startup)(unsigned int cpu),int (* teardown)(unsigned int cpu),bool multi_instance)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/timekeeper_internal.h>

void update_vsyscall(struct timekeeper * tk)
{
	lx_emul_trace(__func__);
}


#include <linux/clocksource.h>

void clocksource_arch_init(struct clocksource * cs)
{
	lx_emul_trace(__func__);
}


#include <linux/sched/signal.h>

void ignore_signals(struct task_struct * t)
{
	lx_emul_trace(__func__);
}


#include <linux/sched/loadavg.h>

void calc_global_load(void)
{
	lx_emul_trace(__func__);
}


#include <linux/kernel_stat.h>

void account_process_tick(struct task_struct * p,int user_tick)
{
	lx_emul_trace(__func__);
}


#include <linux/rcupdate.h>

void rcu_sched_clock_irq(int user)
{
	lx_emul_trace(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_dir_ns(struct kobject * kobj,const void * ns)
{
	lx_emul_trace(__func__);
	return 0;
}


int sysfs_create_groups(struct kobject * kobj,const struct attribute_group ** groups)
{
	lx_emul_trace(__func__);
	return 0;
}


int sysfs_create_bin_file(struct kobject * kobj,const struct bin_attribute * attr)
{
	lx_emul_trace(__func__);
	return 0;
}


int sysfs_create_file_ns(struct kobject * kobj,const struct attribute * attr,const void * ns)
{
	lx_emul_trace(__func__);
	return 0;
}


int sysfs_create_link(struct kobject * kobj,struct kobject * target,const char * name)
{
	lx_emul_trace(__func__);
	return 0;
}

void sysfs_delete_link(struct kobject * kobj,struct kobject * targ,const char * name)
{
	lx_emul_trace(__func__);
}


void sysfs_remove_file_ns(struct kobject * kobj,const struct attribute * attr,const void * ns)
{
	lx_emul_trace(__func__);
}


#include <linux/kernfs.h>

void kernfs_get(struct kernfs_node * kn)
{
	lx_emul_trace(__func__);
}


void kernfs_put(struct kernfs_node * kn)
{
	lx_emul_trace(__func__);
}


#include <linux/kobject.h>

int kobject_uevent(struct kobject * kobj,enum kobject_action action)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/property.h>

int software_node_notify(struct device * dev,unsigned long action)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/random.h>

void get_random_bytes(void * buf,int nbytes)
{
	lx_emul_trace(__func__);
}


int __must_check get_random_bytes_arch(void * buf,int nbytes)
{
	lx_emul_trace(__func__);
	return 0;
}


int add_random_ready_callback(struct random_ready_callback * rdy)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/proc_fs.h>

struct proc_dir_entry { char dummy [512]; };

struct proc_dir_entry * proc_create_seq_private(const char * name,umode_t mode,struct proc_dir_entry * parent,const struct seq_operations * ops,unsigned int state_size,void * data)
{
	static struct proc_dir_entry ret;
	lx_emul_trace(__func__);

	return &ret;
}


#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
{
	lx_emul_trace(__func__);
}


#include <linux/pci.h>

struct irq_domain * pci_host_bridge_acpi_msi_domain(struct pci_bus * bus)
{
	lx_emul_trace(__func__);
	return NULL;
}


void pci_fixup_device(enum pci_fixup_pass pass,struct pci_dev * dev)
{
	lx_emul_trace(__func__);
}


extern int pci_acpi_program_hp_params(struct pci_dev * dev);
int pci_acpi_program_hp_params(struct pci_dev * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


extern void pci_allocate_vc_save_buffers(struct pci_dev * dev);
void pci_allocate_vc_save_buffers(struct pci_dev * dev)
{
	lx_emul_trace(__func__);
}


extern void pci_vpd_init(struct pci_dev * dev);
void pci_vpd_init(struct pci_dev * dev)
{
	lx_emul_trace(__func__);
}


extern int pci_dev_specific_reset(struct pci_dev * dev,int probe);
int pci_dev_specific_reset(struct pci_dev * dev,int probe)
{
	lx_emul_trace(__func__);
	return 0;
}


extern int pci_proc_attach_device(struct pci_dev * dev);
int pci_proc_attach_device(struct pci_dev * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


//POSSSIBLY important

#include <linux/fs.h>

int __register_chrdev(unsigned int major,unsigned int baseminor,unsigned int count,const char * name,const struct file_operations * fops)
{
	printk("[I] %s: name: %s\n", __func__, name);
	return 0;
}


