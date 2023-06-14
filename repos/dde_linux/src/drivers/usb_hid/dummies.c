#include <lx_emul.h>

#include <linux/interrupt.h>

DEFINE_STATIC_KEY_FALSE(force_irqthreads_key);

#include <linux/uaccess.h>

unsigned long __must_check clear_user(void __user *mem, unsigned long len)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


#include <linux/random.h>

u32 __get_random_u32_below(u32 ceil)
{
	lx_emul_trace_and_stop(__func__);
	return 0;
}


#include <linux/context_tracking_irq.h>

noinstr void ct_irq_enter(void)
{
	lx_emul_trace(__func__);
}


#include <linux/context_tracking_irq.h>

noinstr void ct_irq_exit(void)
{
	lx_emul_trace(__func__);
}

