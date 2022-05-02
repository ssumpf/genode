/*
 * \brief  Dummy definitions of Linux Kernel functions - handled manually
 * \author Christian Helmuth
 * \date   2022-05-02
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

#include <linux/pci.h>

const struct attribute_group pci_dev_acpi_attr_group;


#include <linux/seq_file.h>

void seq_printf(struct seq_file * m,const char * f,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int __printk_ratelimit(const char * func)
{
	lx_emul_trace(__func__);
	/* suppress */
	return 0;
}


#include <linux/kobject.h>

int kobject_uevent(struct kobject * kobj,enum kobject_action action)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
{
	lx_emul_trace(__func__);
}


#include <linux/proc_fs.h>

struct proc_dir_entry * proc_mkdir(const char * name,struct proc_dir_entry * parent)
{
	static struct { void *p; } dummy;
	lx_emul_trace(__func__);
	return (struct proc_dir_entry *)&dummy;
}


#include <linux/proc_fs.h>

struct proc_dir_entry * proc_create(const char * name,umode_t mode,struct proc_dir_entry * parent,const struct proc_ops * proc_ops)
{
	static struct { void *p; } dummy;
	lx_emul_trace(__func__);
	return (struct proc_dir_entry *)&dummy;
}


#include <linux/pci.h>

struct irq_domain *pci_host_bridge_acpi_msi_domain(struct pci_bus *bus)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/fs.h>

int alloc_chrdev_region(dev_t * dev, unsigned baseminor, unsigned count, const char * name)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/acpi.h>

int acpi_check_resource_conflict(const struct resource * res)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <acpi/acpi_bus.h>

int acpi_device_fix_up_power(struct acpi_device * device)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/sched/rt.h>

void rt_mutex_setprio(struct task_struct *p, struct task_struct *pi_task)
{
	lx_emul_trace(__func__);
}


#include <linux/input.h>

void input_ff_destroy(struct input_dev * dev)
{
	lx_emul_trace(__func__);
}


#include <linux/input.h>

int input_ff_event(struct input_dev * dev,unsigned int type,unsigned int code,int value)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/input/mt.h>

void input_mt_destroy_slots(struct input_dev * dev)
{
	lx_emul_trace(__func__);
}


