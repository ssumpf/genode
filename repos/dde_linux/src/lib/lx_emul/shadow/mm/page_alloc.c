/*
 * \brief  Replaces mm/page_alloc.c
 * \author Stefan Kalkowski
 * \author Christian Helmuth
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
		struct page *page = lx_emul_virt_to_page(ptr);
		int i;

		for (i = 0; i < nr_pages; i++) {

			if (page_array[i])
				lx_emul_trace_and_stop("__alloc_pages_bulk: page_array entry not null");

			page_array[i] = page + i;
		}
	}

	return nr_pages;
}

static void lx_free_pages(struct page *page, bool force)
{
	void * const virt_addr = page_address(page);

	if (force)
		set_page_count(page, 0);
	else if (!put_page_testzero(page))
		return;

	lx_emul_mem_free(virt_addr);
}


void __free_pages(struct page * page, unsigned int order)
{
	lx_free_pages(page, false);
}


void free_pages(unsigned long addr,unsigned int order)
{
	if (addr != 0ul)
		__free_pages(virt_to_page((void *)addr), order);
}


static struct page * lx_alloc_pages(unsigned const nr_pages)
{
	void const  *ptr  = lx_emul_mem_alloc_aligned(PAGE_SIZE*nr_pages, PAGE_SIZE);
	struct page *page = lx_emul_virt_to_page(ptr);

	init_page_count(page);

	return page;
}


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


/*
 * In earlier kernel versions, '__alloc_pages' was an inline function.
 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,13,0)
struct page * __alloc_pages_nodemask(gfp_t gfp, unsigned int order, int preferred_nid,
                                     nodemask_t * nodemask)
#else
struct page * __alloc_pages(gfp_t gfp, unsigned int order, int preferred_nid,
                            nodemask_t * nodemask)
#endif
{
	struct page *page  = lx_alloc_pages(1u << order);

	prep_new_page(page, order, gfp);

	return page;
}


unsigned long __get_free_pages(gfp_t gfp_mask, unsigned int order)
{
	struct page *page = lx_alloc_pages(1u << order);

	if (!page)
		return 0;

	return (unsigned long)page_address(page);
}


/*
 * Exact page allocation
 *
 * This implementation does only support alloc-free pairs that use the same
 * size and does not set the page_count of pages beyond the head page. It is
 * currently not possible to allocate individual but contiguous pages, which is
 * required to satisfy Linux semantics.
 */

void free_pages_exact(void *virt_addr, size_t size)
{
	struct page *page = lx_emul_virt_to_page(virt_addr);

	if (!page)
		return;

	lx_free_pages(page, false);
}


void *alloc_pages_exact(size_t size, gfp_t gfp_mask)
{
	size_t const nr_pages = DIV_ROUND_UP(size, PAGE_SIZE);
	struct page *page = lx_alloc_pages(nr_pages);

	if (!page)
		return NULL;

	return page_address(page);
}


#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
void __folio_put(struct folio * folio)
{
	struct page *page = folio_page(folio, 0);

	/* should only be called if refcount is 0 */
	if (page_count(page) != 0)
		printk("%s: page refocunt not 0 for page=%px\n", __func__, page);

	lx_free_pages(&folio->page, true);
}
#endif
