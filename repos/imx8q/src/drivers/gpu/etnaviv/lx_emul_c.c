/*
 * \brief  Linux emulation C helper functions
 * \author Josef Soentgen
 * \date   2021-03-22
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>
#include <linux/interrupt.h>
#include <lx_emul_cc.h>
#include <lx_emul_c.h>

#ifdef LX_DEBUG
#define LX_TRACE_PRINT(...) do { lx_emul_printf(__VA_ARGS__); } while (0)
#else
#define LX_TRACE_PRINT(...)
#endif


#include <linux/printk.h>

asmlinkage __visible int printk(const char * fmt,...)
{
	va_list args;
	va_start(args, fmt);
	lx_emul_vprintf(fmt, args);
	va_end(args);
	return 0;
}


#include <linux/kernel.h>

int snprintf(char *buf, size_t size, char const *fmt, ...)
{
	int ret;

	va_list args;
	va_start(args, fmt);
	ret = lx_emul_vsnprintf(buf, size, fmt, args);
	va_end(args);
	return ret;
}


#include <linux/device.h>

void dev_printk(const char *level, const struct device *dev,
                const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	lx_emul_vprintf(fmt, args);
	va_end(args);
}

void _dev_err(const struct device *dev, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	lx_emul_vprintf(fmt, args);
	va_end(args);
}


void _dev_warn(const struct device *dev, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	lx_emul_vprintf(fmt, args);
	va_end(args);
}


void _dev_info(const struct device *dev, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	lx_emul_vprintf(fmt, args);
	va_end(args);
}

static struct bus_type *_bus;

int bus_register(struct bus_type *bus)
{
	lx_emul_trace(__func__);

	if (_bus) {
		lx_emul_printf("%s: called twice\n", __func__);
		return -ENOMEM;
	}

	_bus = bus;

	return 0;
}


#include <linux/percpu-refcount.h>
#include <linux/mm.h>
#include <mm/slab.h>
#include <linux/slab.h>
#include <linux/page-flags.h>
#include <linux/gfp.h>


unsigned long __get_free_pages(gfp_t gfp_mask, unsigned int order)
{
	// XXX __get_free_pages Address_to_page_mapping
	if (order != 0) {
		lx_emul_printf("%s: order: %u\n", __func__, order);
	}

	return (unsigned long)lx_emul_kmalloc((1u << order) * PAGE_SIZE, 0);
}


void free_pages(unsigned long addr, unsigned int order)
{
	lx_emul_kfree((void const *)addr);
}


int set_page_dirty(struct page *page)
{
	set_bit(PG_dirty, &page->flags);
	return 0;
}


void *__kmalloc_node_track_caller(size_t size, gfp_t gfpflags, int node,
                                  unsigned long caller)
{
	(void)node;
	(void)caller;

	return lx_emul_kmalloc(size, gfpflags);
}


void *__kmalloc(size_t size, gfp_t flags)
{
	return lx_emul_kmalloc(size, flags);
}


void kfree(const void *x)
{
	lx_emul_kfree(x);
}


void *krealloc(const void *p, size_t new_size, gfp_t flags)
{
	void *np = lx_emul_kmalloc(new_size, flags);
	if (!np) {
		return NULL;
	}
	memcpy(np, np, new_size);
	kfree(p);
	return np;
}


size_t ksize(void const *objp)
{
	return lx_emul_ksize(objp);
}


void *kmem_cache_alloc(struct kmem_cache *s, gfp_t gfpflags)
{
	void *addr = lx_emul_kmem_cache_alloc(s);
	if (addr && s->ctor) {
		s->ctor(addr);
	}

	return addr;
}


struct kmem_cache *kmem_cache_create(const char *name, unsigned int size,
                                     unsigned int align, slab_flags_t flags,
                                     void (*ctor)(void *))
{
	int len = 0;
	char *cache_name = NULL;

	struct kmem_cache *cache =
		(struct kmem_cache*)kzalloc(sizeof (struct kmem_cache), GFP_KERNEL);

	if (!cache) {
		return NULL;
	}

	len = strlen(name);
	cache_name = (char *)kzalloc(len + 1, GFP_KERNEL);

	if (!cache_name) {
		kfree(cache);
		return 0;
	}
	cache_name[len] = 0;

	cache->name  = cache_name;
	cache->size  = size;
	cache->align = align;
	cache->ctor  = ctor;

	if (lx_emul_kmem_cache_create(cache, cache->size, cache->align)) {
		kfree(cache->name);
		kfree(cache);
		return NULL;
	}

	return cache;
}


void kmem_cache_free(struct kmem_cache *s, void *x)
{
	lx_emul_kmem_cache_free(s, x);
}


void *kvmalloc_node(size_t size, gfp_t flags, int node)
{
	return lx_emul_kmalloc(size, flags);
}


void kvfree(void const *addr)
{
	lx_emul_kfree(addr);
}


#include <linux/pagevec.h>

void __pagevec_release(struct pagevec *pvec)
{
	unsigned i;
	unsigned nr = pagevec_count(pvec);
	for (i = 0 ; i < nr; i++) {
		struct page *page = pvec->pages[i];
		int res = lx_emul_remove_page_to_address_page(page->mapping, page, page->index);
		if (res) {
			lx_emul_printf("%s: could not remove page: %p (index: %lu) from as: %p\n",
			               __func__, page, page->index, page->mapping);
		}
		kfree(page);
	}
	pagevec_reinit(pvec);
}


#include <linux/swap.h>

void check_move_unevictable_pages(struct pagevec *pvec)
{
	/* intentionally left blank */

	/*
	 * This functions is called from drm_gem_check_release_pagevec WRT
	 * to pagevec_release (see above).
	 */
}


#include <linux/of.h>

static struct device_node _vivante_gc = {
	.name = "vivante,gc",
	.full_name = "vivante,gc"
};

