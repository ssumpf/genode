/*
 * \brief  Dummy definitions of Linux Kernel functions
 * \author Automatically generated file - do no edit
 * \date   2022-11-03
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


#include <linux/file.h>

unsigned long __fdget(unsigned int fd)
{
	lx_emul_trace_and_stop(__func__);
}


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

unsigned int __kfifo_out(struct __kfifo * fifo,void * buf,unsigned int len)
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


#include <linux/srcu.h>

void __srcu_read_unlock(struct srcu_struct * ssp,int idx)
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


extern void ack_bad_irq(unsigned int irq);
void ack_bad_irq(unsigned int irq)
{
	lx_emul_trace_and_stop(__func__);
}


extern acpi_status acpi_get_handle(acpi_handle parent,acpi_string pathname,acpi_handle * ret_handle);
acpi_status acpi_get_handle(acpi_handle parent,acpi_string pathname,acpi_handle * ret_handle)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/acpi.h>

int acpi_get_override_irq(u32 gsi,int * is_level,int * active_low)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/acpi.h>

int acpi_register_gsi(struct device * dev,u32 gsi,int trigger,int polarity)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

int add_uevent_var(struct kobj_uevent_env * env,const char * format,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/anon_inodes.h>

struct file * anon_inode_getfile(const char * name,const struct file_operations * fops,void * priv,int flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kernel.h>

void bust_spinlocks(int yes)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/cdev.h>

int cdev_device_add(struct cdev * cdev,struct device * dev)
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

void cpu_latency_qos_remove_request(struct pm_qos_request * req)
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


#include <linux/leds.h>

int devm_led_classdev_register_ext(struct device * parent,struct led_classdev * led_cdev,struct led_init_data * init_data)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pinctrl/consumer.h>

struct pinctrl * devm_pinctrl_get(struct device * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/dma-mapping.h>

int dma_mmap_attrs(struct device * dev,struct vm_area_struct * vma,void * cpu_addr,dma_addr_t dma_addr,size_t size,unsigned long attrs)
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


#include <linux/file.h>

void fd_install(unsigned int fd,struct file * file)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/capability.h>

bool file_ns_capable(const struct file * file,struct user_namespace * ns,int cap)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

struct kobject *firmware_kobj;


#include <linux/file.h>

void fput(struct file * file)
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


#include <linux/kernel.h>

int get_option(char ** str,int * pint)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/file.h>

int get_unused_fd_flags(unsigned flags)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/uuid.h>

const u8 guid_index[16] = {};


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


#include <linux/pseudo_fs.h>

struct pseudo_fs_context * init_pseudo(struct fs_context * fc,unsigned long magic)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/init.h>

bool initcall_debug;


#include <linux/input.h>

void input_ff_destroy(struct input_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/input/mt.h>

void input_mt_destroy_slots(struct input_dev * dev)
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


#include <linux/property.h>

bool is_software_node(const struct fwnode_handle * fwnode)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/kobject.h>

struct kobject *kernel_kobj;


#include <linux/fs.h>

void kill_anon_super(struct super_block * sb)
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


#include <linux/leds.h>

enum led_brightness ledtrig_audio_get(enum led_audio type)
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

loff_t noop_llseek(struct file * file,loff_t offset,int whence)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/irq.h>

void note_interrupt(struct irq_desc * desc,irqreturn_t action_ret)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/reboot.h>

enum reboot_mode panic_reboot_mode;


#include <linux/pci.h>

void pci_restore_state(struct pci_dev * dev)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pci.h>

int pci_save_state(struct pci_dev * dev)
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


#include <linux/pinctrl/consumer.h>

bool pinctrl_gpio_can_use_line(unsigned gpio)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pinctrl/consumer.h>

struct pinctrl_state * pinctrl_lookup_state(struct pinctrl * p,const char * name)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/pinctrl/consumer.h>

int pinctrl_select_state(struct pinctrl * p,struct pinctrl_state * state)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/prandom.h>

u32 prandom_u32(void)
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


#include <linux/file.h>

void put_unused_fd(unsigned int fd)
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


#include <linux/proc_fs.h>

void remove_proc_entry(const char * name,struct proc_dir_entry * parent)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

struct list_head * seq_list_next(void * v,struct list_head * head,loff_t * ppos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

struct list_head * seq_list_start(struct list_head * head,loff_t pos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

loff_t seq_lseek(struct file * file,loff_t offset,int whence)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

int seq_open(struct file * file,const struct seq_operations * op)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

void seq_printf(struct seq_file * m,const char * f,...)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

void seq_putc(struct seq_file * m,char c)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

void seq_puts(struct seq_file * m,const char * s)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

ssize_t seq_read(struct file * file,char __user * buf,size_t size,loff_t * ppos)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/seq_file.h>

int seq_release(struct inode * inode,struct file * file)
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


#include <linux/siphash.h>

u64 siphash_1u64(const u64 first,const siphash_key_t * key)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/smp.h>

int smp_call_function_single(int cpu,smp_call_func_t func,void * info,int wait)
{
	lx_emul_trace_and_stop(__func__);
}


extern void snd_hda_sysfs_clear(struct hda_codec * codec);
void snd_hda_sysfs_clear(struct hda_codec * codec)
{
	lx_emul_trace_and_stop(__func__);
}


#include <sound/soc-acpi-intel-match.h>

struct snd_soc_acpi_mach snd_soc_acpi_intel_adl_machines[] = {};


#include <sound/soc-acpi-intel-match.h>

struct snd_soc_acpi_mach snd_soc_acpi_intel_adl_sdw_machines[] = {};


#include <sound/soc-acpi-intel-match.h>

struct snd_soc_acpi_mach snd_soc_acpi_intel_ehl_machines[] = {};


#include <linux/jump_label.h>

bool static_key_initialized;


#include <linux/string_helpers.h>

int string_escape_mem(const char * src,size_t isz,char * dst,size_t osz,unsigned int flags,const char * only)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/printk.h>

int suppress_printk;


#include <linux/rcupdate.h>

void synchronize_rcu(void)
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


#include <linux/uuid.h>

const u8 uuid_index[16] = {};


#include <linux/mm.h>

struct page * vmalloc_to_page(const void * vmalloc_addr)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/sched/wake_q.h>

void wake_q_add_safe(struct wake_q_head * head,struct task_struct * task)
{
	lx_emul_trace_and_stop(__func__);
}

