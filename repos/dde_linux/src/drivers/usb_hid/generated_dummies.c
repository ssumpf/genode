/*
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Automatically generated file - do no edit
 * \date   2023-06-14
 */

#include <lx_emul.h>


#include <linux/ratelimit_types.h>

int ___ratelimit(struct ratelimit_state * rs,const char * func)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cpumask.h>

struct cpumask __cpu_active_mask;


#include <linux/kfifo.h>

int __kfifo_alloc(struct __kfifo * fifo,unsigned int size,size_t esize,gfp_t gfp_mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kfifo.h>

void __kfifo_free(struct __kfifo * fifo)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kfifo.h>

unsigned int __kfifo_in(struct __kfifo * fifo,const void * buf,unsigned int len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kfifo.h>

unsigned int __kfifo_in_r(struct __kfifo * fifo,const void * buf,unsigned int len,size_t recsize)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kfifo.h>

unsigned int __kfifo_max_r(unsigned int len,size_t recsize)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kfifo.h>

unsigned int __kfifo_out(struct __kfifo * fifo,void * buf,unsigned int len)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kfifo.h>

unsigned int __kfifo_out_r(struct __kfifo * fifo,void * buf,unsigned int len,size_t recsize)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kfifo.h>

void __kfifo_skip_r(struct __kfifo * fifo,size_t recsize)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/task.h>

void __put_task_struct(struct task_struct * tsk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int __usb_get_extra_descriptor(char * buffer,unsigned size,unsigned char type,void ** ptr,size_t minsize)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmalloc.h>

void * __vmalloc_node_range(unsigned long size,unsigned long align,unsigned long start,unsigned long end,gfp_t gfp_mask,pgprot_t prot,unsigned long vm_flags,int node,const void * caller)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uaccess.h>

unsigned long _copy_from_user(void * to,const void __user * from,unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uaccess.h>

unsigned long _copy_to_user(void __user * to,const void * from,unsigned long n)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ctype.h>

const unsigned char _ctype[] = {};


#include <linux/printk.h>

int _printk_deferred(const char * fmt,...)
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


#include <linux/cdev.h>

int cdev_device_add(struct cdev * cdev,struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cdev.h>

void cdev_device_del(struct cdev * cdev,struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cdev.h>

void cdev_init(struct cdev * cdev,const struct file_operations * fops)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/leds.h>

int devm_led_classdev_register_ext(struct device * parent,struct led_classdev * led_cdev,struct led_init_data * init_data)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/leds.h>

int devm_led_trigger_register(struct device * dev,struct led_trigger * trig)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/power_supply.h>

struct power_supply * __must_check devm_power_supply_register(struct device * parent,const struct power_supply_desc * desc,const struct power_supply_config * cfg)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/semaphore.h>

void __sched down(struct semaphore * sem)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/semaphore.h>

int __sched down_interruptible(struct semaphore * sem)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/semaphore.h>

int __sched down_trylock(struct semaphore * sem)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/device/driver.h>

int driver_register(struct device_driver * drv)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

asmlinkage __visible void dump_stack(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int fasync_helper(int fd,struct file * filp,int on,struct fasync_struct ** fapp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uuid.h>

const u8 guid_index[16] = {};


#include <linux/init.h>

bool initcall_debug;


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


extern int input_event_from_user(const char __user * buffer,struct input_event * event);
int input_event_from_user(const char __user * buffer,struct input_event * event)
{
	lx_emul_trace_and_stop(__func__);
}


extern int input_event_to_user(char __user * buffer,const struct input_event * event);
int input_event_to_user(char __user * buffer,const struct input_event * event)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/input.h>

int input_ff_create_memless(struct input_dev * dev,void * data,int (* play_effect)(struct input_dev *,void *,struct ff_effect *))
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/input.h>

void input_ff_destroy(struct input_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int input_ff_effect_from_user(const char __user * buffer,size_t size,struct ff_effect * effect);
int input_ff_effect_from_user(const char __user * buffer,size_t size,struct ff_effect * effect)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/input.h>

int input_ff_erase(struct input_dev * dev,int effect_id,struct file * file)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/input.h>

int input_ff_event(struct input_dev * dev,unsigned int type,unsigned int code,int value)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/input.h>

int input_ff_upload(struct input_dev * dev,struct ff_effect * effect,struct file * file)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/math.h>

unsigned long int_sqrt(unsigned long x)
{
	lx_emul_trace_and_stop(__func__);
}


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

int irq_set_affinity(unsigned int irq,const struct cpumask * cpumask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq_work.h>

void irq_work_tick(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

bool is_vmalloc_addr(const void * x)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

void kill_fasync(struct fasync_struct ** fp,int sig,int band)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

int kobject_synth_uevent(struct kobject * kobj,const char * buf,size_t count)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

int kobject_uevent(struct kobject * kobj,enum kobject_action action)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/leds.h>

void led_trigger_event(struct led_trigger * trig,enum led_brightness brightness)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

bool parse_option_str(const char * str,const char * option)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/power_supply.h>

void power_supply_changed(struct power_supply * psy)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/power_supply.h>

void * power_supply_get_drvdata(struct power_supply * psy)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/power_supply.h>

int power_supply_powers(struct power_supply * psy,struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/radix-tree.h>

void * radix_tree_lookup(const struct radix_tree_root * root,unsigned long index)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/refcount.h>

void refcount_warn_saturate(refcount_t * r,enum refcount_saturation_type t)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int register_chrdev_region(dev_t from,unsigned count,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/siphash.h>

u64 siphash_1u64(const u64 first,const siphash_key_t * key)
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


#include <linux/fs.h>

int stream_open(struct inode * inode,struct file * filp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcupdate.h>

void synchronize_rcu(void)
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


#include <linux/semaphore.h>

void __sched up(struct semaphore * sem)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

void * usb_alloc_coherent(struct usb_device * dev,size_t size,gfp_t mem_flags,dma_addr_t * dma)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

struct urb * usb_alloc_urb(int iso_packets,gfp_t mem_flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

void usb_block_urb(struct urb * urb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_clear_halt(struct usb_device * dev,int pipe)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_control_msg(struct usb_device * dev,unsigned int pipe,__u8 request,__u8 requesttype,__u16 value,__u16 index,void * data,__u16 size,int timeout)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

void usb_free_coherent(struct usb_device * dev,size_t size,void * addr,dma_addr_t dma)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

void usb_free_urb(struct urb * urb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_interrupt_msg(struct usb_device * usb_dev,unsigned int pipe,void * data,int len,int * actual_length,int timeout)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

void usb_kill_urb(struct urb * urb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

void usb_queue_reset_device(struct usb_interface * iface)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_register_driver(struct usb_driver * new_driver,struct module * owner,const char * mod_name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_string(struct usb_device * dev,int index,char * buf,size_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_submit_urb(struct urb * urb,gfp_t mem_flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_unlink_urb(struct urb * urb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

void usb_unpoison_urb(struct urb * urb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uuid.h>

const u8 uuid_index[16] = {};


#include <linux/vmalloc.h>

void vfree(const void * addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmalloc.h>

void * vzalloc(unsigned long size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/wake_q.h>

void wake_q_add_safe(struct wake_q_head * head,struct task_struct * task)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/xarray.h>

void xas_clear_mark(const struct xa_state * xas,xa_mark_t mark)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/xarray.h>

void * xas_find_marked(struct xa_state * xas,unsigned long max,xa_mark_t mark)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/xarray.h>

void * xas_load(struct xa_state * xas)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/xarray.h>

bool xas_nomem(struct xa_state * xas,gfp_t gfp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/xarray.h>

void xas_set_mark(const struct xa_state * xas,xa_mark_t mark)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/xarray.h>

void * xas_store(struct xa_state * xas,void * entry)
{
	lx_emul_trace_and_stop(__func__);
}