struct device_node *of_find_compatible_node(struct device_node *from,
                                            const char *type,
                                            const char *compatible)
{
	if (strcmp(compatible, _vivante_gc.name) == 0) {
		static int called = 0;
		// XXX this function is supposed to be called twice - wrap it better
		if (called > 2) {
			return NULL;
		}
		++called;
		return &_vivante_gc;
	}

	return NULL;
}


bool of_device_is_available(const struct device_node *device)
{
	if (device == &_vivante_gc) {
		return true;
	}

	return false;
}


int of_dma_configure(struct device *dev, struct device_node *np,
                     bool force_dma)
{
	LX_TRACE_PRINT("%s: dev: %p np: %p force_dma: %d\n", __func__,
	               dev, np, force_dma);
	return 0;
}


void of_node_put(struct device_node *node)
{
	lx_emul_trace(__func__);
}


#include <linux/string.h>
#include <linux/platform_device.h>

static int platform_match(struct device *dev, struct device_driver *drv)
{
	if (!dev->init_name)
		return 0;

	LX_TRACE_PRINT("init_name: '%s' name: '%s'\n", dev->init_name, drv->name);
	return strcmp(dev->init_name, drv->name) == 0;
}


#define to_platform_driver(drv) (container_of((drv), struct platform_driver, \
                                 driver))


static int platform_drv_probe(struct device *_dev)
{
	struct platform_driver *drv = to_platform_driver(_dev->driver);
	struct platform_device *dev = to_platform_device(_dev);

	return drv->probe(dev);
}


#include <linux/list.h>

struct Lx_driver
{
	struct list_head list;
	struct device_driver *driver;
	struct platform_driver *pdriver;
};
static LIST_HEAD(driver_list_head);


struct Lx_device
{
	struct list_head list;
	struct platform_device *pdev;
};
static LIST_HEAD(device_list_head);


void register_gpu_platform_device(void)
{
	struct platform_device *pdev = NULL;
	int err;

	pdev = platform_device_alloc("38000000.gpu3d", 0);
	if (!pdev) {
		lx_emul_printf("%s: could not alloc gpu3d platform device\n",
		               __func__);
		return;
	}

	err = platform_device_add(pdev);
	if (err) {
		lx_emul_printf("%s: could not add gpu3d platform device\n",
		               __func__);
		return;
	}
}


void probe_platform_bus(void)
{
	struct platform_device *pdev;
	struct Lx_device       *lx_dev;
	struct list_head       *lx_devp;

	struct platform_driver *pdrv;
	struct Lx_driver       *lx_drv;
	struct list_head       *lx_drvp;

	int err;

	list_for_each(lx_devp, &device_list_head) {
		lx_dev = (struct Lx_device*)lx_devp;
		pdev = lx_dev->pdev;

		list_for_each(lx_drvp, &driver_list_head) {
			lx_drv = (struct Lx_driver*)lx_drvp;
			pdrv = lx_drv->pdriver;

			if (strcmp(pdrv->driver.name, "etnaviv-gpu")) {
				continue;
			}

			err = pdrv->probe(pdev);
			if (err) {
				lx_emul_printf("%s: probe for '%s' returned error: %d\n",
				               __func__, pdrv->driver.name, err);
			}
		}
	}
}


int __platform_driver_register(struct platform_driver *drv, struct module *mod)
{
	struct Lx_driver *driver = NULL;

	/* init platform_bus_type */
	platform_bus_type.match = platform_match;
	platform_bus_type.probe = platform_drv_probe;

	drv->driver.bus = &platform_bus_type;
	if (drv->probe)
		drv->driver.probe = platform_drv_probe;

	lx_emul_printf("Register: %s\n", drv->driver.name);
	driver = (struct Lx_driver*)kzalloc(sizeof (struct Lx_driver), 0);
	//driver->driver = &drv->driver;
	driver->pdriver = drv;
	list_add(&driver->list, &driver_list_head);
	return 0;
}


struct platform_device *platform_device_alloc(const char *name, int id)
{
	struct platform_device *pdev =
		(struct platform_device *)kzalloc(sizeof (struct platform_device),
		                                  GFP_KERNEL);

	int len = 0;
	char *pdev_name = NULL;

	if (!pdev)
		return 0;

	len = strlen(name);
	pdev_name = (char *)kzalloc(len + 1, GFP_KERNEL);

	if (!pdev_name) {
		kfree(pdev);
		return 0;
	}
	strncpy(pdev_name, name, len + 1);
	pdev_name[len] = 0;

	pdev->name = pdev_name;
	pdev->id = id;
	pdev->dev.dma_mask = (u64*)kzalloc(sizeof(u64),  GFP_KERNEL);

	spin_lock_init(&pdev->dev.devres_lock);
	INIT_LIST_HEAD(&pdev->dev.devres_head);

	LX_TRACE_PRINT("%s:%d name: '%s' (%s) %d\n", __func__, __LINE__, pdev->name, name, len);
	return pdev;
}


int platform_get_irq(struct platform_device *dev, unsigned int num)
{
	LX_TRACE_PRINT("%s: dev: %p num: %u\n", __func__, dev, num);
	return GPU3D_INTR;
}


struct bus_type platform_bus_type = {
	.name  = "platform",
};


