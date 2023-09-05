#include <lx_emul.h>


#include <asm/pgtable.h>

pteval_t __default_kernel_pte_mask __read_mostly = ~0;


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


#include <linux/stringhash.h>

unsigned int full_name_hash(const void *salt, const char *name, unsigned int len)
{
	unsigned hash = ((unsigned long)salt) & ~0u;
	unsigned i;
	for (i = 0; i < len; i++)
		hash += name[i];

	return hash;
}


#include <linux/memblock.h>

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
	void *table;

	nlog2 <<= (1 << nlog2) < elements ? 1 : 0;

	table = kmalloc(elements * bucketsize, GFP_KERNEL);
	if (!table) {
		printk("%s:%d error failed to allocate system hash\n", __func__, __LINE__);
		return NULL;
	}

	if (_hash_mask)
		*_hash_mask = (1 << nlog2) - 1;

	if (_hash_shift)
		*_hash_shift = nlog2;

	return table;
}


#include <linux/syscore_ops.h>

void register_syscore_ops(struct syscore_ops * ops)
{
	lx_emul_trace(__func__);
}


#include <linux/rcutree.h>

/*
 * taken from src/lib/wifi/lx_emul.c
 */
void kvfree_call_rcu(struct rcu_head * head, rcu_callback_t func)
{
	void *ptr = (void *) head - (unsigned long) func;
	kvfree(ptr);
}


/* mm/page_alloc. */

/**
 * nr_free_buffer_pages - count number of pages beyond high watermark
 *
 * nr_free_buffer_pages() counts the number of pages which are beyond the high
 * watermark within ZONE_DMA and ZONE_NORMAL.
 *
 * used in 'tcp_mem_init'
 *
 * limit = max(nr_free_buffer_pages()/16, 128)
 * -> set to max
 */
unsigned long nr_free_buffer_pages(void)
{
	return 2048;
}


/****************************
 ** Linux socket functions **
 ****************************/

#include <linux/net.h>
#include <linux/skbuff.h>


static const struct net_proto_family *net_families[NPROTO];


int sock_register(const struct net_proto_family *ops)
{
	if (ops->family >= NPROTO) {
		printk("protocol %d >=  NPROTO (%d)\n", ops->family, NPROTO);
		return -ENOBUFS;
	}

	net_families[ops->family] = ops;
	pr_info("NET: Registered protocol family %d\n", ops->family);
	return 0;
}


struct socket *sock_alloc(void)
{
	struct socket *sock = (struct socket *)kzalloc(sizeof(struct socket), 0);

	init_waitqueue_head(&sock->wq.wait);
	sock->wq.fasync_list = NULL;
	sock->wq.flags = 0;

	sock->state = SS_UNCONNECTED;
	sock->flags = 0;
	sock->ops = NULL;
	sock->sk = NULL;
	sock->file = NULL;


	return sock;
}


int sock_create_lite(int family, int type, int protocol, struct socket **res)

{
	struct socket *sock = sock_alloc();

	if (!sock)
		return -ENOMEM;

	sock->type = type;
	*res = sock;
	return 0;
}


int sock_create_kern(struct net *net, int family, int type, int proto,
                     struct socket **res)
{
	struct socket *sock;
	const struct net_proto_family *pf;
	int err;

	if (family < 0 || family > NPROTO)
		return -EAFNOSUPPORT;

	if (type < 0 || type > SOCK_MAX)
		return -EINVAL;

	pf = net_families[family];

	if (!pf) {
		printk("No protocol found for family %d\n", family);
		return -ENOPROTOOPT;
	}

	sock = sock_alloc();
	if (!sock) {
		printk("Could not allocate socket\n");
		return -ENFILE;
	}

	sock->type = type;

	err = pf->create(net, sock, proto, 1);
	if (err) {
		kfree(sock);
		return err;
	}

	*res = sock;

	return 0;
}


static int sock_init(void)
{
	skb_init();
	return 0;
}


core_initcall(sock_init);


