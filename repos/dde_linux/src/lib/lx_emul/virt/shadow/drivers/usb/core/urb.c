/*
 * \brief  urb/message functions using genode_c_api/usb_client.h
 * \author Stefan Kalkowski
 * \author Sebastian Sumpf
 * \date   2023-06-20
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <linux/usb.h>
#include <genode_c_api/usb_client.h>

extern struct bus_type    usb_bus_type;
extern struct device_type usb_if_device_type;

static DECLARE_WAIT_QUEUE_HEAD(lx_emul_urb_wait);

static int wait_for_free_urb(unsigned int timeout_jiffies)
{
	int ret = 0;

	DECLARE_WAITQUEUE(wait, current);
	add_wait_queue(&lx_emul_urb_wait, &wait);

	ret = schedule_timeout(timeout_jiffies);

	remove_wait_queue(&lx_emul_urb_wait, &wait);

	return ret;
}


static int packet_errno(int error)
{
	switch (error) {
	case INTERFACE_OR_ENDPOINT_ERROR: return -ENOENT;
	case MEMORY_ERROR:                return -ENOMEM;
	case NO_DEVICE_ERROR:             return -ESHUTDOWN;
	case PACKET_INVALID_ERROR:        return -EINVAL;
	case PROTOCOL_ERROR:              return -EPROTO;
	case STALL_ERROR:                 return -EPIPE;
	case TIMEOUT_ERROR:               return -ETIMEDOUT;
	case UNKNOWN_ERROR:
		printk("%s: got UNKNOWN_ERROR code\n", __func__);
		return -EIO;
	}

	return -EIO;
}


/*
 * message.c
 */

static void sync_complete(struct genode_usb_client_request_packet *packet)
{
	complete((struct completion *)packet->opaque_data);
};


int usb_control_msg(struct usb_device *dev, unsigned int pipe,
                    __u8 request, __u8 requesttype, __u16 value,
                    __u16 index, void *data, __u16 size, int timeout)
{
	unsigned timeout_jiffies;
	int      ret;
	struct   urb *urb;
	struct   completion comp;

	struct genode_usb_client_request_packet packet;
	struct genode_usb_request_control       control;

	genode_usb_client_handle_t handle;

	if (!dev->bus) return -ENODEV;

	handle = (genode_usb_client_handle_t)dev->bus->controller;

	/*
	 * If this function is called with a timeout of 0 to wait forever,
	 * we wait in pieces of 10s each as 'schedule_timeout' might trigger
	 * immediately otherwise. The intend to wait forever is reflected
	 * back nonetheless when sending the urb.
	 */
	timeout_jiffies = timeout ? msecs_to_jiffies(timeout)
	                          : msecs_to_jiffies(10000u);

	/* dummy alloc urb for wait_for_free_urb below */
	urb = (struct urb *)usb_alloc_urb(0, GFP_KERNEL);
	if (!urb) return -ENOMEM;

	packet.request.type  = CTRL;
	control.request      = request;
	control.request_type = requesttype;
	control.value        = value;
	control.index        = index;
	control.timeout      = timeout ? jiffies_to_msecs(timeout_jiffies) : 0;
	packet.request.req   = &control;
	packet.buffer.size   = size;

	for (;;) {

		if (genode_usb_client_request(handle, &packet)) break;

		timeout_jiffies = wait_for_free_urb(timeout_jiffies);
		if (!timeout_jiffies && timeout) {
			ret = -ETIMEDOUT;
			goto err_request;
		}
	}

	if (!(requesttype & USB_DIR_IN))
		memcpy(packet.buffer.addr, data, size);

	init_completion(&comp);
	packet.complete_callback = sync_complete;
	packet.free_callback     = sync_complete;
	packet.opaque_data       = &comp;

	genode_usb_client_request_submit(handle, &packet);
	wait_for_completion(&comp);

	if (packet.actual_length && data && (size >= packet.actual_length))
		memcpy(data, packet.buffer.addr, packet.actual_length);

	ret = packet.error ? packet_errno(packet.error) : packet.actual_length;
	genode_usb_client_request_finish(handle, &packet);

err_request:
	kfree(urb);

	return ret;
}


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