int platform_device_add(struct platform_device *pdev)
{
	struct device *dev = NULL;
	struct list_head *p = NULL;

	struct Lx_device *lx_device;

	struct Lx_driver        *D   = NULL;
	struct platform_driver *pdrv;
	struct device_driver *drv = NULL;
	int match = 0;
	int err = 0;

	if (!pdev->dev.bus) {
		pdev->dev.bus  = &platform_bus_type;
	}

	pdev->dev.init_name = pdev->name;

	// XXX proper place for setting dev.of_node?
	pdev->dev.of_node = &_vivante_gc;

	/*Set parent to ourselfs */
	if (!pdev->dev.parent) {
		pdev->dev.parent = &pdev->dev;
	}

	dev = &pdev->dev;

	lx_device = (struct Lx_device*)kzalloc(sizeof (struct Lx_device), 0);
	if (!lx_device) {
		return -1;
	}
	lx_device->pdev = pdev;
	list_add(&lx_device->list, &device_list_head);

	if (dev->driver) {
		return 0;
	}

	/* foreach driver match and probe device */
	list_for_each(p, &driver_list_head) {
		D   = (struct Lx_driver*)p;
		pdrv = D->pdriver;
		drv = &pdrv->driver;

		if (drv->bus != dev->bus) {
			continue;
		}
		match = 1;
		if (drv->bus->match) {
			match = drv->bus->match(dev, drv);
		}

		if (!match) {
			continue;
		}

		err = 1;
		dev->driver = drv;
		if (dev->bus->probe) {
			err = dev->bus->probe(dev);
		} else if (drv->probe) {
			// XXX check probe, try_to_bring_up_master() fails
			err = drv->probe(dev);
		}

		if (!err) {
			return 0;
		}
	}

	return -1;
}


void __iomem *devm_platform_ioremap_resource(struct platform_device *pdev,
                                             unsigned int index)
{
	LX_TRACE_PRINT("%s: pdev: %p index: %u\n", __func__, pdev, index);
	return lx_emul_devm_platform_ioremap_resource(pdev, index);
}


#include <linux/clk.h>

struct clk *devm_clk_get(struct device *dev, char const *id)
{
	return lx_emul_devm_clk_get(dev, id);
}


void clk_disable(struct clk * clk)
{
	lx_emul_trace_and_stop(__func__);
}


int clk_enable(struct clk * clk)
{
	lx_emul_trace(__func__);
	return 0;
}


unsigned long clk_get_rate(struct clk * clk)
{
	return lx_emul_clk_get_rate(clk);
}


int clk_prepare(struct clk * clk)
{
	lx_emul_trace(__func__);
	return 0;
}


int clk_set_rate(struct clk * clk,unsigned long rate)
{
	lx_emul_trace(__func__);
	return 0;
}


void clk_unprepare(struct clk * clk)
{
	lx_emul_trace(__func__);
}


#include <linux/interrupt.h>

int devm_request_threaded_irq(struct device *dev, unsigned int irq,
                              irq_handler_t handler, irq_handler_t thread_fn,
                              unsigned long irqflags, const char *devname,
                              void *dev_id)
{
	typedef int (*handler_func)(int, void*);
	handler_func hf;
	handler_func tf;


	int id = 0;
	switch (irq) {
	case GPU3D_INTR: id = GPU3D; break;
	default:
		lx_emul_printf("%s:%d: error IRQ %d not found\n",
		               __func__, __LINE__, irq);
		return -1; // XXX -ENODEV ?
		break;
	}

	hf = (handler_func)handler;
	tf = (handler_func)thread_fn;

	return lx_emul_devm_request_threaded_irq(id, irq, hf, dev_id, tf);
}


int genode_emul_interrupt_handler(void *dev, unsigned int irq,
                                  int (*handler)(int, void *),
                                  int (*thread_fn)(int, void*))
{
	irq_handler_t lx_handler;
	irq_handler_t lx_thread_fn;

	lx_handler   = (irq_handler_t)handler;
	lx_thread_fn = (irq_handler_t)thread_fn;

	if (!lx_handler) {
		lx_thread_fn(irq, dev);
		return 1;
	}

	switch (lx_handler(irq, dev)) {
	case IRQ_WAKE_THREAD:
		lx_thread_fn(irq, dev);
		return 1;
	case IRQ_HANDLED:
		return 1;
	case IRQ_NONE:
		break;
	}
	return 0;
}


#include <linux/timer.h>

void init_timer_key(struct timer_list *timer,
                    void (*func)(struct timer_list *),
                    unsigned int flags, char const *name,
                    struct lock_class_key *key)
{
	timer->entry.pprev = NULL;
	timer->function    = func;
	timer->flags       = flags;
}


void genode_emul_update_expires_timer(void *t, unsigned long expires)
{
	struct timer_list *timer = (struct timer_list*)t;
	timer->expires = expires;
}


void genode_emul_execute_timer(void *t)
{
	struct timer_list *timer = (struct timer_list*)t;
	if (timer->function) {
		timer->function(timer);
	}
}


#include <linux/timekeeping.h>

u64 ktime_get_mono_fast_ns(void)
{
	return lx_emul_ktime_get_mono_fast_ns();
}


void ktime_get_ts64(struct timespec64 * ts)
{
	u64 const ns = lx_emul_ktime_get_mono_fast_ns();
	ts->tv_sec  = ns / NSEC_PER_SEC;
	ts->tv_nsec = ns - (ts->tv_sec * NSEC_PER_SEC);
}


ktime_t ktime_get(void)
{
	return (ktime_t)ktime_get_mono_fast_ns();
}


#include <linux/mutex.h>

void __sched mutex_lock(struct mutex *lock)
{
	struct mutex_waiter waiter;

	unsigned long current_task = 0;
	unsigned long lock_task = 0;
	int mutex_free = 0;
	while (1) {

		current_task = lx_emul_current_task();
		lock_task    = atomic_long_read(&lock->owner);
		mutex_free   = (lock_task == 0);

		if (mutex_free) {
			/* there is no owner, its free */
			atomic_long_set(&lock->owner, current_task);
			break;
		}

		if (lock_task == current_task) {
			lx_emul_printf("%s: mutex: %p owner: %p recursive locked\n",
			               __func__, lock, (void*)lock_task);
			break;
		}

		waiter.task = (struct task_struct *)current_task;

		list_add_tail(&waiter.list, &lock->wait_list);

		lx_emul_block_current_task();
	}
}


