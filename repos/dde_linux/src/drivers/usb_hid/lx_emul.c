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

static struct hc_driver _hc_driver = { };
struct device sysdev = { };

unsigned long lx_usb_register_device(genode_usb_client_handle_t handle, char const *label)
{
	struct usb_device *udev;
	struct usb_hcd *hcd;
	int err;
	struct genode_usb_device_descriptor dev_descr;
	struct genode_usb_config_descriptor conf_descr;

	err = genode_usb_client_config_descriptor(handle, &dev_descr, &conf_descr);
	if (err) {
		printk("error: failed to read config descriptor\n");
		return 0;
	}

	device_initialize(&sysdev);
	//udev = (struct usb_device *)kzalloc(sizeof(struct usb_device), GFP_KERNEL);
	printk("%s:%d ALLOC udev: %px UDEV_DEV: %px\n", __func__, __LINE__, udev, &udev->dev);
	hcd = (struct usb_hcd *)kzalloc(sizeof(struct usb_hcd), GFP_KERNEL);
	hcd->driver = & _hc_driver;
	/* hcd->self is usb_bus */
	hcd->self.bus_name = "usbbus";
	hcd->self.controller = (struct device *)handle;
	hcd->self.sysdev = &sysdev;

	udev = usb_alloc_dev(NULL, &hcd->self, 0);
	if (!udev) {
		printk("error: could not allocate udev for %s\n", label);
		return 0;
	}
printk("%s:%d\n", __func__, __LINE__);
	dev_set_name(&udev->dev, "%s", label);
	udev->bus_mA = 900; /* set to maximum USB3.0 */

	memcpy(&udev->descriptor, &dev_descr, sizeof(struct usb_device_descriptor));
	udev->devnum = dev_descr.num;
	udev->speed  = (enum usb_device_speed)dev_descr.speed;
	udev->authorized = 1;


	err = usb_new_device(udev);
	if (err) {
		printk("error: usb_new_device failed %d\n", err);
		return 0;
	}

	return (unsigned long)udev;
}


void * hcd_buffer_alloc(struct usb_bus * bus, size_t size, gfp_t mem_flags, dma_addr_t * dma)
{
	return kmalloc(size, GFP_KERNEL);
}


