#include <lx_emul.h>

#include <asm/processor.h>


struct static_key_false init_on_alloc;

unsigned long sysctl_net_busy_read;

DEFINE_STATIC_KEY_FALSE(force_irqthreads_key);
DEFINE_STATIC_KEY_FALSE(bpf_stats_enabled_key);


#include <linux/percpu-defs.h>

DEFINE_PER_CPU_READ_MOSTLY(cpumask_var_t, cpu_sibling_map);
EXPORT_PER_CPU_SYMBOL(cpu_sibling_map);


#include <net/ipv6_stubs.h>

const struct ipv6_stub *ipv6_stub = NULL;


#include <asm/uaccess.h>

long strncpy_from_user(char * dst,const char __user * src,long count)
{
	lx_emul_trace_and_stop(__func__);
}


#include <asm/uaccess.h>

long strnlen_user(const char __user * str,long count)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/random.h>

u8 get_random_u8(void)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


u16 get_random_u16(void)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


#include <linux/device.h>

void *__devres_alloc_node(dr_release_t release, size_t size, gfp_t gfp,
                          int nid, const char *name)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


void devres_free(void *res)
{
	lx_emul_trace_and_stop(__func__);
}


void devres_add(struct device *dev, void *res)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/rcutree.h>

void synchronize_rcu_expedited(void)
{
	lx_emul_trace(__func__);
}


#include <linux/kernel.h>

char *get_options(const char *str, int nints, int *ints)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


#include <linux/fs.h>

char *file_path(struct file *, char *, int)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


#include <asm/page.h>

void copy_page(void *to, void *from)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/filter.h>

void bpf_jit_compile(struct bpf_prog *prog)
{
	lx_emul_trace_and_stop(__func__);
}


#include <linux/bpf.h>

u64 bpf_get_raw_cpu_id(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


u64 bpf_user_rnd_u32(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


u64 bpf_event_output(struct bpf_map *map, u64 flags, void *meta, u64 meta_size,
                     void *ctx, u64 ctx_size, bpf_ctx_copy_t ctx_copy)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


/* kernel/sched/cpudeadline.h */
struct cpudl;
int  cpudl_init(struct cpudl *cp)
{
	lx_emul_trace_and_stop(__func__);
	return -1;
}


void cpudl_cleanup(struct cpudl *cp)
{
	lx_emul_trace_and_stop(__func__);
}


void dl_clear_root_domain(struct root_domain *rd)
{
	lx_emul_trace_and_stop(__func__);
}


/* kernel/sched/sched.h */
bool sched_smp_initialized = true;

struct dl_bw;
void init_dl_bw(struct dl_bw *dl_b)
{
	lx_emul_trace_and_stop(__func__);
}


struct irq_work;
void rto_push_irq_work_func(struct irq_work *work)
{
	lx_emul_trace_and_stop(__func__);
}


/* include/linux/sched/topology.h */
int arch_asym_cpu_priority(int cpu)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}
