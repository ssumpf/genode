/*
 * \brief  Replaces mm/page_alloc.c
 * \author Stefan Kalkowski
 * \date   2021-06-03
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/version.h>
#include <lx_emul/alloc.h>
#include <lx_emul/debug.h>
#include <lx_emul/page_virt.h>

unsigned long __alloc_pages_bulk(gfp_t gfp,int preferred_nid,
                                 nodemask_t * nodemask, int nr_pages,
                                 struct list_head * page_list, struct page ** page_array)
{
	if (page_list)
		lx_emul_trace_and_stop("__alloc_pages_bulk unsupported argument");

	{
		void const  *ptr  = lx_emul_mem_alloc_aligned(PAGE_SIZE*nr_pages, PAGE_SIZE);
		struct page *page = lx_emul_virt_to_pages(ptr, nr_pages);
		int i;

		for (i = 0; i < nr_pages; i++) {

			if (page_array[i])
				lx_emul_trace_and_stop("__alloc_pages_bulk: page_array entry not null");

			page_array[i] = page + i;
		}
	}

	return nr_pages;
}

static void lx_free_pages(struct page *page, unsigned const num_pages)
{
	unsigned i;
	void *   const virt_addr = page->virtual;

	if (atomic_read(&page->_refcount) && !atomic_dec_and_test(&page->_refcount))
		return;

	for (i = 0; i < num_pages; i++)
		lx_emul_disassociate_page_from_virt_addr(page[i].virtual);

	lx_emul_mem_free(virt_addr);
	lx_emul_mem_free(page);
}


void __free_pages(struct page * page, unsigned int order)
{
	lx_free_pages(page, (1u << order));
}


void free_pages_exact(void *virt_addr, size_t size)
{
	lx_free_pages(virt_to_page(virt_addr), PAGE_ALIGN(size) / PAGE_SIZE);
}


static struct page * lx_alloc_pages(unsigned const nr_pages)
{
	void const  *ptr  = lx_emul_mem_alloc_aligned(PAGE_SIZE*nr_pages, PAGE_SIZE);
	struct page *page = lx_emul_virt_to_pages(ptr, nr_pages);

	atomic_set(&page->_refcount, 1);

	return page;
}


/*
 * In earlier kernel versions, '__alloc_pages' was an inline function.
 */
#if LINUX_VERSION_CODE > KERNEL_VERSION(5,12,0)

/*
 * This is needed to support compound/folio pages that are allocated useing
 * __GFP_COMP
 */
static void prep_compound_head(struct page *page, unsigned int order)
{
	set_compound_page_dtor(page, COMPOUND_PAGE_DTOR);
	set_compound_order(page, order);
}


static void prep_compound_tail(struct page *head, int tail_idx)
{
	struct page *p = head + tail_idx;

	p->mapping = TAIL_MAPPING;
	set_compound_head(p, head);
	set_page_private(p, 0);
}


static void prep_compound_page(struct page *page, unsigned int order)
{
	int i;
	int nr_pages = 1 << order;

	__SetPageHead(page);
	for (i = 1; i < nr_pages; i++)
		prep_compound_tail(page, i);

	prep_compound_head(page, order);
}


static void prep_new_page(struct page *page, unsigned int order, gfp_t gfp_flags)
{
	if (order && (gfp_flags & __GFP_COMP))
		prep_compound_page(page, order);
}


struct page * __alloc_pages(gfp_t gfp, unsigned int order, int preferred_nid,
                            nodemask_t * nodemask)
{
	struct page *page  = lx_alloc_pages(1u << order);

	prep_new_page(page, order, gfp);

	return page;
}
#endif


void *alloc_pages_exact(size_t size, gfp_t gfp_mask)
{
	return lx_alloc_pages(PAGE_ALIGN(size) / PAGE_SIZE)->virtual;
}


void free_pages(unsigned long addr,unsigned int order)
{
	if (addr != 0ul)
		__free_pages(virt_to_page((void *)addr), order);
}


unsigned long __get_free_pages(gfp_t gfp_mask, unsigned int order)
{
	struct page *page = lx_alloc_pages(1u << order);

	if (!page)
		return 0;

	return (unsigned long)page_address(page);
}