void hcd_buffer_free(struct usb_bus * bus, size_t size, void * addr, dma_addr_t dma)
{
	kfree(addr);
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


static struct usb_interface_assoc_descriptor *find_iad(struct usb_device *dev,
                                                       struct usb_host_config *config,
                                                       u8 inum)
{
	struct usb_interface_assoc_descriptor *retval = NULL;
	struct usb_interface_assoc_descriptor *intf_assoc;
	int first_intf;
	int last_intf;
	int i;

	for (i = 0; (i < USB_MAXIADS && config->intf_assoc[i]); i++) {
		intf_assoc = config->intf_assoc[i];
		if (intf_assoc->bInterfaceCount == 0)
			continue;

		first_intf = intf_assoc->bFirstInterface;
		last_intf = first_intf + (intf_assoc->bInterfaceCount - 1);
		if (inum >= first_intf && inum <= last_intf) {
			if (!retval)
				retval = intf_assoc;
			else
				dev_err(&dev->dev, "Interface #%d referenced"
						" by multiple IADs\n", inum);
		}
	}

	return retval;
}

extern struct bus_type usb_bus_type;
extern struct device_type usb_if_device_type;

int usb_set_configuration(struct usb_device *dev, int configuration)
{
	int i, ret;
	struct usb_host_config *cp = NULL;
	struct usb_interface **new_interfaces = NULL;
	int n, nintf;
printk("%s:%d\n", __func__, __LINE__);
	if (dev->authorized == 0 || configuration == -1)
		configuration = 0;
	else {
		for (i = 0; i < dev->descriptor.bNumConfigurations; i++) {
			if (dev->config[i].desc.bConfigurationValue ==
				configuration) {
				cp = &dev->config[i];
				break;
			}
		}
	}
	if ((!cp && configuration != 0))
		return -EINVAL;

	/* The USB spec says configuration 0 means unconfigured.
	 * But if a device includes a configuration numbered 0,
	 * we will accept it as a correctly configured state.
	 * Use -1 if you really want to unconfigure the device.
	 */
	if (cp && configuration == 0)
		dev_warn(&dev->dev, "config 0 descriptor??\n");

	/* Allocate memory for new interfaces before doing anything else,
	 * so that if we run out then nothing will have changed. */
	n = nintf = 0;
	if (cp) {
		nintf = cp->desc.bNumInterfaces;
		new_interfaces = (struct usb_interface **)
			kmalloc(nintf * sizeof(*new_interfaces), GFP_KERNEL);
		if (!new_interfaces)
			return -ENOMEM;

		for (; n < nintf; ++n) {
			new_interfaces[n] = (struct usb_interface*)
				kzalloc( sizeof(struct usb_interface), GFP_KERNEL);
			if (!new_interfaces[n]) {
				ret = -ENOMEM;
				while (--n >= 0)
					kfree(new_interfaces[n]);
				kfree(new_interfaces);
				return ret;
			}
		}
	}

	/*
	 * Initialize the new interface structures and the
	 * hc/hcd/usbcore interface/endpoint state.
	 */
	for (i = 0; i < nintf; ++i) {
		struct usb_interface_cache *intfc;
		struct usb_interface *intf;
		struct usb_host_interface *alt;
		u8 ifnum;

		cp->interface[i] = intf = new_interfaces[i];
		intfc = cp->intf_cache[i];
		intf->altsetting = intfc->altsetting;
		intf->num_altsetting = intfc->num_altsetting;
		intf->authorized = 1; //FIXME

		alt = usb_altnum_to_altsetting(intf, 0);

		/* No altsetting 0?  We'll assume the first altsetting.
		 * We could use a GetInterface call, but if a device is
		 * so non-compliant that it doesn't have altsetting 0
		 * then I wouldn't trust its reply anyway.
		 */
		if (!alt)
			alt = &intf->altsetting[0];

		ifnum = alt->desc.bInterfaceNumber;
		intf->intf_assoc = find_iad(dev, cp, ifnum);
		intf->cur_altsetting = alt;
		intf->dev.parent = &dev->dev;
		intf->dev.driver = NULL;
		intf->dev.bus = &usb_bus_type;
		intf->dev.type = &usb_if_device_type;
		intf->minor = -1;
		device_initialize(&intf->dev);
		dev_set_name(&intf->dev, "%d-%s:%d.%d", dev->bus->busnum,
					 dev->devpath, configuration, ifnum);
	}
	kfree(new_interfaces);

	ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
						  USB_REQ_SET_CONFIGURATION, 0, configuration, 0,
						  NULL, 0, USB_CTRL_SET_TIMEOUT);
	if (ret < 0 && cp) {
		for (i = 0; i < nintf; ++i) {
			put_device(&cp->interface[i]->dev);
			cp->interface[i] = NULL;
		}
		cp = NULL;
	}

	dev->actconfig = cp;

	if (!cp) {
		dev->state = USB_STATE_ADDRESS;
		return ret;
	}
	dev->state = USB_STATE_CONFIGURED;

	for (i = 0; i < nintf; ++i) {
		struct usb_interface *intf = cp->interface[i];

		dev_dbg(&dev->dev,
			"adding %s (config #%d, interface %d)\n",
			dev_name(&intf->dev), configuration,
			intf->cur_altsetting->desc.bInterfaceNumber);
		device_enable_async_suspend(&intf->dev);
		printk("%s:%d ADD\n", __func__, __LINE__);
		ret = device_add(&intf->dev);
		printk("%s:%d ADD %d %s\n", __func__, __LINE__, ret, dev_name(&intf->dev));
		if (ret != 0) {
			printk("device_add(%s) --> %d\n", dev_name(&intf->dev), ret);
			continue;
		}
	}

	return 0;
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
