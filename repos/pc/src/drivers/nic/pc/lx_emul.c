/*
 * \brief  Linux emulation environment specific to this driver
 * \author Christian Helmuth
 * \date   2023-05-22
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

/* TODO move dummy functions into dummies.c */

#include <lx_emul.h>


unsigned long __FIXADDR_TOP = 0xfffff000;

#include <linux/random.h>
#include <lx_emul/random.h>

u32 __get_random_u32_below(u32 ceil)
{
	/**
	 * Returns a random number from the half-open interval [0, ceil)
	 * with uniform distribution.
	 *
	 * The idea here is to split [0, 2^32) into #ceil bins. By dividing a random
	 * number from the 32-bit interval, we can determine into which bin the number
	 * fell.
	 */

	/* determine divisor to determine bin number by dividing 2^32 by ceil */
	u32 div = 0x100000000ULL / ceil;

	/**
	 * In case the above division has a remainder, we will end up with an
	 * additional (but smaller) bin at the end of the 32-bit interval. We'll
	 * discard the result if the number fell into this bin and repeat.
	 */
	u32 result = ceil;
	while (result >= ceil)
		result = lx_emul_random_gen_u32() / div;

	return result;
}


#include <linux/uaccess.h>

#ifndef INLINE_COPY_FROM_USER
unsigned long _copy_from_user(void * to, const void __user * from, unsigned long n)
{
	memcpy(to, from, n);
	return 0;
}
#endif

unsigned long _copy_to_user(void __user * to,const void * from,unsigned long n)
{
	memcpy(to, from, n);
	return 0;
}


#include <linux/gfp.h>

unsigned long get_zeroed_page(gfp_t gfp_mask)
{
	return (unsigned long)__alloc_pages(GFP_KERNEL, 0, 0, NULL)->virtual;
}

void * page_frag_alloc_align(struct page_frag_cache *nc,
                             unsigned int fragsz, gfp_t gfp_mask,
                             unsigned int align_mask)
{
	struct page *page;

	if (fragsz > PAGE_SIZE) {
		printk("no support for fragments larger than PAGE_SIZE\n");
		lx_emul_trace_and_stop(__func__);
	}

	page = __alloc_pages(gfp_mask, 0, 0, NULL);

	if (!page)
		return NULL;

	return page->virtual;
}

void page_frag_free(void * addr)
{
	struct page *page = lx_emul_virt_to_pages(addr, 1ul);
	if (!page) {
		printk("BUG %s: page for addr: %p not found\n", __func__, addr);
		lx_emul_backtrace();
	}

	__free_pages(page, 0ul);
}


#include <linux/slab.h>

struct kmem_cache * kmem_cache_create_usercopy(const char * name,
                                               unsigned int size,
                                               unsigned int align,
                                               slab_flags_t flags,
                                               unsigned int useroffset,
                                               unsigned int usersize,
                                               void (* ctor)(void *))
{
	return kmem_cache_create(name, size, align, flags, ctor);
}

int kmem_cache_alloc_bulk(struct kmem_cache * s,gfp_t flags, size_t nr,void ** p)
{
	size_t i;
	for (i = 0; i < nr; i++)
		p[i] = kmem_cache_alloc(s, flags);

	return nr;
}


#include <asm/hardirq.h>

void ack_bad_irq(unsigned int irq)
{
	printk(KERN_CRIT "unexpected IRQ trap at vector %02x\n", irq);
}


#include <linux/pci.h>

void __iomem * pci_ioremap_bar(struct pci_dev * pdev, int bar)
{
	struct resource *res = &pdev->resource[bar];
	return ioremap(res->start, resource_size(res));
}

int pci_read_config_word(const struct pci_dev *dev, int where, u16 *val)
{
	switch (where) {
	case PCI_COMMAND:
		*val = 0x7;
		return 0;

	/*
	 * drivers/net/ethernet/intel/e1000e/ich8lan.c e1000_platform_pm_pch_lpt
	 */
	case 0xa8:
	case 0xaa:
		*val = 0;
		return 0;
	/*
	 * drivers/net/ethernet/intel/e1000e/netdev.c e1000_flush_desc_rings
	 *
	 * In i219, the descriptor rings must be emptied before resetting the HW or
	 * before changing the device state to D3 during runtime (runtime PM).
	 *
	 * Failure to do this will cause the HW to enter a unit hang state which
	 * can only be released by PCI reset on the device
	 */
	case 0xe4:
		/* XXX report no need to flush */
		*val = 0;
		return 0;
	};

	printk("%s: unexpected read at %x\n", __func__, where);
	return -1;
}

int pcie_capability_read_word(struct pci_dev *dev, int pos, u16 *val)
{
	printk("%s: unexpected read at %x\n", __func__, pos);
	return -1;
}
