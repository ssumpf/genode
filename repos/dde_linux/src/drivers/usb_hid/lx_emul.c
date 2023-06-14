#include <lx_emul.h>

#include <linux/device.h>
#include <linux/sysfs.h>

const struct attribute_group input_poller_attribute_group;
pteval_t __default_kernel_pte_mask __read_mostly = ~0;


struct device_type usb_device_type = {
	.name = "usb_device"
};

struct device_type usb_if_device_type = {
	.name = "usb_interface"
};

const char *usbcore_name = "usbcore";

