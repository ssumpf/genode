#include <lx_emul.h>

#include <linux/proc_fs.h>
#include <linux/slab.h>

const struct attribute_group hdac_dev_attr_groups;
const struct attribute_group pci_dev_acpi_attr_group;

pteval_t __default_kernel_pte_mask __read_mostly = ~0;


