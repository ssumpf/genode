/*
 * \brief  Replaces mm/slub.c
 * \author Stefan Kalkowski
 * \date   2021-03-16
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <../mm/slab.h>
#include <../mm/internal.h>
#include <lx_emul/alloc.h>
#include <lx_emul/debug.h>

void * krealloc(const void * p,size_t new_size,gfp_t flags)
{
	if (!p)
		return kmalloc(new_size, flags);

	if (!new_size) {
		kfree(p);
		return NULL;

	} else {

		unsigned long const old_size = ksize(p);
		void *ret;

		if (new_size <= old_size)
			return (void*) p;

		ret = kmalloc(new_size, flags);
		memcpy(ret, p, old_size);
		return ret;
	}
}


size_t ksize(const void * objp)
{
	if (objp == NULL)
		return 0;

	return __ksize(objp);
}


/*
 * We can use our __kmalloc() implementation here as it supports large
 * allocations well.
 */
void * kmalloc_order(size_t size, gfp_t flags, unsigned int order)
{
	return __kmalloc(size, flags);
}


size_t kmalloc_size_roundup(size_t size) { return size; }


#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,1,0) || defined(CONFIG_NUMA)
void * __kmalloc_node(size_t size, gfp_t flags, int node)
{
	return __kmalloc(size, flags);
}
#endif


#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,1,0)
void * kmalloc_large(size_t size,gfp_t flags)
{
	return __kmalloc(size, flags);
}
#endif


#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,0,0)
void *kmalloc_trace(struct kmem_cache *s, gfp_t gfpflags, size_t size)
{
	return __kmalloc(size, gfpflags);
}


void *kmalloc_node_trace(struct kmem_cache *s, gfp_t gfpflags,
                         int node, size_t size)
{
	return __kmalloc(size, gfpflags);
}
#endif
