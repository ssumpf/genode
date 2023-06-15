#include <lx_emul.h>

#include <linux/device.h>
#include <linux/sysfs.h>
#include <linux/usb.h>

const struct attribute_group input_poller_attribute_group;
pteval_t __default_kernel_pte_mask __read_mostly = ~0;

#if 0
struct device_type usb_device_type = {
	.name = "usb_device"
};

struct device_type usb_if_device_type = {
	.name = "usb_interface"
};
#endif
const char *usbcore_name = "usbcore";

/*******************
 ** device_driver **
 *******************/
#if 0
static LIST_HEAD(hid_drivers);


struct hid_driver_entry
{
	struct device_driver *driver;
	struct list_head      list;
};


static bool driver_match(struct device *dev, struct device_driver *dev_drv)
{
	/*
	 *  Don't try if buses don't match, since drivers often use 'container_of'
	 *  which might cast the device to non-matching type
	 */
	if (dev_drv->bus != dev->bus)
		return false;

	return dev_drv->bus->match ? dev_drv->bus->match(dev, dev_drv)
	                          : false;
}


static int driver_probe(struct device *dev, struct device_driver *dev_drv)
{
	dev->driver = dev_drv;
	if (dev_drv->bus->probe) return dev_drv->bus->probe(dev);
	return 0;
}


int driver_register(struct device_driver *drv)
{
	struct hid_driver_entry *entry;
	if (!drv)
		return 1;

	printk("%s:%d name: %s\n", __func__, __LINE__, drv->name);

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	entry->driver = drv;

	INIT_LIST_HEAD(&entry->list);
	list_add_tail(&entry->list, &hid_drivers);

	return 0;
}

static struct usb_driver * hid_driver;
int usb_register_driver(struct usb_driver * driver, struct module *, const char *)
{
	printk("%s:%d: name: %s\n", __func__, __LINE__, driver->name);
	hid_driver = driver;
	return 0;
}
#endif

/************
 ** device **
 ************/
#if 0
int device_add(struct device *dev)
{
	struct hid_driver_entry *entry;
	int ret;
	printk("%s:%d %s\n", __func__, __LINE__, dev_name(dev));
	if (dev->driver) return 0;

	/* foreach driver match and probe device */
	list_for_each_entry(entry, &hid_drivers, list) {
		if (driver_match(dev, entry->driver)) {
			ret = driver_probe(dev, entry->driver);
			if (!ret) return 0;
		}
	}

	return 0;
}


void device_del(struct device *dev)
{
	if (dev->bus && dev->bus->remove)
		dev->bus->remove(dev);
}
#endif
