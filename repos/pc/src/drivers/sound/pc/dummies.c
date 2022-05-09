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
//XXX:might be needed
bool acpi_dev_present(const char * hid,const char * uid,s64 hrv)
{
	lx_emul_trace(__func__);
	return false;
}


#include <acpi/acpi_bus.h>

bool is_acpi_device_node(const struct fwnode_handle * fwnode)
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


extern int pci_acpi_program_hp_params(struct pci_dev * dev);
int pci_acpi_program_hp_params(struct pci_dev * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sched.h>

void sched_set_fifo(struct task_struct * p)
{
	lx_emul_trace(__func__);
}


#include <linux/task_work.h>

int task_work_add(struct task_struct * task,struct callback_head * work,enum task_work_notify_mode notify)
{
	lx_emul_trace(__func__);
	return -1;
}


extern int hda_widget_sysfs_reinit(struct hdac_device * codec,hda_nid_t start_nid,int num_nodes);
int hda_widget_sysfs_reinit(struct hdac_device * codec,hda_nid_t start_nid,int num_nodes)
{
	lx_emul_trace(__func__);
	return 0;
}


extern int hda_widget_sysfs_init(struct hdac_device * codec);
int hda_widget_sysfs_init(struct hdac_device * codec)
{
	lx_emul_trace(__func__);
	return 0;
}


extern void hda_widget_sysfs_exit(struct hdac_device * codec);
void hda_widget_sysfs_exit(struct hdac_device * codec)
{
	lx_emul_trace(__func__);
}


extern void snd_hda_sysfs_init(struct hda_codec * codec);
void snd_hda_sysfs_init(struct hda_codec * codec)
{
	lx_emul_trace(__func__);
}


extern int snd_hda_get_int_hint(struct hda_codec * codec,const char * key,int * valp);
int snd_hda_get_int_hint(struct hda_codec * codec,const char * key,int * valp)
{
	lx_emul_trace(__func__);
	return -ENOENT;
}


extern int snd_hda_get_bool_hint(struct hda_codec * codec,const char * key);
int snd_hda_get_bool_hint(struct hda_codec * codec,const char * key)
{
	lx_emul_trace(__func__);
	return -ENOENT;
}