void __sched mutex_unlock(struct mutex *lock)
{
	unsigned long current_task  = lx_emul_current_task();
	unsigned long lock_task     = atomic_long_read(&lock->owner);
	unsigned long waiter_task   = 0;
	struct mutex_waiter *waiter = NULL;

	if (lock_task != current_task) {
		lx_emul_printf("%s: mutex: %p owner: %p current_task: %p\n",
		               __func__, lock, (void*)lock_task,
		               (void*)current_task);
		return;
	}

	atomic_long_set(&lock->owner, 0);

	if (!list_empty(&lock->wait_list)) {
		waiter = list_first_entry(&lock->wait_list,
			                      struct mutex_waiter, list);
		if (waiter) {
			waiter_task = (unsigned long)waiter->task;
			lx_emul_unblock_task(waiter_task);
		} else {
			LX_TRACE_PRINT("%s: lock: %px wait_list: %px not empty but waiter NULL from: %px\n",
			               __func__, &lock->wait_list, lock, __builtin_return_address(0));
		}
	}
}


void __mutex_init(struct mutex *lock, const char *name,
                  struct lock_class_key * key)
{
	atomic_long_set(&lock->owner, 0);
	INIT_LIST_HEAD(&lock->wait_list);
}


bool mutex_is_locked(struct mutex *lock)
{
	return atomic_long_read(&lock->owner) != 0;
}


/************************
 ** DRM implementation **
 ************************/

#include <drm/drm_print.h>

void drm_dbg(unsigned int category, char const *fmt, ...)
{
#if 0
	va_list args;
	va_start(args, fmt);
	lx_emul_vprintf(fmt, args);
	va_end(args);
#endif
}


void drm_err(char const *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	lx_emul_vprintf(fmt, args);
	va_end(args);
}


#include <drm/drm_drv.h>

unsigned int drm_debug = 0x0;

struct drm_device *drm_dev_alloc(struct drm_driver *driver,
				 struct device *parent)
{
	struct drm_device *dev;
	int ret;

	dev = (struct drm_device*)kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return (struct drm_device*)ERR_PTR(-ENOMEM);

	ret = drm_dev_init(dev, driver, parent);
	if (ret) {
		kfree(dev);
		return (struct drm_device*)ERR_PTR(ret);
	}

	return dev;
}


#include <drivers/gpu/drm/drm_internal.h>


int drm_dev_init(struct drm_device *dev, struct drm_driver *driver,
                 struct device *parent)
{
	kref_init(&dev->ref);
	dev->dev = parent;
	dev->driver = driver;

	dev->driver_features = ~0u;

	INIT_LIST_HEAD(&dev->filelist);
	INIT_LIST_HEAD(&dev->ctxlist);
	INIT_LIST_HEAD(&dev->vmalist);
	INIT_LIST_HEAD(&dev->maplist);
	INIT_LIST_HEAD(&dev->vblank_event_list);

	spin_lock_init(&dev->buf_lock);
	spin_lock_init(&dev->event_lock);
	mutex_init(&dev->struct_mutex);
	mutex_init(&dev->filelist_mutex);
	mutex_init(&dev->ctxlist_mutex);
	mutex_init(&dev->master_mutex);

	if (drm_gem_init(dev)) {
		lx_emul_printf("Error: cannot initialize GEM\n");
		return -1;
	}

	return 0;
}


struct drm_device *_lx_drm_device;


int drm_dev_register(struct drm_device *dev, unsigned long flags)
{
	int ret = 0;

	if (_lx_drm_device) {
		return -1;
	}

	_lx_drm_device = dev;

	dev->registered = true;

	if (dev->driver->load) {
		ret = dev->driver->load(dev, flags);
		if (ret)
			return ret;
	}

	return 0;
}


#include <drm/drm_file.h>

struct drm_file *_lx_drm_file;

static struct file *_lx_file;

static void drm_get_minor(struct drm_device *dev, struct drm_minor **minor, int type)
{
	struct drm_minor *new_minor = (struct drm_minor*)
		kzalloc(sizeof(struct drm_minor), GFP_KERNEL);
	new_minor->type = type;
	new_minor->dev = dev;
	new_minor->kdev = dev->dev;
	*minor = new_minor;
}

int lx_drm_open(void)
{
	int err = 0;
	struct drm_driver *drv;

	if (!_lx_drm_device) {
		return -1;
	}

	drv = _lx_drm_device->driver;
	if (!drv) {
		return -2;
	}

	if (!_lx_drm_file) {
		_lx_drm_file = (struct drm_file*)kzalloc(sizeof (*_lx_drm_file), 0);
		if (!_lx_drm_file) {
			return -3;
		}
	}

	err = drv->open(_lx_drm_device, _lx_drm_file);
	if (!err) {
		_lx_file = (struct file*)kzalloc(sizeof (*_lx_file), 0);
		if (!_lx_file) {
			kfree(_lx_drm_file);
			return -4;
		}

		drm_get_minor(_lx_drm_device, &_lx_drm_device->primary,
		              DRM_MINOR_RENDER);

		_lx_drm_file->minor = _lx_drm_device->primary;
		_lx_file->private_data = _lx_drm_file;
	}
	return err;
}


#include <drm/drm_ioctl.h>
#include <uapi/drm/drm.h>
#include <uapi/drm/etnaviv_drm.h>

static void lx_drm_gem_submit_in(struct drm_etnaviv_gem_submit *submit)
{
	submit->bos    += (unsigned long)submit;
	submit->relocs += (unsigned long)submit;
	submit->pmrs   += (unsigned long)submit;
	submit->stream += (unsigned long)submit;
}


static void lx_drm_version_in(struct drm_version *version)
{
	/* set proper pointer value from offset */
	version->name += (unsigned long)version;
	version->date += (unsigned long)version;
	version->desc += (unsigned long)version;
}


static void lx_drm_version_out(struct drm_version *version)
{
	/* set proper offset value from pointer */
	version->name -= (unsigned long)version;
	version->date -= (unsigned long)version;
	version->desc -= (unsigned long)version;
}