int usb_set_configuration(struct usb_device *dev, int configuration)
{
	int i, ret;
	struct usb_host_config *cp = NULL;
	struct usb_interface **new_interfaces = NULL;
	int n, nintf;

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

		ret = device_add(&intf->dev);
		if (ret != 0) {
			printk("error: device_add(%s) --> %d\n", dev_name(&intf->dev), ret);
			continue;
		}
	}

	return 0;
}


void usb_enable_endpoint(struct usb_device *dev, struct usb_host_endpoint *ep, bool reset_ep)
{
	int epnum = usb_endpoint_num(&ep->desc);
	int is_out = usb_endpoint_dir_out(&ep->desc);
	int is_control = usb_endpoint_xfer_control(&ep->desc);

	if (is_out || is_control)
		dev->ep_out[epnum] = ep;
	if (!is_out || is_control)
		dev->ep_in[epnum] = ep;
	ep->enabled = 1;
}


void usb_enable_interface(struct usb_device *dev,
		struct usb_interface *intf, bool reset_eps)
{
	struct usb_host_interface *alt = intf->cur_altsetting;
	int i;

	for (i = 0; i < alt->desc.bNumEndpoints; ++i)
		usb_enable_endpoint(dev, &alt->endpoint[i], reset_eps);
}


int usb_set_interface(struct usb_device *udev, int ifnum, int alternate)
{
	int      ret;
	struct   urb *urb;
	struct   completion comp;
	unsigned timeout_jiffies = msecs_to_jiffies(10000u);

	struct genode_usb_client_request_packet packet;
	struct genode_usb_altsetting            alt_setting;

	genode_usb_client_handle_t handle;

	struct usb_interface *iface;

	if (!udev->bus) return -ENODEV;

	if (!udev->config)
		return -ENODEV;

	if (ifnum >= USB_MAXINTERFACES || ifnum < 0)
		return -EINVAL;

	iface = udev->config->interface[ifnum];

	handle = (genode_usb_client_handle_t)udev->bus->controller;

	/* dummy alloc urb for wait_for_free_urb below */
	urb = (struct urb *)usb_alloc_urb(0, GFP_KERNEL);
	if (!urb) return -ENOMEM;

	packet.request.type          = ALT_SETTING;
	alt_setting.interface_number = ifnum;
	alt_setting.alt_setting      = alternate;
	packet.request.req           = &alt_setting;
	packet.buffer.size           = 0;

	for (;;) {

		if (genode_usb_client_request(handle, &packet)) break;

		timeout_jiffies = wait_for_free_urb(timeout_jiffies);
		if (!timeout_jiffies) {
			ret = -ETIMEDOUT;
			goto err_request;
		}
	}

	init_completion(&comp);
	packet.complete_callback = sync_complete;
	packet.free_callback     = sync_complete;
	packet.opaque_data       = &comp;

	genode_usb_client_request_submit(handle, &packet);
	wait_for_completion(&comp);

	ret = packet.error ? packet_errno(packet.error) : 0;
	if (!ret)
		iface->cur_altsetting = &iface->altsetting[alternate];

	usb_enable_interface(udev, iface, true);

	genode_usb_client_request_finish(handle, &packet);

err_request:
	kfree(urb);

	return ret;
}


/*
 * urb.c
 */

struct urb *usb_alloc_urb(int iso_packets, gfp_t mem_flags)
{
	struct urb *urb = (struct urb*)
		kmalloc(sizeof(struct urb) +
		        iso_packets * sizeof(struct usb_iso_packet_descriptor),
		        GFP_KERNEL);

	if (!urb) return NULL;
	memset(urb, 0, sizeof(*urb));
	INIT_LIST_HEAD(&urb->anchor_list);
	return urb;
}


static void free_packet(struct genode_usb_client_request_packet *packet)
{
	kfree(packet->request.req);
	kfree(packet);
}


