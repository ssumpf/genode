/**
 * \brief  Linux emulation code
 * \author Sebastian Sumpf
 * \author Emery Hemingway
 * \author Christian Helmuth
 * \date   2013-08-28
 */

/*
 * Copyright (C) 2013-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

/* Genode includes */
#include <base/allocator_avl.h>
#include <base/object_pool.h>
#include <base/sleep.h>
#include <base/snprintf.h>
#include <dataspace/client.h>
#include <region_map/client.h>
#include <timer_session/connection.h>
#include <trace/timestamp.h>

/* local includes */
#include <lx_emul.h>
#include <lx.h>


/* Lx_kit */
#include <lx_kit/env.h>

/*********************************
 ** Lx::Backend_alloc interface **
 *********************************/

#include <lx_kit/backend_alloc.h>

static Lx_kit::Env *lx_env;

void Lx::lxcc_emul_init(Lx_kit::Env &env)
{
	lx_env = &env;
}

struct Memory_object_base : Genode::Object_pool<Memory_object_base>::Entry
{
	Memory_object_base(Genode::Ram_dataspace_capability cap)
	: Genode::Object_pool<Memory_object_base>::Entry(cap) {}

	void free() { lx_env->ram().free(ram_cap()); }

	Genode::Ram_dataspace_capability ram_cap()
	{
		using namespace Genode;
		return reinterpret_cap_cast<Ram_dataspace>(cap());
	}
};


static Genode::Object_pool<Memory_object_base> memory_pool;


Genode::Ram_dataspace_capability
Lx::backend_alloc(Genode::addr_t size, Genode::Cache_attribute cached)
{
	using namespace Genode;

	Genode::Ram_dataspace_capability cap = lx_env->ram().alloc(size);
	Memory_object_base *o = new (lx_env->heap()) Memory_object_base(cap);

	memory_pool.insert(o);
	return cap;
}


void Lx::backend_free(Genode::Ram_dataspace_capability cap)
{
	using namespace Genode;

	Memory_object_base *object;
	memory_pool.apply(cap, [&] (Memory_object_base *o) {
		if (!o) return;

		o->free();
		memory_pool.remove(o);

		object = o; /* save for destroy */
	});
	destroy(lx_env->heap(), object);
}


/*************************************
 ** Memory allocation, linux/slab.h **
 *************************************/

#include <lx_emul/impl/slab.h>


void *alloc_large_system_hash(const char *tablename,
	                            unsigned long bucketsize,
	                            unsigned long numentries,
	                            int scale,
	                            int flags,
	                            unsigned int *_hash_shift,
	                            unsigned int *_hash_mask,
	                            unsigned long low_limit,
	                            unsigned long high_limit)
{
	unsigned long elements = numentries ? numentries : high_limit;
	unsigned long nlog2 = ilog2(elements);
	nlog2 <<= (1 << nlog2) < elements ? 1 : 0;

	void *table;
	lx_env->heap().alloc(elements * bucketsize, &table);

	if (_hash_mask)
		*_hash_mask = (1 << nlog2) - 1;
	if (_hash_shift)
		*_hash_shift = nlog2;

	return table;
}


void *kmalloc_array(size_t n, size_t size, gfp_t flags)
{
	if (size != 0 && n > SIZE_MAX / size) return NULL;
	return kmalloc(n * size, flags);
}


/********************
 ** linux/slab.h   **
 ********************/

void *kmem_cache_alloc_node(struct kmem_cache *cache, gfp_t flags, int node)
{
	return (void*)cache->alloc();
}

void *kmem_cache_zalloc(struct kmem_cache *cache, gfp_t flags)
{
	void *addr = (void*)cache->alloc();
	if (addr) { memset(addr, 0, cache->size()); }

	return addr;
}


/*********************
 ** linux/vmalloc.h **
 *********************/

void *vmalloc(unsigned long size)
{
	return kmalloc(size, 0);
}


void vfree(void const *addr)
{
	kfree(addr);
}


/********************
 ** linux/string.h **
 ********************/

char *strcpy(char *to, const char *from)
{
	char *save = to;
	for (; (*to = *from); ++from, ++to);
 	return(save);
}


char *strncpy(char *dst, const char* src, size_t n)
{
	return Genode::strncpy(dst, src, n);
}


char *strchr(const char *p, int ch)
{
	char c;
	c = ch;
	for (;; ++p) {
		if (*p == c)
			return ((char *)p);
		if (*p == '\0')
			break;
	}

	return 0;
}