static int lx_drm_in(unsigned int cmd, unsigned long arg)
{
	unsigned int const nr = DRM_IOCTL_NR(cmd);
	bool const is_driver_ioctl =
		nr >= DRM_COMMAND_BASE && nr < DRM_COMMAND_END;

	if (is_driver_ioctl) {
		unsigned const int dnr = nr - DRM_COMMAND_BASE;

		switch (dnr) {
		case DRM_ETNAVIV_GEM_SUBMIT:
			lx_drm_gem_submit_in((struct drm_etnaviv_gem_submit*)arg);
			break;
		default:
			break;
		}
	} else {
		switch (nr) {
		case DRM_IOCTL_NR(DRM_IOCTL_VERSION):
			lx_drm_version_in((struct drm_version*)arg);
			break;
		default:
			break;
		}
	}
	return 0;
}


static int lx_drm_out(unsigned int cmd, unsigned long arg)
{
	unsigned int const nr = DRM_IOCTL_NR(cmd);
	bool const is_driver_ioctl =
		nr >= DRM_COMMAND_BASE && nr < DRM_COMMAND_END;

	if (is_driver_ioctl) {
		unsigned const int dnr = nr - DRM_COMMAND_BASE;

		switch (dnr) {
		default:
			break;
		}
	} else {
		switch (nr) {
		case DRM_IOCTL_NR(DRM_IOCTL_VERSION):
			lx_drm_version_out((struct drm_version*)arg);
			break;
		default:
			break;
		}
	}
	return 0;
}


int lx_drm_ioctl(unsigned int cmd, unsigned long arg)
{
	int res = -1;

	if (cmd & IOC_IN) {
		lx_drm_in(cmd, arg);
	}
	res = drm_ioctl(_lx_file, cmd, arg);
	if (cmd & IOC_OUT) {
		lx_drm_out(cmd, arg);
	}
	return res;
}


#include <drm/drm_gem.h>
#include <drm/drm_vma_manager.h>

void *genode_lookup_mapping_from_offset(unsigned long offset,
                                        unsigned long size)
{
	struct drm_vma_offset_manager *mgr;
	struct drm_vma_offset_node *node;

	LX_TRACE_PRINT("%s:%d offset: 0x%lx size: %lu vma_offset_manager: %px\n", __func__, __LINE__,
	               offset, size, _lx_drm_device->vma_offset_manager);

	mgr = _lx_drm_device->vma_offset_manager;

	drm_vma_offset_lock_lookup(mgr);
	node = drm_vma_offset_lookup_locked(mgr, offset / PAGE_SIZE,
	                                    size / PAGE_SIZE);
	drm_vma_offset_unlock_lookup(mgr);

	LX_TRACE_PRINT("%s:%d node: %px\n", __func__, __LINE__, node);
	if (node) {
		struct drm_gem_object *obj =
			container_of(node, struct drm_gem_object, vma_node);
		if (obj) {
			struct file *f = obj->filp;
			return f ? f->f_mapping : NULL;
		}
	}
	return NULL;
}


#include <linux/wait.h>

void __init_waitqueue_head(struct wait_queue_head *wq_head, const char *name,
                           struct lock_class_key *key)
{
	LX_TRACE_PRINT("%s:%d\n", __func__, __LINE__);
	INIT_LIST_HEAD(&wq_head->head);
}


static int __wake_function(struct wait_queue_entry *wq_entry,
                           unsigned mode, int sync, void *key)
{
	LX_TRACE_PRINT("%s:%d wq_entry: %px mode: %x sync: %d key: %px called\n",
	               __func__, __LINE__, wq_entry, mode, sync, key);
	if (wq_entry->private) {
		LX_TRACE_PRINT("unblock: %px\n", (void*)wq_entry->private);
		lx_emul_unblock_task((unsigned long)wq_entry->private);
	}
	return 0;
}


void init_wait_entry(struct wait_queue_entry * wq_entry,int flags)
{
	wq_entry->flags = flags;
	wq_entry->private = (void*)lx_emul_current_task();
	wq_entry->func = __wake_function;
	INIT_LIST_HEAD(&wq_entry->entry);
}


long prepare_to_wait_event(struct wait_queue_head *wq_head,
                           struct wait_queue_entry *wq_entry,
                           int state)
{
	LX_TRACE_PRINT("%s:%d wq_head: %px wq_entry: %px state: %d not completely implemented\n",
	               __func__, __LINE__, wq_head, wq_entry, state);
	// XXX check WQ_EXCLUSIVE etc. pp
	if (list_empty(&wq_entry->entry)) {
		__add_wait_queue(wq_head, wq_entry);
	}
	// XXX current task state change?

	return 0;
}


void finish_wait(struct wait_queue_head *wq_head,
                 struct wait_queue_entry *wq_entry)
{
	LX_TRACE_PRINT("%s:%d wq_head: %px wq_entry: %px\n", __func__,
	               __LINE__, wq_head, wq_entry);

	if (!list_empty_careful(&wq_entry->entry)) {
		list_del_init(&wq_entry->entry);
	}
}


void __wake_up(struct wait_queue_head *wq_head, unsigned int mode,
               int nr_exclusive, void *key)
{
	wait_queue_entry_t *curr, *next;
	LX_TRACE_PRINT("%s:%d wq_head: %px\n", __func__, __LINE__, wq_head);

	curr = list_first_entry(&wq_head->head, wait_queue_entry_t, entry); 

	if (&curr->entry == &wq_head->head)
		return; //nr_exclusive;

	list_for_each_entry_safe_from(curr, next, &wq_head->head, entry) {
		(void)curr->func(curr, mode, 0, key);
	}
}


#include <linux/dma-mapping.h>

void *dma_alloc_attrs(struct device *dev, size_t size, dma_addr_t *dma_handle,
                      gfp_t flag, unsigned long attrs)
{
	int dma_wc;
	struct Lx_dma lx_dma;

	dma_wc = (attrs & DMA_ATTR_WRITE_COMBINE);

	lx_dma = lx_emul_dma_alloc_attrs(dev, size, dma_wc);
	if (!lx_dma.vaddr && !lx_dma.paddr) {
		return NULL;
	}

	LX_TRACE_PRINT("%s:%d size: %zu paddr: 0x%lx vaddr: 0x%lx\n", __func__, __LINE__,
	               size, lx_dma.paddr, lx_dma.vaddr);

	*dma_handle = lx_dma.paddr;
	return (void*)lx_dma.vaddr;
}


