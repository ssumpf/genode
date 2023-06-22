/*
 * \brief  Linux emulation environment: input event sink
 * \author Christian Helmuth
 * \date   2022-06-23
 *
 * This implementation is derived from drivers/input/evbug.c and
 * drivers/input/evdev.c.
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>
#include <lx_emul/event.h>
#include <genode_c_api/event.h>

#include <linux/slab.h>
#include <linux/module.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/device.h>


struct multi_touch
{
	unsigned long width;
	unsigned long height;
	bool          multi_touch;
};

struct evdev
{
	struct genode_event *event;
	struct input_handle  handle;
};

void * (*genode_multi_touch_config)(void);


static bool _multi_touch(void)
{
	if (genode_multi_touch_config)
		return ((struct multi_touch *)genode_multi_touch_config())->multi_touch;
	return false;
}


static void submit_rel_motion(struct genode_event_submit *submit,
                              unsigned code, int value)
{
	switch (code) {
	case REL_X:      submit->rel_motion(submit, value, 0); break;
	case REL_Y:      submit->rel_motion(submit, 0, value); break;

	case REL_HWHEEL: submit->wheel(submit, value, 0);      break;
	case REL_WHEEL:  submit->wheel(submit, 0, value);      break;

	/* skip for now because of large values */
	case REL_HWHEEL_HI_RES: break;
	case REL_WHEEL_HI_RES:  break;

	default:
		printk("Unsupported relative motion event code=%d dropped\n", code);
	}
}


static void submit_key(struct genode_event_submit *submit,
                       unsigned code, bool press)
{
	/* map BTN_TOUCH to BTN_LEFT */
	if (code == BTN_TOUCH) code = BTN_LEFT;

	if (press)
		submit->press(submit, lx_emul_event_keycode(code));
	else
		submit->release(submit, lx_emul_event_keycode(code));
}


/*
 * absolute/multi-touch handling
 */

static struct slot
{
	int id;;   /* current tracking id  */
	int x;     /* last reported x axis */
	int y;     /* last reported y axis */
	int event; /* last reported ABS_MT_ event */
} slots[16];

static int slot = 0; /* store current input slot */

static bool transform(struct input_dev *dev, int *x, int *y)
{
	unsigned long screen_x = 0;
	unsigned long screen_y = 0;
	int const min_x_dev  = input_abs_get_min(dev, ABS_X);
	int const min_y_dev  = input_abs_get_min(dev, ABS_Y);
	int const max_x_dev  = input_abs_get_max(dev, ABS_X);
	int const max_y_dev  = input_abs_get_max(dev, ABS_Y);
	int const max_y_norm = max_y_dev - min_y_dev;
	int const max_x_norm = max_x_dev - min_x_dev;

	if (genode_multi_touch_config) {
		struct multi_touch *m = genode_multi_touch_config();
		screen_x = m->width;
		screen_y = m->height;
	}

	if (!screen_x || !screen_y) return true;

	if (!max_x_norm   || !max_y_norm   ||
	    *x < min_x_dev || *y < min_y_dev || *x > max_x_dev || *y > max_y_dev) {
		printk("ignore input source with coordinates out of range\n");
		return false;
	}

	*x = screen_x * (*x - min_x_dev) / (max_x_norm);
	*y = screen_y * (*y - min_y_dev) / (max_y_norm);

	return true;
}


static void handle_mt_tracking_id(struct genode_event_submit *submit,
                                  struct input_dev *dev, int value)
{
	int x, y;

	if (value != -1) {
		if (slots[slot].id != -1)
			printk("old tracking id in use and got new one\n");

		slots[slot].id = value;
		return;
	}

	/* send end of slot usage event for clients */
	x = slots[slot].x < 0 ? 0 : slots[slot].x;
	y = slots[slot].y < 0 ? 0 : slots[slot].y;

	if (!transform(dev, &x, &y)) return;

	submit->touch_release(submit, slot);

	slots[slot].event = slots[slot].x = slots[slot].y = -1;
	slots[slot].id = value;
}


static void handle_mt_slot(int value)
{
	if ((unsigned)value >= sizeof(slots) / sizeof(slots[0])) {
		printk("drop multi-touch slot id %d\n", value);
		return;
	}

	slot = value;
}


enum Axis { AXIS_X, AXIS_Y };

static void handle_absolute_axis(struct genode_event_submit *submit,
                                 struct input_dev *dev,
                                 unsigned code, int value,
                                 enum Axis axis)
{
	enum Type { MOTION, TOUCH };
	int x, y;
	enum Type type = MOTION;

	slots[slot].event = code;

	switch (axis) {
	case AXIS_X:
		type          = code == ABS_X ? MOTION : TOUCH;
		slots[slot].x = value;
		break;
	case AXIS_Y:
		type          = code == ABS_Y ? MOTION : TOUCH;
		slots[slot].y = value;
		break;
	}

	x = slots[slot].x;
	y = slots[slot].y;

	if (x == -1 || y == -1) return;

	if (!transform(dev, &x, &y)) return;

	if (type == MOTION)
		submit->abs_motion(submit, x, y);
	else if (type == TOUCH) {
		struct genode_event_touch_args args = {
			.finger =  slot,
			.xpos   =  x,
			.ypos   =  y
		};
		submit->touch(submit, &args);
	}
}


