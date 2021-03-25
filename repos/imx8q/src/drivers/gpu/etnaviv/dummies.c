/**
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Josef Soentgen
 * \date   2021-03-16
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>


#include <linux/slab.h>

struct kmem_cache * kmalloc_caches[NR_KMALLOC_TYPES][KMALLOC_SHIFT_HIGH + 1] = {};


#include <linux/jiffies.h>

unsigned long volatile __cacheline_aligned_in_smp __jiffy_arch_data jiffies = 0;


#include <linux/kernel.h>

int oops_in_progress;


/**************************************
 ** arch/arm64/include/asm/uaccess.h **
 **************************************/

unsigned long __must_check __arch_clear_user(void __user *to, unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


/****************************
 ** arm64/include/asm/io.h **
 ****************************/

void __iomem *__ioremap(phys_addr_t phys_addr, size_t size, pgprot_t prot)
{
	lx_emul_trace_and_stop(__func__);
	return (void*)0;
}


void iounmap(volatile void __iomem *addr)
{
	lx_emul_trace_and_stop(__func__);
}


/**********************
 ** linux/rcupdate.h **
 **********************/

void __rcu_read_lock(void)
{
	// lx_emul_trace(__func__);
}


void __rcu_read_unlock(void)
{
	// lx_emul_trace(__func__);
}


/**********************************
 ** drivers/of/of_reserved_mem.c **
 **********************************/

char __reservedmem_of_table[1];


/*****************************
 ** arm64/include/asm/mmu.h **
 *****************************/

 const struct midr_range cavium_erratum_27456_cpus[1];


/************************************
 ** arm64/include/asm/cpufeature.h **
 ************************************/

#include <asm/cpucaps.h>

struct static_key_false arm64_const_caps_ready;


struct static_key_false cpu_hwcap_keys[ARM64_NCAPS];

DECLARE_BITMAP(cpu_hwcaps, ARM64_NCAPS);


/*********************
 ** linux/debugfs.h **
 *********************/

struct dentry *debugfs_create_dir(const char *name, struct dentry *parent)
{
	lx_emul_trace(__func__);
	return (void*)0;
}


struct dentry *debugfs_create_file(const char *name, umode_t mode,
                                   struct dentry *parent, void *data,
                                   const struct file_operations *fops)
{
	lx_emul_trace(__func__);
	return (void*)0;
}


void debugfs_remove(struct dentry *dentry)
{
	lx_emul_trace(__func__);
}


/********************************
 ** arm64/include/asm/memory.h **
 ********************************/

u64 kimage_vaddr;
u64 kimage_voffset;
s64 memstart_addr;
u64 vabits_actual;


/*************************
 ** include/linux/pci.h **
 *************************/

 unsigned long pci_address_to_pio(phys_addr_t addr) { return -1; }


#include <linux/spinlock_api_smp.h>

void __lockfunc _raw_spin_lock(raw_spinlock_t * lock)
{
	// lx_emul_trace(__func__);
}


unsigned long __lockfunc _raw_spin_lock_irqsave(raw_spinlock_t * lock)
{
	// lx_emul_trace(__func__);
	return 0;
}


void __lockfunc _raw_spin_unlock(raw_spinlock_t * lock)
{
	// lx_emul_trace(__func__);
}


void __lockfunc _raw_spin_unlock_irqrestore(raw_spinlock_t * lock,unsigned long flags)
{
	// lx_emul_trace(__func__);
}


#include <linux/platform_device.h>

void platform_device_put(struct platform_device * pdev)
{
	lx_emul_trace(__func__);
}


#include <linux/of.h>

struct device_node * of_node_get(struct device_node * node)
{
	lx_emul_trace(__func__);
	lx_emul_printf("%s: from: %p\n", __func__, __builtin_return_address(0));
	return node;
}


#include <linux/pm_runtime.h>

void pm_runtime_enable(struct device *dev)
{
	lx_emul_trace(__func__);
}


void pm_runtime_set_autosuspend_delay(struct device *dev, int delay)
{
	lx_emul_trace(__func__);
}


void __pm_runtime_use_autosuspend(struct device * dev,bool use)
{
	lx_emul_trace(__func__);
}


void __pm_runtime_disable(struct device * dev,bool check_resume)
{
	lx_emul_trace(__func__);
}


int __pm_runtime_resume(struct device * dev,int rpmflags)
{
	// lx_emul_trace(__func__);
	return 0;
}


int __pm_runtime_suspend(struct device * dev,int rpmflags)
{
	// lx_emul_trace(__func__);
	return 0;
}


#include <linux/platform_device.h>

void platform_driver_unregister(struct platform_driver *drv)
{
	lx_emul_trace(__func__);
}


#include <linux/thermal.h>

struct thermal_cooling_device *
thermal_of_cooling_device_register(struct device_node *np,
                                   const char *type, void *devdata,
                                   const struct thermal_cooling_device_ops *ops)
{
	lx_emul_trace(__func__);
	return NULL;
}


#include <linux/sched.h>

int wake_up_process(struct task_struct *p)
{
	lx_emul_trace(__func__);
	return 0;
}


int sched_setscheduler(struct task_struct * p,int policy,const struct sched_param * param)
{
	lx_emul_printf("%s:%d\n", __func__, __LINE__);

	return 0;
}

#include <asm-generic/preempt.h>

asmlinkage __visible void __sched notrace preempt_schedule(void)
{
	lx_emul_trace(__func__);
}



#include <linux/cpuhotplug.h>

int __cpuhp_setup_state(enum cpuhp_state state, char const *name,
                        bool invoke, int (*startup)(unsigned int cpu),
                        int (*teardown)(unsigned int cpu), bool multi_instance)
{
	lx_emul_trace(__func__);
	return 0;
}


#include <asm-generic/percpu.h>

unsigned long __per_cpu_offset[NR_CPUS] = {};


#include <linux/rwlock_api_smp.h>

void __lockfunc _raw_read_lock(rwlock_t * lock)
{
	// lx_emul_trace(__func__);
}


void __lockfunc _raw_read_unlock(rwlock_t * lock)
{
	// lx_emul_trace(__func__);
}


void __lockfunc _raw_write_lock(rwlock_t * lock)
{
	// lx_emul_trace(__func__);
}


void __lockfunc _raw_write_unlock(rwlock_t * lock)
{
	// lx_emul_trace(__func__);
}


DEFINE_MUTEX(drm_global_mutex);


// extern int drm_authmagic(struct drm_device * dev,void * data,struct drm_file * file_priv);
struct drm_device;
struct drm_file;
int drm_authmagic(struct drm_device * dev,void * data,struct drm_file * file_priv)
{
	lx_emul_trace_and_stop(__func__);
}

#include <drm/drm_drv.h>

bool drm_dev_enter(struct drm_device * dev,int * idx)
{
	// lx_emul_trace(__func__);
	return true;
}


void drm_dev_exit(int idx)
{
	// lx_emul_trace(__func__);
}


void drm_dev_get(struct drm_device * dev)
{
	// lx_emul_trace(__func__);
}


void drm_dev_put(struct drm_device * dev)
{
	// lx_emul_trace(__func__);
}



#include <linux/ww_mutex.h>

int __sched ww_mutex_lock_interruptible(struct ww_mutex * lock,struct ww_acquire_ctx * ctx)
{
	// lx_emul_trace(__func__);
	return 0;
}


void __sched ww_mutex_unlock(struct ww_mutex * lock)
{
	// lx_emul_trace(__func__);
}


#include <linux/devcoredump.h>

void dev_coredumpv(struct device * dev,void * data,size_t datalen,gfp_t gfp)
{
	lx_emul_trace(__func__);
}