void dma_free_attrs(struct device *dev, size_t size, void *cpu_addr,
                    dma_addr_t dma_handle, unsigned long attrs)
{
	lx_emul_dma_free_attrs(dev, (unsigned long)size,
	                       (unsigned long)cpu_addr,
	                       (unsigned long)dma_handle);
}


u64 dma_get_required_mask(struct device * dev)
{
	enum { DMA_MASK = 0xbfffffffUL, }; // XXX query board?
	LX_TRACE_PRINT("%s: return 0x%x\n", __func__, DMA_MASK);
	return DMA_MASK;
}


int dma_direct_map_sg(struct device *dev, struct scatterlist *sgl,
                      int nents, enum dma_data_direction dir,
                      unsigned long attrs)
{
	int i;
	struct scatterlist *sg;
	struct Lx_dma dma;

	for_each_sg(sgl, sg, nents, i) {
		struct page *page = sg_page(sg);
		dma = lx_emul_get_dma_address_for_page(page->mapping, page);
		if (!dma.vaddr && !dma.paddr) {
			BUG();
		}
		sg->dma_address = dma.paddr;
		sg_dma_len(sg) = sg->length;
		LX_TRACE_PRINT("%s: i: %d page: %px offset: %u length: %u dma_addr: 0x%llx\n",
		               __func__, i, page, sg->offset, sg->length, sg->dma_address);
	}

	return 0;
}


void dma_direct_unmap_sg(struct device *dev, struct scatterlist *sgl,
                         int nents, enum dma_data_direction dir,
                         unsigned long attrs)
{
	int i;
	struct scatterlist *sg;

	for_each_sg(sgl, sg, nents, i) {

		if (!(attrs & DMA_ATTR_SKIP_CPU_SYNC)) {
			LX_TRACE_PRINT("%s: dma_direct_sync_single_for_cpu(0x%llx) not implemented\n",
			               __func__, sg->dma_address);
		}
		sg->dma_address = 0;
	}
}


#include <linux/workqueue.h>

struct workqueue_struct *alloc_workqueue(const char *fmt, unsigned int flags,
                                         int max_active, ...)
{
	return lx_emul_alloc_workqueue(fmt, flags);
}


void genode_emul_execute_work(void *w)
{
	struct work_struct *work = (struct work_struct*)w;
	work->func(work);
}


bool cancel_delayed_work(struct delayed_work *dwork)
{
	return lx_emul_del_timer(&dwork->timer);
}


bool queue_work_on(int cpu, struct workqueue_struct *wq,
                   struct work_struct *work)
{
	if (!work || !work->func) {
		lx_emul_printf("%s:%d invalid work from: %px\n",
		               __func__, __LINE__, __builtin_return_address(0));
		lx_emul_trace_and_stop(__func__);
	}

	return lx_emul_schedule_work(wq, work);
}


static void delayed_work_timer_func(struct timer_list *list)
{
	struct delayed_work *dwork = from_timer(dwork, list, timer);
	(void)queue_work_on(0, dwork->wq, &dwork->work);
}


bool queue_delayed_work_on(int cpu, struct workqueue_struct *wq,
                           struct delayed_work *dwork, unsigned long delay)
{
	dwork->wq = wq;

	if (delay == 0) {
		delayed_work_timer_func(&dwork->timer);
	} else {
		unsigned long expires = lx_emul_absolute_timeout(delay);
		dwork->timer.function = delayed_work_timer_func;
		(void)lx_emul_mod_timer(&dwork->timer, expires);
	}

	return true;
}


#include <linux/kthread.h>

struct task_struct *kthread_create_on_node(int (* threadfn)(void *data),
                                           void * data, int node,
                                           const char namefmt[], ...)
{
	struct task_struct *lx_task;
	int err;

	lx_task = (struct task_struct*)kzalloc(sizeof (*lx_task), 0);
	if (!lx_task) {
		return ERR_PTR(-ENOMEM);
	}

	err = lx_emul_create_task(lx_task, threadfn, data);
	if (err) {
		return ERR_PTR(-ENOMEM);
	}

	return lx_task;
}


struct park_task
{
	unsigned long parked_task;
	unsigned long waiter_task;
};


static struct park_task _parked;


int kthread_park(struct task_struct *k)
{
	int err;
	unsigned long task;
	unsigned long current_task;

	err = lx_emul_lookup_task(k, &task);
	if (err) {
		return err;
	}

	if (_parked.parked_task || _parked.waiter_task) {
		lx_emul_printf("%s:%d cannot park %px, already waiting\n",
		               __func__, __LINE__, (void*)task);
		lx_emul_trace_and_stop(__func__);
	}

	current_task = lx_emul_current_task();

	if (task == current_task) {
		lx_emul_printf("%s:%d cannot park myself: %px\n",
		               __func__, __LINE__, (void*)task);
		lx_emul_trace_and_stop(__func__);
	}

	lx_emul_park_task(task);
	lx_emul_unblock_task(task);
	_parked.parked_task = task;
	_parked.waiter_task = current_task;

	/* kthread_parkme should wake us up again */
	lx_emul_block_current_task();
	return 0;
}


void kthread_parkme(void)
{
	unsigned long current_task;

	current_task = lx_emul_current_task();

	if (_parked.parked_task != current_task || !_parked.waiter_task) {
		lx_emul_printf("%s:%d cannot parkme %px\n",
		               __func__, __LINE__, (void*)current_task);
		lx_emul_trace_and_stop(__func__);
	}

	lx_emul_unblock_task(_parked.waiter_task);

	_parked.parked_task = 0;
	_parked.waiter_task = 0;

	lx_emul_parked_task(current_task);
	lx_emul_block_current_task();
}