char *strnchr(const char *p, size_t count, int ch)
{
	char c;
	c = ch;
	for (; count; ++p, count--) {
		if (*p == c)
			return ((char *)p);
		if (*p == '\0')
			break;
	}

	return 0;
}


size_t strnlen(const char *s, size_t maxlen)
{
	size_t c;
	for (c = 0; c < maxlen; c++)
		if (!s[c])
			return c;

	return maxlen;
}


size_t strlen(const char *s) { return Genode::strlen(s); }


int strcmp(const char *s1, const char *s2) { return Genode::strcmp(s1, s2); }


int strncmp(const char *s1, const char *s2, size_t len) {
	return Genode::strcmp(s1, s2, len); }


int memcmp(const void *p0, const void *p1, size_t size) {
	return Genode::memcmp(p0, p1, size); }


int snprintf(char *str, size_t size, const char *format, ...)
{
	va_list list;
	va_start(list, format);

	Genode::String_console sc(str, size);
	sc.vprintf(format, list);
	va_end(list);

	return sc.len();
}


size_t strlcpy(char *dest, const char *src, size_t size)
{
	size_t ret = strlen(src);
	
	if (size) {
		size_t len = (ret >= size) ? size - 1 : ret;
		Genode::memcpy(dest, src, len);
		dest[len] = '\0';
	}
	return ret;
}


/* from linux/lib/string.c */
char *strstr(char const *s1, char const *s2)
{
	size_t l1, l2;

	l2 = strlen(s2);
	if (!l2)
		return (char *)s1;
	l1 = strlen(s1);
	while (l1 >= l2) {
		l1--;
		if (!memcmp(s1, s2, l2))
			return (char *)s1;
		s1++;
	}
	return NULL;
}

void *memset(void *s, int c, size_t n)
{
	return Genode::memset(s, c, n);
}


void *memcpy(void *d, const void *s, size_t n)
{
	return Genode::memcpy(d, s, n);
}


void *memmove(void *d, const void *s, size_t n)
{
	return Genode::memmove(d, s, n);
}


/*******************
 ** linux/sched.h **
 *******************/

struct Timeout : Genode::Signal_handler<Timeout>
{
	Genode::Entrypoint &ep;
	Timer::Connection timer;
	void (*tick)();

	void handle()
	{
		update_jiffies();

		/* tick the higher layer of the component */
		tick();
	}

	Timeout(Genode::Env &env, Genode::Entrypoint &ep, void (*ticker)())
	:
		Signal_handler<Timeout>(ep, *this, &Timeout::handle),
		ep(ep), timer(env), tick(ticker)
	{
		timer.sigh(*this);
	}

	void schedule(signed long msec)
	{
		timer.trigger_once(msec * 1000);
	}

	void wait()
	{
		ep.wait_and_dispatch_one_signal();
	}
};


static Timeout *_timeout;
static Genode::Signal_context_capability tick_sig_cap;

void Lx::event_init(Genode::Env &env, Genode::Entrypoint &ep, void (*ticker)())
{
	static Timeout handler(env, ep, ticker);
	_timeout = &handler;
}

signed long schedule_timeout(signed long timeout)
{
	long start = jiffies;
	_timeout->schedule(timeout);
	_timeout->wait();
	timeout -= jiffies - start;
	return timeout < 0 ? 0 : timeout;
}


long schedule_timeout_uninterruptible(signed long timeout)
{
	return schedule_timeout(timeout);
}

void poll_wait(struct file * filp, wait_queue_head_t * wait_address, poll_table *p)
{
	_timeout->wait();
}

bool poll_does_not_wait(const poll_table *p)
{
	return p == nullptr;
}


/******************
 ** linux/time.h **
 ******************/

unsigned long get_seconds(void)
{
	return jiffies / HZ;
}


/*****************
 ** linux/gfp.h **
 *****************/

class Avl_page : public Genode::Avl_node<Avl_page>
{
	private:

		Genode::addr_t  _addr;
		Genode::size_t  _size;
		struct page    *_page;

	public:

		Avl_page(Genode::size_t size) : _size(size)
		{
			_addr =(Genode::addr_t)kmalloc(size, 0);
			if (!_addr)
				throw -1;

			_page = (struct page *) kzalloc(sizeof(struct page), 0);
			if (!_page) {
				kfree((void *)_addr);
				throw -2;
			}

			_page->addr = (void *)_addr;
			atomic_set(&_page->_count, 1);

			lx_log(DEBUG_SLAB, "alloc page: %p addr: %lx-%lx", _page, _addr, _addr + _size);
		}

