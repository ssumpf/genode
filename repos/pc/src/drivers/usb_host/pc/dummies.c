/*
 * \brief  Dummy definitions of Linux Kernel functions - handled manually
 * \author Josef Soentgen
 * \date   2022-01-10
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

const struct attribute_group pci_dev_acpi_attr_group;


#include <linux/random.h>

int __must_check get_random_bytes_arch(void * buf,int nbytes)
{
	lx_emul_trace(__func__);
	printk("%s: leaving buffer unmodified!\n", __func__);
	return 0;
}


#include <linux/random.h>

void get_random_bytes(void * buf,int nbytes)
{
	lx_emul_trace(__func__);
	printk("%s: leaving buffer unmodified!\n", __func__);
}


#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
{
	lx_emul_trace(__func__);
}


#include <linux/mm.h>

bool is_vmalloc_addr(const void * x)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/kobject.h>

int acpi_platform_notify(struct device *dev, enum kobject_action action)
{
	lx_emul_trace(__func__);
	return 0;
}


int pci_acpi_program_hp_params(struct pci_dev *dev)
{
	lx_emul_trace(__func__);
	return 0;
}

#include <linux/property.h>

struct device_driver;


bool acpi_driver_match_device(struct device *dev, const struct device_driver *drv)
{
	lx_emul_trace(__func__);
	return false;
}


bool is_acpi_device_node(const struct fwnode_handle *fwnode)
{
	lx_emul_trace(__func__);
	return false;
}


struct acpi_device;

enum dev_dma_attr acpi_get_dma_attr(struct acpi_device *adev)
{
	lx_emul_trace_and_stop(__func__);
}


int acpi_device_uevent_modalias(struct device *dev, struct kobj_uevent_env *event)
{
	lx_emul_trace_and_stop(__func__);
}


int acpi_dma_configure_id(struct device *dev, enum dev_dma_attr attr, const u32 *input_id)
{
	lx_emul_trace_and_stop(__func__);
}


int acpi_device_modalias(struct device *device, char * x, int y)
{
	lx_emul_trace_and_stop(__func__);
}


bool pciehp_is_native(struct pci_dev *bridge)
{
	lx_emul_trace_and_stop(__func__);
}


struct irq_domain *pci_host_bridge_acpi_msi_domain(struct pci_bus *bus)
{
	lx_emul_trace(__func__);
	return NULL;
}


typedef void * acpi_handle;

union acpi_object *acpi_evaluate_dsm(acpi_handle handle, const guid_t *guid,
                                     u64 rev, u64 func, union acpi_object *argv4)
{
	lx_emul_trace(__func__);
	return NULL;
}


int usb_acpi_register(void)
{
	lx_emul_trace(__func__);
	return 0;
};


void usb_acpi_unregister(void)
{
	lx_emul_trace(__func__);
};


struct usb_device;
bool usb_acpi_power_manageable(struct usb_device *hdev, int index)
{
	lx_emul_trace(__func__);
	return false;
}


int usb_acpi_set_power_state(struct usb_device *hdev, int index, bool enable)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/printk.h>

int __printk_ratelimit(const char * func)
{
	lx_emul_trace(__func__);
	/* suppress */
	return 0;
}
