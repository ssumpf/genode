/*
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Automatically generated file - do no edit
 * \date   2023-06-15
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


#include <linux/printk.h>

int __printk_ratelimit(const char * func)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

void __printk_safe_enter(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

void __printk_safe_exit(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/task.h>

void __put_task_struct(struct task_struct * tsk)
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


extern void ack_bad_irq(unsigned int irq);
void ack_bad_irq(unsigned int irq)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/random.h>

void add_device_randomness(const void * buf,size_t len)
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


#include <linux/rcuwait.h>

void finish_rcuwait(struct rcuwait * w)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uuid.h>

const u8 guid_index[16] = {};


#include <linux/usb/hcd.h>

void * hcd_buffer_alloc(struct usb_bus * bus,size_t size,gfp_t mem_flags,dma_addr_t * dma)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb/hcd.h>

void hcd_buffer_free(struct usb_bus * bus,size_t size,void * addr,dma_addr_t dma)
{
	lx_emul_trace_and_stop(__func__);
}


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

int irq_can_set_affinity(unsigned int irq)
{
	lx_emul_trace_and_stop(__func__);
}


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


#include <linux/slab.h>

void * kmem_cache_alloc_lru(struct kmem_cache * cachep,struct list_lru * lru,gfp_t flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

int kobject_synth_uevent(struct kobject * kobj,const char * buf,size_t count)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

int kobject_uevent_env(struct kobject * kobj,enum kobject_action action,char * envp_ext[])
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/leds.h>

void led_trigger_event(struct led_trigger * trig,enum led_brightness brightness)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/moduleparam.h>

int param_set_copystring(const char * val,const struct kernel_param * kp)
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


#include <linux/refcount.h>

void refcount_warn_saturate(refcount_t * r,enum refcount_saturation_type t)
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


#include <linux/jump_label.h>

bool static_key_initialized;


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

struct urb * usb_alloc_urb(int iso_packets,gfp_t mem_flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

void usb_block_urb(struct urb * urb)
{
	lx_emul_trace_and_stop(__func__);
}


extern char * usb_cache_string(struct usb_device * udev,int index);
char * usb_cache_string(struct usb_device * udev,int index)
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


extern int usb_create_ep_devs(struct device * parent,struct usb_host_endpoint * endpoint,struct usb_device * udev);
int usb_create_ep_devs(struct device * parent,struct usb_host_endpoint * endpoint,struct usb_device * udev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int usb_create_sysfs_dev_files(struct usb_device * udev);
int usb_create_sysfs_dev_files(struct usb_device * udev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_create_sysfs_intf_files(struct usb_interface * intf);
void usb_create_sysfs_intf_files(struct usb_interface * intf)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_devio_cleanup(void);
void usb_devio_cleanup(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_disable_device(struct usb_device * dev,int skip_ep0);
void usb_disable_device(struct usb_device * dev,int skip_ep0)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_disable_endpoint(struct usb_device * dev,unsigned int epaddr,bool reset_hardware);
void usb_disable_endpoint(struct usb_device * dev,unsigned int epaddr,bool reset_hardware)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_disable_interface(struct usb_device * dev,struct usb_interface * intf,bool reset_hardware);
void usb_disable_interface(struct usb_device * dev,struct usb_interface * intf,bool reset_hardware)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_enable_endpoint(struct usb_device * dev,struct usb_host_endpoint * ep,bool reset_ep);
void usb_enable_endpoint(struct usb_device * dev,struct usb_host_endpoint * ep,bool reset_ep)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_enable_interface(struct usb_device * dev,struct usb_interface * intf,bool reset_eps);
void usb_enable_interface(struct usb_device * dev,struct usb_interface * intf,bool reset_eps)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_free_streams(struct usb_interface * interface,struct usb_host_endpoint ** eps,unsigned int num_eps,gfp_t mem_flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

void usb_free_urb(struct urb * urb)
{
	lx_emul_trace_and_stop(__func__);
}


extern int usb_get_device_descriptor(struct usb_device * dev,unsigned int size);
int usb_get_device_descriptor(struct usb_device * dev,unsigned int size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb/hcd.h>

struct usb_hcd * usb_get_hcd(struct usb_hcd * hcd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_get_status(struct usb_device * dev,int recip,int type,int target,void * data)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb/hcd.h>

int usb_hcd_alloc_bandwidth(struct usb_device * udev,struct usb_host_config * new_config,struct usb_host_interface * cur_alt,struct usb_host_interface * new_alt)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb/hcd.h>

int usb_hcd_find_raw_port_number(struct usb_hcd * hcd,int port1)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb/hcd.h>

void usb_hcd_synchronize_unlinks(struct usb_device * udev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int usb_hub_create_port_device(struct usb_hub * hub,int port1);
int usb_hub_create_port_device(struct usb_hub * hub,int port1)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_hub_remove_port_device(struct usb_hub * hub,int port1);
void usb_hub_remove_port_device(struct usb_hub * hub,int port1)
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


extern void usb_major_cleanup(void);
void usb_major_cleanup(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_notify_add_device(struct usb_device * udev);
void usb_notify_add_device(struct usb_device * udev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_notify_remove_device(struct usb_device * udev);
void usb_notify_remove_device(struct usb_device * udev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb/hcd.h>

void usb_put_hcd(struct usb_hcd * hcd)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_remove_ep_devs(struct usb_host_endpoint * endpoint);
void usb_remove_ep_devs(struct usb_host_endpoint * endpoint)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_remove_sysfs_dev_files(struct usb_device * udev);
void usb_remove_sysfs_dev_files(struct usb_device * udev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void usb_remove_sysfs_intf_files(struct usb_interface * intf);
void usb_remove_sysfs_intf_files(struct usb_interface * intf)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_set_configuration(struct usb_device * dev,int configuration)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb.h>

int usb_set_interface(struct usb_device * dev,int interface,int alternate)
{
	lx_emul_trace_and_stop(__func__);
}


extern int usb_set_isoch_delay(struct usb_device * dev);
int usb_set_isoch_delay(struct usb_device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/usb/ch9.h>

const char * usb_speed_string(enum usb_device_speed speed)
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