static void urb_submit_complete(struct genode_usb_client_request_packet *packet)
{
	struct urb *urb = (struct urb *)packet->opaque_data;
	genode_usb_client_handle_t handle = (genode_usb_client_handle_t)urb->hcpriv;

	urb->status = packet->error ? packet_errno(packet->error) : 0;

	if (packet->error == 0 &&
	    packet->actual_length && urb->transfer_buffer &&
	    urb->transfer_buffer_length >= packet->actual_length)
		memcpy(urb->transfer_buffer, packet->buffer.addr, packet->actual_length);

	urb->actual_length = packet->actual_length;

	genode_usb_client_request_finish(handle, packet);

	free_packet(packet);

	if (urb->complete) urb->complete(urb);
};


int usb_submit_urb(struct urb *urb, gfp_t mem_flags)
{
	genode_usb_client_handle_t handle;
	struct genode_usb_client_request_packet *packet;
	struct genode_usb_request_transfer *transfer;
	struct genode_usb_request_control  *control;
	int ret = 0;
	unsigned timeout_jiffies = msecs_to_jiffies(10000u);

	if (!urb->dev->bus)
		return -ENODEV;

	handle = (genode_usb_client_handle_t)urb->dev->bus->controller;

	packet = (struct genode_usb_client_request_packet *)
		kzalloc(sizeof(*packet), GFP_KERNEL);

	if (!packet) return -ENOMEM;

	if (usb_pipetype(urb->pipe) == PIPE_CONTROL) {
		control = (struct genode_usb_request_control *)
			kzalloc(sizeof(*control), GFP_KERNEL);

		if (!control) {
			ret = -ENOMEM;
			goto transfer;
		}
	}
	else {
		transfer = (struct genode_usb_request_transfer *)
			kzalloc(sizeof(*transfer), GFP_KERNEL);

		if (!transfer) {
			ret = -ENOMEM;
			goto transfer;
		}
	}

	switch(usb_pipetype(urb->pipe)) {
	case PIPE_CONTROL:
		{
			struct usb_ctrlrequest * ctrl = (struct usb_ctrlrequest *)
				urb->setup_packet;
			packet->request.type  = CTRL;
			control->request      = ctrl->bRequest;
			control->request_type = ctrl->bRequestType;
			control->value        = ctrl->wValue;
			control->index        = ctrl->wIndex;
			packet->request.req   = control;
			break;
		}
	case PIPE_INTERRUPT:
		{
			packet->request.type       = IRQ;
			transfer->polling_interval = urb->interval;
			transfer->ep               = usb_pipeendpoint(urb->pipe)
			                             | (usb_pipein(urb->pipe) ?  USB_DIR_IN : 0);
			packet->request.req        = transfer;
			break;
		}
	case PIPE_BULK:
		{
			packet->request.type = BULK;
			transfer->ep         = usb_pipeendpoint(urb->pipe)
			                       | (usb_pipein(urb->pipe) ?  USB_DIR_IN : 0);
			packet->request.req  = transfer;
			break;
		}
	default:
		printk("unknown URB requested: %d\n", usb_pipetype(urb->pipe));
	}

	packet->buffer.size       = urb->transfer_buffer_length;
	packet->complete_callback = urb_submit_complete;
	packet->opaque_data       = urb;
	packet->free_callback     = free_packet;

	for (;;) {

		if (genode_usb_client_request(handle, packet)) break;

		timeout_jiffies = wait_for_free_urb(timeout_jiffies);
		if (!timeout_jiffies) {
			ret = -ETIMEDOUT;
			goto err_request;
		}
	}

	if (usb_pipeout(urb->pipe))
		memcpy(packet->buffer.addr, urb->transfer_buffer, urb->transfer_buffer_length);

	urb->hcpriv = (void *)handle;

	genode_usb_client_request_submit(handle, packet);

	return ret;

err_request:
	if (transfer) kfree(transfer);
	if (control)  kfree(control);
transfer:
	kfree(packet);

	return ret;
}


void usb_free_urb(struct urb *urb)
{
	if (!urb)
		return;

	kfree(urb);

	wake_up(&lx_emul_urb_wait);
}
