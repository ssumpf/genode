/*
 * \brief  Dummies - used but of no use
 * \author Sebastian Sumpf
 * \date   2022-05-31
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

#include <linux/acpi.h>

void acpi_put_table(struct acpi_table_header *table)
{
	lx_emul_trace(__func__);
}


#include <acpi/acpi_bus.h>
//XXX:might be needed
bool acpi_dev_present(const char * hid,const char * uid,s64 hrv)
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

struct input_dev_poller;
extern void input_dev_poller_finalize(struct input_dev_poller * poller);
void input_dev_poller_finalize(struct input_dev_poller * poller)
{
	lx_emul_trace_and_stop(__func__);
}


extern void input_dev_poller_start(struct input_dev_poller * poller);
void input_dev_poller_start(struct input_dev_poller * poller)
{
	lx_emul_trace_and_stop(__func__);
}


extern void input_dev_poller_stop(struct input_dev_poller * poller);
void input_dev_poller_stop(struct input_dev_poller * poller)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/proc_fs.h>

struct proc_dir_entry { unsigned dummy; };

struct proc_dir_entry * proc_create(const char * name,umode_t mode,struct proc_dir_entry * parent,const struct proc_ops * proc_ops)
{
	static struct proc_dir_entry entry;
	lx_emul_trace(__func__);
	return &entry;
}


struct proc_dir_entry * proc_mkdir(const char * name,struct proc_dir_entry * parent)
{
	static struct proc_dir_entry entry;
	lx_emul_trace(__func__);
	return &entry;
}


#include <linux/fs.h>

int alloc_chrdev_region(dev_t * dev,unsigned baseminor,unsigned count,const char * name)
{
	lx_emul_trace(__func__);
	return 0;
}


int nonseekable_open(struct inode * inode,struct file * filp)
{
	lx_emul_trace(__func__);
	return 0;
}


int stream_open(struct inode * inode,struct file * filp)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <linux/async.h>

void async_synchronize_full_domain(struct async_domain * domain)
{
	lx_emul_trace(__func__);
}


#include <linux/leds.h>

void ledtrig_audio_set(enum led_audio type,enum led_brightness state)
{
	lx_emul_trace(__func__);
}


bool dma_can_mmap(struct device * dev)
{
	lx_emul_trace(__func__);
	return false;
}


#include <linux/pm_qos.h>

bool cpu_latency_qos_request_active(struct pm_qos_request * req)
{
	lx_emul_trace(__func__);
	return false;
}


void cpu_latency_qos_add_request(struct pm_qos_request * req,s32 value)
{
	lx_emul_trace(__func__);
}


#include <linux/pid.h>

void put_pid(struct pid * pid)
{
	lx_emul_trace(__func__);
}


#include <linux/pinctrl/devinfo.h>

int pinctrl_bind_pins(struct device * dev)
{
	lx_emul_trace(__func__);
	return 0;
}


int pinctrl_init_done(struct device * dev)
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


#include <asm/smp.h>

struct smp_ops smp_ops = { };