static void submit_abs_motion(struct genode_event_submit *submit,
                              struct input_dev *dev,
                              unsigned code, int value)
{
	switch (code) {
	case ABS_WHEEL:
		submit->wheel(submit, 0, value);
		return;

	case ABS_X:
		if (dev->mt && _multi_touch()) return;
		handle_absolute_axis(submit, dev, code, value, AXIS_X);
		return;

	case ABS_MT_POSITION_X:
		if (!_multi_touch()) return;
		handle_absolute_axis(submit, dev, code, value, AXIS_X);
		return;

	case ABS_Y:
		if (dev->mt && _multi_touch()) return;
		handle_absolute_axis(submit, dev, code, value, AXIS_Y);
		return;

	case ABS_MT_POSITION_Y:
		if (!_multi_touch()) return;
		handle_absolute_axis(submit, dev, code, value, AXIS_Y);
		return;

	case ABS_MT_TRACKING_ID:
		if (!_multi_touch()) return;
		handle_mt_tracking_id(submit, dev, value);
		return;

	case ABS_MT_SLOT:
		if (!_multi_touch()) return;
		handle_mt_slot(value);
		return;

	case ABS_MT_TOUCH_MAJOR:
	case ABS_MT_TOUCH_MINOR:
	case ABS_MT_ORIENTATION:
	case ABS_MT_TOOL_TYPE:
	case ABS_MT_BLOB_ID:
	case ABS_MT_PRESSURE:
	case ABS_MT_DISTANCE:
	case ABS_MT_TOOL_X:
	case ABS_MT_TOOL_Y:
		/* ignore unused multi-touch events */
		return;

	default:
		printk("unknown absolute event code %u not handled\n", code);
		return;
	}
}

struct genode_event_generator_ctx
{
	struct evdev *evdev;
	struct input_value const *values;
	unsigned count;
};


static void evdev_event_generator(struct genode_event_generator_ctx *ctx,
                                  struct genode_event_submit *submit)
{
	int i;
	struct input_dev *dev = ctx->evdev->handle.dev;

	for (i = 0; i < ctx->count; i++) {
		unsigned const type  = ctx->values[i].type;
		unsigned const code  = ctx->values[i].code;
		unsigned const value = ctx->values[i].value;

		/* filter input_repeat_key() */
		if ((type == EV_KEY) && (value > 1)) continue;

		/* filter EV_SYN and EV_MSC */
		if (type == EV_SYN || type == EV_MSC) continue;

		switch (type) {
		case EV_KEY: if (!dev->mt || !_multi_touch()) submit_key(submit, code, value);  break;
		case EV_REL: submit_rel_motion(submit, code, value);      break;
		case EV_ABS: submit_abs_motion(submit, dev, code, value); break;

		default:
			printk("Unsupported Event[%u/%u] device=%s, type=%d, code=%d, value=%d dropped\n",
			       i + 1, ctx->count, dev_name(&ctx->evdev->handle.dev->dev), type, code, value);
			continue;
		}
	}
}


static void evdev_events(struct input_handle *handle,
                         struct input_value const *values, unsigned int count)
{
	struct evdev *evdev = handle->private;

	struct genode_event_generator_ctx ctx = {
		.evdev = evdev, .values = values, .count = count };

	genode_event_generate(evdev->event, &evdev_event_generator, &ctx);
}


static void evdev_event(struct input_handle *handle,
                        unsigned int type, unsigned int code, int value)
{
	struct input_value vals[] = { { type, code, value } };

	evdev_events(handle, vals, 1);
}


static int evdev_connect(struct input_handler *handler, struct input_dev *dev,
                         const struct input_device_id *id)
{
	struct evdev *evdev;
	int error;
	struct genode_event_args args = { .label = dev->name };

	evdev = kzalloc(sizeof(*evdev), GFP_KERNEL);
	if (!evdev)
		return -ENOMEM;

	evdev->event = genode_event_create(&args);

	evdev->handle.private = evdev;
	evdev->handle.dev     = dev;
	evdev->handle.handler = handler;
	evdev->handle.name    = dev->name;

	error = input_register_handle(&evdev->handle);
	if (error)
		goto err_free_handle;

	error = input_open_device(&evdev->handle);
	if (error)
		goto err_unregister_handle;

	printk("Connected device: %s (%s at %s)\n",
	       dev_name(&dev->dev),
	       dev->name ?: "unknown",
	       dev->phys ?: "unknown");

	return 0;

err_unregister_handle:
	input_unregister_handle(&evdev->handle);

err_free_handle:
	genode_event_destroy(evdev->event);
	kfree(evdev);
	return error;
}


static void evdev_disconnect(struct input_handle *handle)
{
	struct evdev *evdev = handle->private;

	printk("Disconnected device: %s\n", dev_name(&handle->dev->dev));

	input_close_device(handle);
	input_unregister_handle(handle);
	genode_event_destroy(evdev->event);
	kfree(evdev);
}


static const struct input_device_id evdev_ids[] = {
	{ .driver_info = 1 }, /* Matches all devices */
	{ },                  /* Terminating zero entry */
};


MODULE_DEVICE_TABLE(input, evdev_ids);

static struct input_handler evdev_handler = {
	.event      = evdev_event,
	.events     = evdev_events,
	.connect    = evdev_connect,
	.disconnect = evdev_disconnect,
	.name       = "evdev",
	.id_table   = evdev_ids,
};


static int __init evdev_init(void)
{
	int i;

	for (i = 0; i < 16; i++)
		slots[i].id = slots[i].x = slots[i].y = slots[i].event = -1;

	return input_register_handler(&evdev_handler);
}


static void __exit evdev_exit(void)
{
	input_unregister_handler(&evdev_handler);
}


/**
 * Let's hook into the evdev initcall, so we do not need to register
 * an additional one
 */
module_init(evdev_init);
module_exit(evdev_exit);
