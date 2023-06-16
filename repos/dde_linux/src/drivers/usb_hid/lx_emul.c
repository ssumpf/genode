#include <lx_emul.h>

#include <linux/device.h>
#include <linux/sysfs.h>
#include <linux/usb.h>
#include <linux/usb/hcd.h>

#include <usb_hid.h>

const struct attribute_group input_poller_attribute_group;
pteval_t __default_kernel_pte_mask __read_mostly = ~0;

struct device_type usb_if_device_type = {
	.name = "usb_interface"
};

struct usb_driver usbfs_driver = {
	.name = "usbfs"
};
const struct attribute_group *usb_device_groups[] = { };


unsigned long lx_usb_register_device(genode_usb_client_handle_t handle)
{
	struct usb_device *udev;
	int err;
	struct genode_usb_device_descriptor dev_descr;
	struct genode_usb_config_descriptor conf_descr;

	err = genode_usb_client_config_descriptor(handle, &dev_descr, &conf_descr);
	if (err) {
		printk("error: failed to read config descriptor\n");
		return NULL;
	}

	udev = (struct usb_device *)kzalloc(sizeof(struct usb_device), GFP_KERNEL);
	udev->bus = (struct usb_bus *)kzalloc(sizeof(struct usb_bus), GFP_KERNEL);
	udev->bus->bus_name = "usbbus";
	udev->bus->controller = (struct device *)handle;
	udev->bus_mA = 900; /* set to maximum USB3.0 */

	memcpy(&udev->descriptor, &dev_descr, sizeof(struct usb_device_descriptor));
	udev->devnum = dev_descr.num;
	udev->speed  = (enum usb_device_speed)dev_descr.speed;
	udev->authorized = 1;

	err = usb_new_device(udev);
	if (err) {
		printk("error: usb_new_device failed %d\n", err);
		return NULL;
	}

	return (unsigned long)udev;
}


/*
 * message.c
 */

int usb_get_descriptor(struct usb_device *dev, unsigned char type,
                       unsigned char index, void *buf, int size)
{
	int i;
	int result;

	if (size <= 0)		/* No point in asking for no data */
		return -EINVAL;

	memset(buf, 0, size);	/* Make sure we parse really received data */

	for (i = 0; i < 3; ++i) {
		/* retry on length 0 or error; some devices are flakey */
		result = usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
				USB_REQ_GET_DESCRIPTOR, USB_DIR_IN,
				(type << 8) + index, 0, buf, size,
				USB_CTRL_GET_TIMEOUT);
		if (result <= 0 && result != -ETIMEDOUT)
			continue;
		if (result > 1 && ((u8 *)buf)[1] != type) {
			result = -ENODATA;
			continue;
		}
		break;
	}
	return result;
}

#if 1
//struct device_type usb_device_type = {
//	.name = "usb_device"
//};

#endif
//const char *usbcore_name = "usbcore";

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
