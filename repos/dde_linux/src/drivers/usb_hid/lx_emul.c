/*
 * \brief  Implementation of driver specific Linux functions
 * \author Sebastian Sumpf
 * \date   2023-06-29
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

#include <linux/cdev.h>
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

struct meta_data
{
	struct usb_hcd    *hcd;
	struct device     *sysdev;
	struct usb_device *udev;
};


void *lx_emul_usb_client_register_device(genode_usb_client_handle_t handle, char const *label)
{
	struct meta_data  *meta;
	int err;
	struct genode_usb_device_descriptor dev_descr;
	struct genode_usb_config_descriptor conf_descr;

	err = genode_usb_client_config_descriptor(handle, &dev_descr, &conf_descr);
	if (err) {
		printk("error: failed to read config descriptor\n");
		return NULL;;
	}

	meta = (struct meta_data *)kmalloc(sizeof(struct meta_data), GFP_KERNEL);
	if (!meta) return NULL;

	meta->sysdev = (struct device*)kzalloc(sizeof(struct device), GFP_KERNEL);
	if (!meta->sysdev) goto sysdev;

	device_initialize(meta->sysdev);

	meta->hcd = (struct usb_hcd *)kzalloc(sizeof(struct usb_hcd), GFP_KERNEL);
	if (!meta->hcd) goto hcd;

	/* hcd->self is usb_bus */
	meta->hcd->driver        = &_hc_driver;
	meta->hcd->self.bus_name = "usbbus";
	meta->hcd->self.sysdev   = meta->sysdev;

	meta->udev = usb_alloc_dev(NULL, &meta->hcd->self, 0);
	if (!meta->udev) {
		printk("error: could not allocate udev for %s\n", label);
		goto udev;
	}
	printk("%s:%d NAME: %s\n", __func__, __LINE__, meta->udev->dev.bus->name);
	/* usb_alloc_dev sets parent to bus->controller if first argument is NULL */
	meta->hcd->self.controller = (struct device *)handle;

	memcpy(&meta->udev->descriptor, &dev_descr, sizeof(struct usb_device_descriptor));
	meta->udev->devnum     = dev_descr.num;
	meta->udev->speed      = (enum usb_device_speed)dev_descr.speed;
	meta->udev->authorized = 1;
	meta->udev->bus_mA     = 900; /* set to maximum USB3.0 */
	meta->udev->state      = USB_STATE_NOTATTACHED;

	dev_set_name(&meta->udev->dev, "%s", label);

	printk("%s:%d 1: %px 2: %px 3: %px &3: %px\n", __func__, __LINE__, meta->hcd, meta->sysdev, meta->udev, &meta->udev);
	err = usb_new_device(meta->udev);
	printk("%s:%d 1: %px 2: %px 3: %px\n", __func__, __LINE__, meta->hcd, meta->sysdev, meta->udev);

	if (err) {
		printk("error: usb_new_device failed %d\n", err);
		goto new_device;
	}
	return meta;

new_device:
	usb_put_dev(meta->udev);
udev:
	kfree(meta->hcd);
hcd:
	kfree(meta->sysdev);
sysdev:
	kfree(meta);

	return NULL;
}


void lx_emul_usb_client_unregister_device(genode_usb_client_handle_t handle, void *data)
{
	struct meta_data *meta = (struct meta_data *)data;

	printk("%s:%d\n", __func__, __LINE__);
	printk("%s:%d %s\n", __func__, __LINE__, meta->udev->dev.bus->name);
	usb_disconnect(&meta->udev);
	printk("%s:%d\n", __func__, __LINE__);
	usb_put_dev(meta->udev);
	printk("%s:%d\n", __func__, __LINE__);
	kfree(meta->hcd);
	printk("%s:%d\n", __func__, __LINE__);
	kobject_put(&meta->sysdev->kobj);
	printk("%s:%d\n", __func__, __LINE__);
	kfree(meta->sysdev);
	printk("%s:%d\n", __func__, __LINE__);
	kfree(meta);
	printk("%s:%d\n", __func__, __LINE__);
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

	genode_usb_client_handle_t handle =
		(genode_usb_client_handle_t)dev->bus->controller;

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
		printk("%s:%d ADD h: %lu i: %d\n", __func__, __LINE__, handle, intf->cur_altsetting->desc.bInterfaceNumber);
		ret = device_add(&intf->dev);
		printk("%s:%d ADD %d %s\n", __func__, __LINE__, ret, dev_name(&intf->dev));

		if (ret != 0) {
			printk("error: device_add(%s) --> %d\n", dev_name(&intf->dev), ret);
			continue;
		}
	}

	return 0;
}

void usb_disable_device(struct usb_device *dev, int skip_ep0)
{
	int i;

	/* getting rid of interfaces will disconnect
	 * any drivers bound to them (a key side effect)
	 */
	if (dev->actconfig) {
		/*
		 * FIXME: In order to avoid self-deadlock involving the
		 * bandwidth_mutex, we have to mark all the interfaces
		 * before unregistering any of them.
		 */
		for (i = 0; i < dev->actconfig->desc.bNumInterfaces; i++)
			dev->actconfig->interface[i]->unregistering = 1;

		for (i = 0; i < dev->actconfig->desc.bNumInterfaces; i++) {
			struct usb_interface	*interface;

			/* remove this interface if it has been registered */
			interface = dev->actconfig->interface[i];
			if (!device_is_registered(&interface->dev))
				continue;

			dev_dbg(&dev->dev, "unregistering interface %s\n",
				dev_name(&interface->dev));
			device_del(&interface->dev);
		}

		/* Now that the interfaces are unbound, nobody should
		 * try to access them.
		 */
		for (i = 0; i < dev->actconfig->desc.bNumInterfaces; i++) {
			put_device(&dev->actconfig->interface[i]->dev);
			dev->actconfig->interface[i] = NULL;
		}

		dev->actconfig = NULL;
		if (dev->state == USB_STATE_CONFIGURED)
			usb_set_device_state(dev, USB_STATE_ADDRESS);
	}

	dev_dbg(&dev->dev, "%s nuking %s URBs\n", __func__,
		skip_ep0 ? "non-ep0" : "all");
}
