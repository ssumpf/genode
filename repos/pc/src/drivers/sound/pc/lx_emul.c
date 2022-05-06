#include <lx_emul.h>

#include <linux/proc_fs.h>
#include <linux/slab.h>

const struct attribute_group hdac_dev_attr_groups;
const struct attribute_group pci_dev_acpi_attr_group;

pteval_t __default_kernel_pte_mask __read_mostly = ~0;


void * kmalloc_order(size_t size, gfp_t flags, unsigned int order)
{
	return kmalloc(size, flags);
}


int simple_pin_fs(struct file_system_type *type, struct vfsmount ** mount, int * count)
{
	lx_emul_trace(__func__);

	if (!mount)
		return -EFAULT;

	if (!*mount)
		*mount = kzalloc(sizeof(struct vfsmount), GFP_KERNEL);

	if (!*mount)
		return -ENOMEM;

	if (count)
		++*count;

	return 0;
}


struct inode * alloc_anon_inode(struct super_block * s)
{
	return kzalloc(sizeof(struct inode), GFP_KERNEL);
}


extern bool pat_enabled(void);
bool pat_enabled(void)
{
	lx_emul_trace(__func__);
	return true;
}


