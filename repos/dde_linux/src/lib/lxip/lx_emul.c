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


#include <linux/net.h>


/****************************
 ** Linux socket functions **
 ****************************/

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


