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