		virtual ~Avl_page()
		{
			lx_log(DEBUG_SLAB, "free page: %p addr: %lx-%lx", _page, _addr, _addr + _size);
			kfree((void *)_addr);
			kfree((void *)_page);
		}

		struct page* page() { return _page; }

		bool higher(Avl_page *c)
		{
			return c->_addr > _addr;
		}

		Avl_page *find_by_address(Genode::addr_t addr)
		{
			if (addr >= _addr && addr < _addr + _size)
				return this;

			bool side = addr > _addr;
			Avl_page *c = Avl_node<Avl_page>::child(side);
			return c ? c->find_by_address(addr) : 0;
		}
};


static Genode::Avl_tree<Avl_page> tree;


struct page *alloc_pages(gfp_t gfp_mask, unsigned int order)
{
	Avl_page *p;
	try {
		p = (Avl_page *)new (lx_env->heap()) Avl_page(PAGE_SIZE << order);
		tree.insert(p);
	} catch (...) { return 0; }

	return p->page();
}


void *__alloc_page_frag(struct page_frag_cache *nc,
                        unsigned int fragsz, gfp_t gfp_mask)
{
	struct page *page = alloc_pages(gfp_mask, fragsz / PAGE_SIZE);
	if (!page) return nullptr;

	return page->addr;
}


void __free_page_frag(void *addr)
{
	Avl_page *p = tree.first()->find_by_address((Genode::addr_t)addr);

	tree.remove(p);
	destroy(lx_env->heap(), p);
}


/****************
 ** linux/mm.h **
 ****************/

struct page *virt_to_head_page(const void *x)
{
	Avl_page *p = tree.first()->find_by_address((Genode::addr_t)x);
	lx_log(DEBUG_SLAB, "virt_to_head_page: %p page %p\n", x,p ? p->page() : 0);
	
	return p ? p->page() : 0;
}


void put_page(struct page *page)
{
	if (!atomic_dec_and_test(&page->_count))
		return;

	lx_log(DEBUG_SLAB, "put_page: %p", page);
	Avl_page *p = tree.first()->find_by_address((Genode::addr_t)page->addr);

	tree.remove(p);
	destroy(lx_env->heap(), p);
}


static void create_event(char const *fmt, va_list list)
{
	enum { BUFFER_LEN = 64, EVENT_LEN = BUFFER_LEN + 32 };
	char buf[BUFFER_LEN];

	using namespace Genode;

	String_console sc(buf, BUFFER_LEN);
	sc.vprintf(fmt, list);

	char event[EVENT_LEN];
	static Trace::Timestamp last = 0;
	       Trace::Timestamp now  = Trace::timestamp();
	Genode::snprintf(event, sizeof(event), "delta = %llu ms %s",
	                 (now - last) / 2260000, buf);
	Thread::trace(event);
	last = now;
}


extern "C" void lx_trace_event(char const *fmt, ...)
{
	va_list list;
	va_start(list, fmt);
	create_event(fmt, list);
	va_end(list);
}


/*****************
 ** linux/uio.h **
 *****************/

size_t copy_from_iter(void *addr, size_t bytes, struct iov_iter *i)
{
	if (bytes > i->count)
		bytes = i->count;

	if (bytes == 0)
		return 0;

	char             *kdata = reinterpret_cast<char*>(addr);
	struct iovec const *iov = i->iov;

	size_t len = bytes;
	while (len > 0) {
		if (iov->iov_len) {
			size_t copy_len = (size_t)len < iov->iov_len ? len : iov->iov_len;
			Genode::memcpy(kdata, iov->iov_base, copy_len);

			len -= copy_len;
			kdata += copy_len;
			i->count -= copy_len; /* XXX the vanilla macro does that */
		}
		iov++;
	}

	return bytes;
}


size_t copy_to_iter(void *addr, size_t bytes, struct iov_iter *i)
{
	if (bytes > i->count)
		bytes = i->count;

	if (bytes == 0)
		return 0;

	char             *kdata = reinterpret_cast<char*>(addr);
	struct iovec const *iov = i->iov;

	size_t len = bytes;
	while (len > 0) {
		if (iov->iov_len) {
			size_t copy_len = (size_t)len < iov->iov_len ? len : iov->iov_len;
			Genode::memcpy(iov->iov_base, kdata, copy_len);

			len   -= copy_len;
			kdata += copy_len;

			i->count -= copy_len; /* XXX the vanilla macro does that */
		}
		iov++;
	}

	return bytes;
}


