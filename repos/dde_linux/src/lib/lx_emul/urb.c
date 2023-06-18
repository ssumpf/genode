/*
 * \brief  urb functions
 * \author Stefan Kalkowski
 * \date   2018-08-25
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <linux/usb.h>
#include <usb_client.h>

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


static void usb_control_msg_complete(struct genode_usb_client_request_packet *packet)
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

	genode_usb_client_handle_t handle =
		(genode_usb_client_handle_t)dev->bus->controller;

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
	packet.complete_callback = usb_control_msg_complete;
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


int usb_submit_urb(struct urb *urb, gfp_t mem_flags)
{
	printk("%s:%d\n", __func__, __LINE__);
	while (1) ;
#if 0
	if (!urb->dev->bus || !urb->dev->bus->controller)
		return -ENODEV;

	Urb * u = (Urb *)kzalloc(sizeof(Urb), mem_flags);
	if (!u)
		return 1;

	Usb::Connection &usb = *(Usb::Connection*)(urb->dev->bus->controller);
	for (;;) {
		if (usb.source()->ready_to_submit(1))
			try {
				Genode::construct_at<Urb>(u, usb, *urb);
				break;
			} catch (...) { }

		(void)wait_for_free_urb(msecs_to_jiffies(10000u));
	}

	/*
	 * Self-destruction of the 'Urb' object in its completion function
	 * would not work if the 'Usb' session gets closed before the
	 * completion function was called. So we store the pointer in the
	 * otherwise unused 'hcpriv' member and free it in a following
	 * 'usb_submit_urb()' or 'usb_free_urb()' call.
	 */

	if (urb->hcpriv) {
		Urb *prev_urb = (Urb*)urb->hcpriv;
		prev_urb->~Urb();
		kfree(urb->hcpriv);
	}

	urb->hcpriv = u;

	u->send();
#endif
	return 0;
}


void usb_free_urb(struct urb *urb)
{
	struct genode_usb_client_request_packet *packet;

	if (!urb)
		return;

	/* free genode objects */
	if (urb->hcpriv) {
		packet = (struct genode_usb_client_request_packet *)urb->hcpriv;
		kfree(packet->request.req);
		kfree(packet);
	}

	kfree(urb);

	wake_up(&lx_emul_urb_wait);
}