bool kthread_should_park(void)
{
	unsigned long current_task = lx_emul_current_task();
	LX_TRACE_PRINT("%s: not completely implemented\n", __func__);
	return lx_emul_should_park_task(current_task);
}


bool kthread_should_stop(void)
{
	LX_TRACE_PRINT("%s: not completely implemented\n", __func__);
	return false;
}


int kthread_stop(struct task_struct * k)
{
	lx_emul_trace_and_stop(__func__);
}


void kthread_unpark(struct task_struct *k)
{
	int err;
	unsigned long task;

	err = lx_emul_lookup_task(k, &task);
	if (err) {
		lx_emul_printf("%s:%d cannot unpark not registered task: %px\n",
		               __func__, __LINE__, k);
		lx_emul_trace_and_stop(__func__);
	}

	lx_emul_unpark_task(task);
	lx_emul_unblock_task(task);
}


#include <asm-generic/delay.h>

void __const_udelay(unsigned long xloops)
{
	LX_TRACE_PRINT("%s:%d xloops: %lu from: %px\n", __func__, __LINE__,
	               xloops, __builtin_return_address(0));

	/*
	 * In 'etnaviv_gpu_wait_idle()' udelay(5) is called.
	 */
	lx_emul_usleep(5u);
}


#include <linux/delay.h>

void __sched usleep_range(unsigned long min, unsigned long max)
{
	lx_emul_usleep(min);
}


#include <linux/completion.h>

void complete(struct completion *x)
{
	x->done++;
	LX_TRACE_PRINT("%s: done: %u -- wake up not implemented yet\n",
	               __func__, x->done);
}


unsigned long __sched wait_for_completion_timeout(struct completion *x,
                                                  unsigned long timeout)
{
	if (!x->done) {
		lx_emul_printf("%s:%d x->done: %u - schedule_timeout not implemented\n",
		               __func__, __LINE__, x->done);
		lx_emul_trace_and_stop(__func__);
	}

	if (x->done) {
		x->done--;
	}

	return timeout;
}


#include <linux/sched.h>

asmlinkage __visible void __sched schedule(void)
{
	lx_emul_block_current_task();
}


struct task_struct *get_current(void)
{
	// XXX for now assume there is no code that accesses task_struct fields directly
	return (struct task_struct*)lx_emul_current_task();
}


struct timeout_task
{
	struct timer_list timer;
	unsigned long     task;
};


static void timeout_task_func(struct timer_list *list)
{
	struct timeout_task *to = from_timer(to, list, timer);
	lx_emul_unblock_task(to->task);
}


signed long __sched schedule_timeout(signed long timeout)
{
	unsigned long       current_task;
	unsigned long       expires;
	struct timeout_task to;

	memset(&to, 0, sizeof (to));

	current_task = lx_emul_current_task();
	expires = lx_emul_absolute_timeout(timeout);

	to.task           = current_task;
	to.timer.function = timeout_task_func;

	(void)lx_emul_mod_timer(&to.timer, expires);

	LX_TRACE_PRINT("%s:%d timeout: %ld expires: %lu\n", __func__, __LINE__,
	               timeout, expires);

	lx_emul_block_current_task();

	(void)lx_emul_del_timer(&to.timer);

	timeout = lx_emul_remaining_timeout(expires);

	LX_TRACE_PRINT("%s:%d timeout: %ld \n", __func__, __LINE__, timeout);

	return timeout < 0 ? 0 : timeout;
}


int wake_up_state(struct task_struct *p, unsigned int state)
{
	/*
	 * AFAICT this is only used for waking up the 'drm_worker' task
	 */
	lx_emul_unblock_task((unsigned long)p);
	return 1;
}


#include <linux/vmalloc.h>


void *__vmalloc(unsigned long size, gfp_t gfp_mask, pgprot_t prot)
{
	return lx_emul_vzalloc(size);
}


void *vzalloc(unsigned long size)
{
	return lx_emul_vzalloc(size);
}


void vfree(void const *addr)
{
	lx_emul_vfree(addr);
}


void *vmap(struct page **pages, unsigned int count, unsigned long flags,
           pgprot_t prot)
{
	unsigned i;
	struct page *p;
	struct address_space *mapping;
	pgoff_t index;

	/* use for continous check */
	mapping = pages[0]->mapping;
	index   = pages[0]->index;

	for (i = 1; i < count; i++) {
		p = pages[i];

		if (p->mapping != mapping || (p->index - 1 != index)) {
			lx_emul_printf("%s: page[%u]: %px not continous\n", __func__, i, p);
			lx_emul_trace_and_stop(__func__);
		}

		index = p->index;
		LX_TRACE_PRINT("%s: i: %u page: %px as: %px off: %ld\n", __func__, i, p, p->mapping, p->index);
	}

	return lx_emul_address_space_vmap(mapping);
}


void vunmap(void const *addr)
{
	if (addr) {
		lx_emul_trace_and_stop(__func__);
	}
}


#include <linux/mount.h>
#include <linux/fs.h>

struct vfsmount * kern_mount(struct file_system_type * type)
{
	struct vfsmount *m;

	m = kzalloc(sizeof (struct vfsmount), 0);
	if (!m) {
		return (struct vfsmount*)ERR_PTR(-ENOMEM);
	}

	return m;
}


void inode_set_bytes(struct inode *inode, loff_t bytes)
{
	inode->i_blocks = bytes >> 9;
	inode->i_bytes = bytes & 511;
}


static unsigned long _get_next_ino(void)
{
	static unsigned long count = 0;
	return ++count;
}


struct inode *alloc_anon_inode(struct super_block *s)
{
	struct inode *inode;

	inode = kzalloc(sizeof (struct inode), 0);
	if (!inode) {
		return (struct inode*)ERR_PTR(-ENOMEM);
	}

	inode->i_ino = _get_next_ino();