size_t copy_page_to_iter(struct page *page, size_t offset, size_t bytes,
                         struct iov_iter *i)
{
	return copy_to_iter(reinterpret_cast<unsigned char*>(page->addr) + offset, bytes, i);
}


size_t copy_page_from_iter(struct page *page, size_t offset, size_t bytes,
                           struct iov_iter *i)
{
	return copy_from_iter(reinterpret_cast<unsigned char*>(page->addr) + offset, bytes, i);
}


size_t csum_and_copy_from_iter(void *addr, size_t bytes, __wsum *csum, struct iov_iter *i)
{
	if (bytes > i->count)
		bytes = i->count;

	if (bytes == 0)
		return 0;

	char             *kdata = reinterpret_cast<char*>(addr);
	struct iovec const *iov = i->iov;

	__wsum sum = *csum;
	size_t len = bytes;
	while (len > 0) {
		if (iov->iov_len) {
			size_t copy_len = (size_t)len < iov->iov_len ? len : iov->iov_len;
			int err = 0;
			__wsum next = csum_and_copy_from_user(iov->iov_base, kdata, copy_len, 0, &err);

			if (err) {
				Genode::error(__func__, ": err: ", err, " - sleeping");
				Genode::sleep_forever();
			}

			sum = csum_block_add(sum, next, bytes-len);

			len   -= copy_len;
			kdata += copy_len;

			i->count -= copy_len; /* XXX the vanilla macro does that */
		}
		iov++;
	}

	*csum = sum;

	return bytes;
}


size_t csum_and_copy_to_iter(void *addr, size_t bytes, __wsum *csum, struct iov_iter *i)
{
	if (bytes > i->count)
		bytes = i->count;

	if (bytes == 0)
		return 0;

	char             *kdata = reinterpret_cast<char*>(addr);
	struct iovec const *iov = i->iov;

	__wsum sum = *csum;
	size_t len = bytes;
	while (len > 0) {
		if (iov->iov_len) {
			size_t copy_len = (size_t)len < iov->iov_len ? len : iov->iov_len;
			int err = 0;
			__wsum next = csum_and_copy_to_user(kdata, iov->iov_base, copy_len, 0, &err);

			if (err) {
				Genode::error(__func__, ": err: ", err, " - sleeping");
				Genode::sleep_forever();
			}

			sum = csum_block_add(sum, next, bytes-len);

			len   -= copy_len;
			kdata += copy_len;

			i->count -= copy_len; /* XXX the vanilla macro does that */
		}
		iov++;
	}

	*csum = sum;

	return bytes;
}


/******************
 ** linux/wait.h **
 ******************/

void __wake_up(wait_queue_head_t *q, bool all) { }


/***********************
 ** linux/workqueue.h **
 ***********************/

static void execute_delayed_work(unsigned long dwork)
{
	delayed_work *d = (delayed_work *)dwork;
	d->work.func(&d->work);
}


bool mod_delayed_work(struct workqueue_struct *wq, struct delayed_work *dwork,
                      unsigned long delay)
{
	/* treat delayed work without delay like any other work */
	if (delay == 0) {
		execute_delayed_work((unsigned long)dwork);
	} else {
		if (!dwork->timer.function) {
			setup_timer(&dwork->timer, execute_delayed_work,
			            (unsigned long)dwork);
		}
		mod_timer(&dwork->timer, delay);
	}
	return true;
}

int schedule_delayed_work(struct delayed_work *dwork, unsigned long delay)
{
	return mod_delayed_work(0, dwork, delay);
}


/*******************
 ** linux/timer.h **
 *******************/

static unsigned long round_jiffies(unsigned long j, bool force_up)
{
	unsigned remainder = j % HZ;

	/*
	 * from timer.c
	 *
	 * If the target jiffie is just after a whole second (which can happen
	 * due to delays of the timer irq, long irq off times etc etc) then
	 * we should round down to the whole second, not up. Use 1/4th second
	 * as cutoff for this rounding as an extreme upper bound for this.
	 * But never round down if @force_up is set.
	 */

	/* per default round down */
	j = j - remainder;

	/* round up if remainder more than 1/4 second (or if we're forced to) */
	if (remainder >= HZ/4 || force_up)
		j += HZ;

	return j;
}

unsigned long round_jiffies(unsigned long j)
{
	return round_jiffies(j, false);
}


unsigned long round_jiffies_up(unsigned long j)
{
	return round_jiffies(j, true);
}


unsigned long round_jiffies_relative(unsigned long j)
{
	return round_jiffies(j + jiffies, false) - jiffies;
}
