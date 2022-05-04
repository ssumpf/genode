/*
 * \brief  Genode implementation of Linux kernel functions
 * \author Sebastian Sumpf
 * \date   2022-05-31
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

#include <linux/async.h>
#include <linux/firmware.h>
#include <linux/moduleparam.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>

#include <lx_vmap.h>

const struct attribute_group hdac_dev_attr_groups;
const struct attribute_group pci_dev_acpi_attr_group;
const struct attribute_group input_poller_attribute_group;

pteval_t __default_kernel_pte_mask __read_mostly = ~0;

extern int  lx_emul_request_firmware_nowait(const char *name, void *dest, size_t *result);
extern void lx_emul_release_firmware(void const *data, size_t size);


/**
 * firmware
 */
int request_firmware(const struct firmware ** firmware_p,
                     const char * name, struct device * device)
{
	struct firmware *fw;

	const char * base = kbasename(name);

	if (!firmware_p) {
		return -1;
	}

	fw = kzalloc(sizeof (struct firmware), GFP_KERNEL);

	if (lx_emul_request_firmware_nowait(base, &fw->data, &fw->size)) {
		kfree(fw);
		return -1;
	}

	*firmware_p = fw;

	return 0;
}


void release_firmware(const struct firmware * fw)
{
	lx_emul_release_firmware(fw->data, fw->size);
	kfree(fw);
}


/*
 * vmap
 */
void * vmap(struct page ** pages,unsigned int count, unsigned long flags, pgprot_t prot)
{
	unsigned i = 0;
	int err = 0;
	void *vmap = lx_vmap_create(count * PAGE_SIZE);
	if (!vmap) {
		printk("Error: could not create vmap\n");
		return NULL;
	}

	for (i = 0; i < count; i++) {

		if ((err = lx_vmap_attach(vmap, page_address(pages[i]), i * PAGE_SIZE))) {
			printk("Error: could not attach vmap page: %p (ret=%d)\n", page_address(pages[i]), err);
			return NULL;
		}
	}

	return lx_vmap_address(vmap);
}


void vunmap(const void * addr)
{
	lx_vmap_destroy(addr);
}


/*
 * module_params
 */
extern char **module_param_hda_model(void);

void lx_emul_module_params(void)
{
	//XXX: make configurable
	char **hda_model = module_param_hda_model();
	*hda_model = kstrdup("dell-headset-multi", GFP_KERNEL);
}


/*
 * async
 */
async_cookie_t async_schedule_node_domain(async_func_t func, void * data, int node,
                                         struct async_domain * domain)
{
	func(data, 0);
	return 0;
}


/*
 * uaccess
 */
unsigned long _copy_to_user(void __user * to, const void * from, unsigned long n)
{
	memcpy(to, from, n);
	return 0;
}


unsigned long _copy_from_user(void * to, const void __user * from, unsigned long n)
{
	memcpy(to, from, n);
	return 0;
}


/*
 * delay
 */
void __const_udelay(unsigned long xloops)
{
	unsigned long usecs = xloops / 0x10C7UL;
	lx_emul_time_udelay(usecs);
}


void __udelay(unsigned long usecs)
{
	__const_udelay(usecs * 0x000010c7); /* 2**32 / 1000000 (rounded up) */
}