	return inode;
}


#include <linux/file.h>

struct file *alloc_file_pseudo(struct inode *inode, struct vfsmount *mnt,
                               char const *name, int flags,
                               struct file_operations const *fops)
{
	struct file *f;
	struct dentry *d;

	f = kzalloc(sizeof (struct file), 0);
	if (!f) {
		return (struct file*)ERR_PTR(-ENOMEM);
	}

	d = kzalloc(sizeof (struct dentry), 0);
	if (!d) {
		kfree(f);
		return (struct file*)ERR_PTR(-ENOMEM);
	}

	f->f_inode = inode;
	f->f_op = fops;
	f->f_path.dentry = d;

	return f;
}



#include <linux/shmem_fs.h>

struct file *shmem_file_setup(char const *name, loff_t size,
                               unsigned long flags)
{
	struct file *f;
	struct inode *inode;
	struct address_space *mapping;
	struct Lx_dma lx_dma;

	f = kzalloc(sizeof (struct file), 0);
	if (!f) {
		return (struct file*)ERR_PTR(-ENOMEM);
	}

	inode = kzalloc(sizeof (struct inode), 0);
	if (!inode) {
		goto err_inode;
	}

	mapping = kzalloc(sizeof (struct address_space), 0);
	if (!mapping) {
		goto err_mapping;
	}

	if (lx_emul_alloc_address_space(mapping, size)) {
		goto err_as;
	}

	lx_dma = lx_emul_dma_alloc_attrs(NULL, size, false);
	if (!lx_dma.vaddr && !lx_dma.paddr) {
		goto err_as;
	}

	LX_TRACE_PRINT("%s:%d paddr: 0x%lx vaddr: 0x%lx\n", __func__, __LINE__,
	               lx_dma.paddr, lx_dma.vaddr);

	lx_emul_add_dma_to_address_space(mapping, lx_dma);

	inode->i_mapping = mapping;

	atomic_long_set(&f->f_count, 1);
	f->f_inode    = inode;
	f->f_mapping  = mapping;
	f->f_flags    = flags;
	f->f_mode     = OPEN_FMODE(flags);
	f->f_mode    |= FMODE_OPENED;

	// XXX lookup dataspace cap later on for drm_mmap
	LX_TRACE_PRINT("%s:%d f: %px mapping: %px size: %llu dma: (0x%lx, 0x%lx)\n",
	               __func__, __LINE__, f, mapping, size, lx_dma.vaddr, lx_dma.paddr);

	return f;

err_as:
	kfree(mapping);
err_mapping:
	kfree(inode);
err_inode:
	kfree(f);
	return (struct file*)ERR_PTR(-ENOMEM);
}


struct page *shmem_read_mapping_page_gfp(struct address_space *mapping,
                                         pgoff_t index, gfp_t gfp)
{
	struct page *p = lx_emul_look_up_address_space_page(mapping, index);
	if (!p) {
		LX_TRACE_PRINT("%s: could not look up page in as: %px for index: %ld - insert new\n",
		               __func__, mapping, index);
		p = (struct page*)kzalloc(sizeof (struct page), 0);
		if (!p) {
			return (struct page*)ERR_PTR(-ENOMEM);
		}
		// XXX set page refcount to 1?
		p->mapping = mapping;
		p->index   = index;
		lx_emul_insert_page_to_address_page(mapping, p, index);
	}
	return p;
}


#include <linux/cpu.h>
#include <linux/cpumask.h>

struct cpumask __cpu_online_mask   = { .bits[0] = 1 };
struct cpumask __cpu_possible_mask = { .bits[0] = 1 };


#include <linux/file.h>

static void _free_file(struct file *file)
{
	struct inode *inode;
	struct address_space *mapping;
	struct Lx_dma lx_dma;

	LX_TRACE_PRINT("%s: file: %p f_count 0\n", __func__, file);

	mapping = file->f_mapping;
	inode   = file->f_inode;
	lx_dma  = lx_emul_get_dma_from_address_space(mapping);

	lx_emul_dma_free_attrs(NULL, 0, lx_dma.vaddr, lx_dma.paddr);
	lx_emul_free_address_space(mapping, 0);
	kfree(inode);
}


void fput(struct file *file)
{
	if (atomic_long_sub_and_test(1, &file->f_count)) {
		_free_file(file);
	}
}


#define FILE_FD_NUM 128

struct File_fd
{
	struct file *file;
	int fd;
};


static struct File_fd _file_fd_array[FILE_FD_NUM];


int get_unused_fd_flags(unsigned flags)
{
	static int counter = 42;

	int id;
	int i;

	(void)flags;

	id = -1;

	for (i = 0; i < FILE_FD_NUM; i++) {
		if (_file_fd_array[i].fd) {
			continue;
		}

		id = ++counter;
		_file_fd_array[i].fd = id;
		break;
	}

	return id;
}


void fd_install(unsigned int fd,struct file * file)
{
	int i;

	for (i = 0; i < FILE_FD_NUM; i++) {
		if (_file_fd_array[i].fd != fd) {
			continue;
		}

		_file_fd_array[i].file = file;
		break;
	}
}


struct file *fget(unsigned int fd)
{
	struct file *f;
	int i;

	f = NULL;

	for (i = 0; i < FILE_FD_NUM; i++) {
		if (_file_fd_array[i].fd != fd) {
			continue;
		}

		f = _file_fd_array[i].file;
		break;
	}

	return f;
}


#include <linux/rcupdate.h>

void call_rcu(struct rcu_head *head, rcu_callback_t func)
{
	func(head);
}


#include <linux/rcutree.h>

void kfree_call_rcu(struct rcu_head *head, rcu_callback_t func)
{
	// XXX kfree_call_rcu needs to implement but func pointer is part of NULL obj
	// lx_emul_printf("%s: ignore head: %px func: %px from: %px\n",
	//                 __func__, head, func, __builtin_return_address(0));
	// call_rcu(head, func);
}
