/*
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Automatically generated file - do no edit
 * \date   2022-05-04
 */

#include <lx_emul.h>


#include <linux/proc_fs.h>

void * PDE_DATA(const struct inode * inode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/ratelimit_types.h>

int ___ratelimit(struct ratelimit_state * rs,const char * func)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/clk-provider.h>

const char * __clk_get_name(const struct clk * clk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm-generic/delay.h>

noinline void __const_udelay(unsigned long xloops)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cpuhotplug.h>

int __cpuhp_setup_state(enum cpuhp_state state,const char * name,bool invoke,int (* startup)(unsigned int cpu),int (* teardown)(unsigned int cpu),bool multi_instance)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/file.h>

unsigned long __fdget(unsigned int fd)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int __printk_ratelimit(const char * func)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/task.h>

void __put_task_struct(struct task_struct * tsk)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int __register_chrdev(unsigned int major,unsigned int baseminor,unsigned int count,const char * name,const struct file_operations * fops)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/srcu.h>

void __srcu_read_unlock(struct srcu_struct * ssp,int idx)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/interrupt.h>

void __tasklet_schedule(struct tasklet_struct * t)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm-generic/delay.h>

void __udelay(unsigned long usecs)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

void __unregister_chrdev(unsigned int major,unsigned int baseminor,unsigned int count,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmalloc.h>

void * __vmalloc(unsigned long size,gfp_t gfp_mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmalloc.h>

void * __vmalloc_node(unsigned long size,unsigned long align,gfp_t gfp_mask,int node,const void * caller)
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


#include <linux/kernel_stat.h>

void account_process_tick(struct task_struct * p,int user_tick)
{
	lx_emul_trace_and_stop(__func__);
}


extern void ack_bad_irq(unsigned int irq);
void ack_bad_irq(unsigned int irq)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/acpi.h>

int acpi_dev_gpio_irq_get_by(struct acpi_device * adev,const char * name,int index)
{
	lx_emul_trace_and_stop(__func__);
}


#include <acpi/acpi_bus.h>

bool acpi_dev_present(const char * hid,const char * uid,s64 hrv)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/acpi.h>

int acpi_device_modalias(struct device * dev,char * buf,int size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/acpi.h>

int acpi_device_uevent_modalias(struct device * dev,struct kobj_uevent_env * env)
{
	lx_emul_trace_and_stop(__func__);
}


#include <acpi/acpi_bus.h>

int acpi_dma_configure_id(struct device * dev,enum dev_dma_attr attr,const u32 * input_id)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/acpi.h>

bool acpi_driver_match_device(struct device * dev,const struct device_driver * drv)
{
	lx_emul_trace_and_stop(__func__);
}


#include <acpi/acpi_bus.h>

enum dev_dma_attr acpi_get_dma_attr(struct acpi_device * adev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/acpi.h>

const struct acpi_device_id * acpi_match_device(const struct acpi_device_id * ids,const struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/acpi.h>

int acpi_platform_notify(struct device * dev,enum kobject_action action)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/random.h>

int add_random_ready_callback(struct random_ready_callback * rdy)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

int add_uevent_var(struct kobj_uevent_env * env,const char * format,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

struct inode * alloc_anon_inode(struct super_block * s)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gfp.h>

void * alloc_pages_exact(size_t size,gfp_t gfp_mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/async.h>

async_cookie_t async_schedule_node(async_func_t func,void * data,int node)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/async.h>

async_cookie_t async_schedule_node_domain(async_func_t func,void * data,int node,struct async_domain * domain)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/async.h>

void async_synchronize_full(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/async.h>

void async_synchronize_full_domain(struct async_domain * domain)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

void bust_spinlocks(int yes)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/loadavg.h>

void calc_global_load(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcupdate.h>

void call_rcu(struct rcu_head * head,rcu_callback_t func)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/clocksource.h>

void clocksource_arch_init(struct clocksource * cs)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/console.h>

void console_flush_on_panic(enum con_flush_mode mode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int console_printk[] = {};


#include <linux/console.h>

void console_unblank(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern struct system_counterval_t convert_art_to_tsc(u64 art);
struct system_counterval_t convert_art_to_tsc(u64 art)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_qos.h>

void cpu_latency_qos_add_request(struct pm_qos_request * req,s32 value)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_qos.h>

void cpu_latency_qos_remove_request(struct pm_qos_request * req)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_qos.h>

bool cpu_latency_qos_request_active(struct pm_qos_request * req)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pm_qos.h>

void cpu_latency_qos_update_request(struct pm_qos_request * req,s32 new_value)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/debug_locks.h>

int debug_locks_off(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/clk.h>

struct clk * devm_clk_get(struct device * dev,const char * id)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

struct gpio_desc * __must_check devm_gpiod_get_optional(struct device * dev,const char * con_id,enum gpiod_flags flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/leds.h>

int devm_led_classdev_register_ext(struct device * parent,struct led_classdev * led_cdev,struct led_init_data * init_data)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

bool dma_can_mmap(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

int dma_mmap_attrs(struct device * dev,struct vm_area_struct * vma,void * cpu_addr,dma_addr_t dma_addr,size_t size,unsigned long attrs)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

int dma_supported(struct device * dev,u64 mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

asmlinkage __visible void dump_stack(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

void emergency_restart(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int fasync_helper(int fd,struct file * filp,int on,struct fasync_struct ** fapp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/capability.h>

bool file_ns_capable(const struct file * file,struct user_namespace * ns,int cap)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/file.h>

void fput(struct file * file)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gfp.h>

void free_pages_exact(void * virt,size_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/property.h>

struct fwnode_handle * fwnode_create_software_node(const struct property_entry * properties,const struct fwnode_handle * parent)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/property.h>

void fwnode_remove_software_node(struct fwnode_handle * fwnode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gcd.h>

unsigned long gcd(unsigned long a,unsigned long b)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

int get_option(char ** str,int * pint)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/random.h>

void get_random_bytes(void * buf,int nbytes)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/random.h>

int __must_check get_random_bytes_arch(void * buf,int nbytes)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/gpio/consumer.h>

void gpiod_set_value_cansleep(struct gpio_desc * desc,int value)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uuid.h>

const u8 guid_index[16] = {};


extern void hda_widget_sysfs_exit(struct hdac_device * codec);
void hda_widget_sysfs_exit(struct hdac_device * codec)
{
	lx_emul_trace_and_stop(__func__);
}


extern int hda_widget_sysfs_init(struct hdac_device * codec);
int hda_widget_sysfs_init(struct hdac_device * codec)
{
	lx_emul_trace_and_stop(__func__);
}


extern int hda_widget_sysfs_reinit(struct hdac_device * codec,hda_nid_t start_nid,int num_nodes);
int hda_widget_sysfs_reinit(struct hdac_device * codec,hda_nid_t start_nid,int num_nodes)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/hdmi.h>

int hdmi_audio_infoframe_init(struct hdmi_audio_infoframe * frame)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/hdmi.h>

ssize_t hdmi_audio_infoframe_pack(struct hdmi_audio_infoframe * frame,void * buffer,size_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/signal.h>

void ignore_signals(struct task_struct * t)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pseudo_fs.h>

struct pseudo_fs_context * init_pseudo(struct fs_context * fc,unsigned long magic)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/utsname.h>

struct user_namespace init_user_ns;


#include <linux/utsname.h>

struct uts_namespace init_uts_ns;


#include <linux/init.h>

bool initcall_debug;


#include <linux/input.h>

struct input_dev * input_allocate_device(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/input.h>

void input_event(struct input_dev * dev,unsigned int type,unsigned int code,int value)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/input.h>

void input_free_device(struct input_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/input.h>

int input_register_device(struct input_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/input.h>

void input_set_capability(struct input_dev * dev,unsigned int type,unsigned int code)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/input.h>

void input_unregister_device(struct input_dev * dev)
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


#include <asm-generic/iomap.h>

unsigned int ioread32(const void __iomem * addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm-generic/logic_io.h>

void __iomem * ioremap(resource_size_t phys_addr,unsigned long size)
{
	lx_emul_trace_and_stop(__func__);
}


extern bool iosf_mbi_available(void);
bool iosf_mbi_available(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern int iosf_mbi_read(u8 port,u8 opcode,u32 offset,u32 * mdr);
int iosf_mbi_read(u8 port,u8 opcode,u32 offset,u32 * mdr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm-generic/logic_io.h>

void iounmap(volatile void __iomem * addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm-generic/iomap.h>

void iowrite32(u32 val,void __iomem * addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq_work.h>

void irq_work_tick(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <acpi/acpi_bus.h>

bool is_acpi_device_node(const struct fwnode_handle * fwnode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/property.h>

bool is_software_node(const struct fwnode_handle * fwnode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

bool is_vmalloc_addr(const void * x)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

struct kobject *kernel_kobj;


#include <linux/kernfs.h>

void kernfs_get(struct kernfs_node * kn)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernfs.h>

void kernfs_put(struct kernfs_node * kn)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

void kill_anon_super(struct super_block * sb)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

void kill_fasync(struct fasync_struct ** fp,int sig,int band)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/slab.h>

void * kmalloc_order(size_t size,gfp_t flags,unsigned int order)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kmsg_dump.h>

void kmsg_dump(enum kmsg_dump_reason reason)
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

enum led_brightness ledtrig_audio_get(enum led_audio type)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/leds.h>

void ledtrig_audio_set(enum led_audio type,enum led_brightness state)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/delay.h>

unsigned long lpj_fine;


#include <linux/kernel.h>

unsigned long long memparse(const char * ptr,char ** retptr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq.h>

struct irq_chip no_irq_chip;


#include <linux/fs.h>

loff_t no_llseek(struct file * file,loff_t offset,int whence)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int nonseekable_open(struct inode * inode,struct file * filp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

loff_t noop_llseek(struct file * file,loff_t offset,int whence)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

enum reboot_mode panic_reboot_mode;


#include <linux/moduleparam.h>

const struct kernel_param_ops param_ops_bool;


#include <linux/moduleparam.h>

const struct kernel_param_ops param_ops_charp;


#include <linux/moduleparam.h>

const struct kernel_param_ops param_ops_int;


#include <linux/kernel.h>

bool parse_option_str(const char * str,const char * option)
{
	lx_emul_trace_and_stop(__func__);
}


extern bool pat_enabled(void);
bool pat_enabled(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern int pci_acpi_program_hp_params(struct pci_dev * dev);
int pci_acpi_program_hp_params(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pci_allocate_vc_save_buffers(struct pci_dev * dev);
void pci_allocate_vc_save_buffers(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_assign_irq(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_assign_unassigned_bridge_resources(struct pci_dev * bridge)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_assign_unassigned_bus_resources(struct pci_bus * bus)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_dev_assign_slot(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int pci_dev_specific_acs_enabled(struct pci_dev * dev,u16 acs_flags);
int pci_dev_specific_acs_enabled(struct pci_dev * dev,u16 acs_flags)
{
	lx_emul_trace_and_stop(__func__);
}


extern int pci_dev_specific_disable_acs_redir(struct pci_dev * dev);
int pci_dev_specific_disable_acs_redir(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int pci_dev_specific_enable_acs(struct pci_dev * dev);
int pci_dev_specific_enable_acs(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int pci_dev_specific_reset(struct pci_dev * dev,int probe);
int pci_dev_specific_reset(struct pci_dev * dev,int probe)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pci_disable_bridge_window(struct pci_dev * dev);
void pci_disable_bridge_window(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_enable_resources(struct pci_dev * dev,int mask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

struct pci_host_bridge * pci_find_host_bridge(struct pci_bus * bus)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_fixup_device(enum pci_fixup_pass pass,struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

unsigned int pci_flags;


extern struct device * pci_get_host_bridge_device(struct pci_dev * dev);
struct device * pci_get_host_bridge_device(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

struct irq_domain * pci_host_bridge_acpi_msi_domain(struct pci_bus * bus)
{
	lx_emul_trace_and_stop(__func__);
}


extern int pci_idt_bus_quirk(struct pci_bus * bus,int devfn,u32 * l,int timeout);
int pci_idt_bus_quirk(struct pci_bus * bus,int devfn,u32 * l,int timeout)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void __iomem * pci_map_rom(struct pci_dev * pdev,size_t * size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_mmap_resource_range(struct pci_dev * pdev,int bar,struct vm_area_struct * vma,enum pci_mmap_state mmap_state,int write_combine)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pci_msi_init(struct pci_dev * dev);
void pci_msi_init(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pci_msix_init(struct pci_dev * dev);
void pci_msix_init(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int pci_proc_attach_device(struct pci_dev * dev);
int pci_proc_attach_device(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pci_put_host_bridge_device(struct device * dev);
void pci_put_host_bridge_device(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void __init pci_realloc_get_opt(char * str);
void __init pci_realloc_get_opt(char * str)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pci_restore_vc_state(struct pci_dev * dev);
void pci_restore_vc_state(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern int pci_save_vc_state(struct pci_dev * dev);
int pci_save_vc_state(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_stop_and_remove_bus_device_locked(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_unmap_rom(struct pci_dev * pdev,void __iomem * rom)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pci_update_resource(struct pci_dev * dev,int resno)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pci_vpd_init(struct pci_dev * dev);
void pci_vpd_init(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pci_vpd_release(struct pci_dev * dev);
void pci_vpd_release(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


extern unsigned int pcibios_assign_all_busses(void);
unsigned int pcibios_assign_all_busses(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pcibios_bus_to_resource(struct pci_bus * bus,struct resource * res,struct pci_bus_region * region)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

void pcibios_resource_to_bus(struct pci_bus * bus,struct pci_bus_region * region,struct resource * res)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pcie_aspm_init_link_state(struct pci_dev * pdev);
void pcie_aspm_init_link_state(struct pci_dev * pdev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pcie_aspm_pm_state_change(struct pci_dev * pdev);
void pcie_aspm_pm_state_change(struct pci_dev * pdev)
{
	lx_emul_trace_and_stop(__func__);
}


extern void pcie_aspm_powersave_config_link(struct pci_dev * pdev);
void pcie_aspm_powersave_config_link(struct pci_dev * pdev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci_hotplug.h>

bool pciehp_is_native(struct pci_dev * bridge)
{
	lx_emul_trace_and_stop(__func__);
}


extern pgprot_t pgprot_writecombine(pgprot_t prot);
pgprot_t pgprot_writecombine(pgprot_t prot)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pid.h>

pid_t pid_vnr(struct pid * pid)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int printk_deferred(const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

void printk_safe_flush_on_panic(void)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/proc_fs.h>

struct proc_dir_entry * proc_create_data(const char * name,umode_t mode,struct proc_dir_entry * parent,const struct proc_ops * proc_ops,void * data)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/proc_fs.h>

struct proc_dir_entry * proc_create_seq_private(const char * name,umode_t mode,struct proc_dir_entry * parent,const struct seq_operations * ops,unsigned int state_size,void * data)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/proc_fs.h>

struct proc_dir_entry * proc_mkdir(const char * name,struct proc_dir_entry * parent)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/proc_fs.h>

struct proc_dir_entry * proc_mkdir_mode(const char * name,umode_t mode,struct proc_dir_entry * parent)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/proc_fs.h>

void proc_remove(struct proc_dir_entry * de)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/proc_fs.h>

void proc_set_size(struct proc_dir_entry * de,loff_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/proc_fs.h>

struct proc_dir_entry * proc_symlink(const char * name,struct proc_dir_entry * parent,const char * dest)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pid.h>

void put_pid(struct pid * pid)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcupdate.h>

void rcu_sched_clock_irq(int user)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

enum reboot_mode reboot_mode;


#include <linux/refcount.h>

bool refcount_dec_not_one(refcount_t * r)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/refcount.h>

void refcount_warn_saturate(refcount_t * r,enum refcount_saturation_type t)
{
	lx_emul_trace_and_stop(__func__);
}


extern void register_handler_proc(unsigned int irq,struct irqaction * action);
void register_handler_proc(unsigned int irq,struct irqaction * action)
{
	lx_emul_trace_and_stop(__func__);
}


extern void register_irq_proc(unsigned int irq,struct irq_desc * desc);
void register_irq_proc(unsigned int irq,struct irq_desc * desc)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/firmware.h>

void release_firmware(const struct firmware * fw)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

int remap_pfn_range(struct vm_area_struct * vma,unsigned long addr,unsigned long pfn,unsigned long size,pgprot_t prot)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmalloc.h>

int remap_vmalloc_range(struct vm_area_struct * vma,void * addr,unsigned long pgoff)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/firmware.h>

int request_firmware(const struct firmware ** firmware_p,const char * name,struct device * device)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/firmware.h>

int request_firmware_nowait(struct module * module,bool uevent,const char * name,struct device * device,gfp_t gfp,void * context,void (* cont)(const struct firmware * fw,void * context))
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched.h>

void sched_set_fifo(struct task_struct * p)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

loff_t seq_lseek(struct file * file,loff_t offset,int whence)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

void seq_printf(struct seq_file * m,const char * f,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

ssize_t seq_read(struct file * file,char __user * buf,size_t size,loff_t * ppos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

void seq_vprintf(struct seq_file * m,const char * f,va_list args)
{
	lx_emul_trace_and_stop(__func__);
}


extern int set_memory_wb(unsigned long addr,int numpages);
int set_memory_wb(unsigned long addr,int numpages)
{
	lx_emul_trace_and_stop(__func__);
}


extern int set_memory_wc(unsigned long addr,int numpages);
int set_memory_wc(unsigned long addr,int numpages)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/mm.h>

void show_mem(unsigned int filter,nodemask_t * nodemask)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/debug.h>

void show_state_filter(unsigned int state_filter)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

int simple_pin_fs(struct file_system_type * type,struct vfsmount ** mount,int * count)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/fs.h>

void simple_release_fs(struct vfsmount ** mount,int * count)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

int single_open(struct file * file,int (* show)(struct seq_file *,void *),void * data)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

int single_open_size(struct file * file,int (* show)(struct seq_file *,void *),void * data,size_t size)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

int single_release(struct inode * inode,struct file * file)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/siphash.h>

u64 siphash_1u64(const u64 first,const siphash_key_t * key)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/smp.h>

int smp_call_function_single(int cpu,void (* func)(void * info),void * info,int wait)
{
	lx_emul_trace_and_stop(__func__);
}


extern void snd_ac97_bus_proc_done(struct snd_ac97_bus * bus);
void snd_ac97_bus_proc_done(struct snd_ac97_bus * bus)
{
	lx_emul_trace_and_stop(__func__);
}


extern void snd_ac97_bus_proc_init(struct snd_ac97_bus * bus);
void snd_ac97_bus_proc_init(struct snd_ac97_bus * bus)
{
	lx_emul_trace_and_stop(__func__);
}


extern void snd_ac97_proc_done(struct snd_ac97 * ac97);
void snd_ac97_proc_done(struct snd_ac97 * ac97)
{
	lx_emul_trace_and_stop(__func__);
}


extern void snd_ac97_proc_init(struct snd_ac97 * ac97);
void snd_ac97_proc_init(struct snd_ac97 * ac97)
{
	lx_emul_trace_and_stop(__func__);
}


extern int snd_hda_codec_proc_new(struct hda_codec * codec);
int snd_hda_codec_proc_new(struct hda_codec * codec)
{
	lx_emul_trace_and_stop(__func__);
}


extern int snd_hda_get_bool_hint(struct hda_codec * codec,const char * key);
int snd_hda_get_bool_hint(struct hda_codec * codec,const char * key)
{
	lx_emul_trace_and_stop(__func__);
}


extern int snd_hda_get_int_hint(struct hda_codec * codec,const char * key,int * valp);
int snd_hda_get_int_hint(struct hda_codec * codec,const char * key,int * valp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <sound/hda_codec.h>

int snd_hda_load_patch(struct hda_bus * bus,size_t fw_size,const void * fw_buf)
{
	lx_emul_trace_and_stop(__func__);
}


extern void snd_hda_sysfs_clear(struct hda_codec * codec);
void snd_hda_sysfs_clear(struct hda_codec * codec)
{
	lx_emul_trace_and_stop(__func__);
}


extern void snd_hda_sysfs_init(struct hda_codec * codec);
void snd_hda_sysfs_init(struct hda_codec * codec)
{
	lx_emul_trace_and_stop(__func__);
}


#include <sound/soc-acpi-intel-match.h>

struct snd_soc_acpi_mach snd_soc_acpi_intel_adl_machines[] = {};


#include <sound/soc-acpi-intel-match.h>

struct snd_soc_acpi_mach snd_soc_acpi_intel_adl_sdw_machines[] = {};


#include <sound/soc-acpi-intel-match.h>

struct snd_soc_acpi_mach snd_soc_acpi_intel_baytrail_machines[] = {};


#include <sound/soc-acpi-intel-match.h>

struct snd_soc_acpi_mach snd_soc_acpi_intel_cherrytrail_machines[] = {};


#include <sound/soc-acpi-intel-match.h>

struct snd_soc_acpi_mach snd_soc_acpi_intel_ehl_machines[] = {};


#include <linux/property.h>

int software_node_notify(struct device * dev,unsigned long action)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/srcutiny.h>

void srcu_drive_gp(struct work_struct * wp)
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


#include <linux/string_helpers.h>

int string_escape_mem(const char * src,size_t isz,char * dst,size_t osz,unsigned int flags,const char * only)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int suppress_printk;


#include <linux/srcutiny.h>

void synchronize_srcu(struct srcu_struct * ssp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_bin_file(struct kobject * kobj,const struct bin_attribute * attr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_dir_ns(struct kobject * kobj,const void * ns)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_file_ns(struct kobject * kobj,const struct attribute * attr,const void * ns)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_group(struct kobject * kobj,const struct attribute_group * grp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_groups(struct kobject * kobj,const struct attribute_group ** groups)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

int sysfs_create_link(struct kobject * kobj,struct kobject * target,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_delete_link(struct kobject * kobj,struct kobject * targ,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

int sysfs_emit(char * buf,const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

int sysfs_emit_at(char * buf,int at,const char * fmt,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_bin_file(struct kobject * kobj,const struct bin_attribute * attr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_dir(struct kobject * kobj)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_file_ns(struct kobject * kobj,const struct attribute * attr,const void * ns)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

bool sysfs_remove_file_self(struct kobject * kobj,const struct attribute * attr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_group(struct kobject * kobj,const struct attribute_group * grp)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_groups(struct kobject * kobj,const struct attribute_group ** groups)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sysfs.h>

void sysfs_remove_link(struct kobject * kobj,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/task_work.h>

int task_work_add(struct task_struct * task,struct callback_head * work,enum task_work_notify_mode notify)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/task_work.h>

struct callback_head * task_work_cancel(struct task_struct * task,task_work_func_t func)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vt_kern.h>

void unblank_screen(void)
{
	lx_emul_trace_and_stop(__func__);
}


extern void unregister_handler_proc(unsigned int irq,struct irqaction * action);
void unregister_handler_proc(unsigned int irq,struct irqaction * action)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/timekeeper_internal.h>

void update_vsyscall(struct timekeeper * tk)
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


#include <linux/mm.h>

struct page * vmalloc_to_page(const void * vmalloc_addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmalloc.h>

void * vmap(struct page ** pages,unsigned int count,unsigned long flags,pgprot_t prot)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/vmalloc.h>

void vunmap(const void * addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/wake_q.h>

void wake_q_add_safe(struct wake_q_head * head,struct task_struct * task)
{
	lx_emul_trace_and_stop(__func__);
}


extern const struct x86_cpu_id * x86_match_cpu(const struct x86_cpu_id * match);
const struct x86_cpu_id * x86_match_cpu(const struct x86_cpu_id * match)
{
	lx_emul_trace_and_stop(__func__);
}

