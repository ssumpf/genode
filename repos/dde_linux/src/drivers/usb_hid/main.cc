#include <base/attached_rom_dataspace.h>
#include <base/component.h>
#include <base/env.h>
#include <base/registry.h>

#include <lx_emul/init.h>
#include <lx_emul/task.h>
#include <lx_kit/env.h>

/* C-interface */
#include <usb_hid.h>

using namespace Genode;


struct Task_handler
{
	task_struct                 *task;
	Signal_handler<Task_handler> handler;
	bool                         handling_signal { false };
	bool                         running         { true  };

	/*
	 * If the task is currently executing and the signal handler
	 * is called again via 'block_and_schedule()', we need to
	 * keep this information, so the task does not block at the
	 * end when a new signal already occurred.
	 *
	 * Initialized as true for the initial run of the task.
	 */
	bool _signal_pending { true };

	void handle_signal()
	{
		_signal_pending = true;
		lx_emul_task_unblock(task);
		handling_signal = true;
		Lx_kit::env().scheduler.schedule();
		handling_signal = false;
	}

	bool signal_pending()
	{
		bool ret = _signal_pending;
		_signal_pending = false;
		return ret;
	}

	void block_and_schedule()
	{
		lx_emul_task_schedule(true);
	}

	void destroy_task()
	{
		running = false;
		lx_emul_task_unblock(task);
		Lx_kit::env().scheduler.schedule();
	}

	Task_handler(Entrypoint & ep, task_struct *task)
	: task(task), handler(ep, *this, &Task_handler::handle_signal) { }

	/* non-copyable */
	Task_handler(const Task_handler&) = delete;
	Task_handler & operator=(const Task_handler&) = delete;
};


struct Device : Registry<Device>::Element
{
	using Label = String<64>;

	Env   &env;
	Label  label;

	/*
	 * Dedicated allocator per device to notice dangling
	 * allocations on device destruction.
	 */
	Allocator_avl alloc { &Lx_kit::env().heap };

	task_struct *state_task { lx_user_new_usb_task(state_task_entry, this) };
	task_struct *urb_task   { lx_user_new_usb_task(urb_task_entry, this)   };

	Task_handler state_task_handler { env.ep(), state_task };
	Task_handler urb_task_handler   { env.ep(), urb_task   };

	genode_usb_client_handle_t usb_handle {
		genode_usb_client_create(genode_env_ptr(env),
		                         genode_allocator_ptr(Lx_kit::env().heap),
		                         genode_range_allocator_ptr(alloc),
		                         label.string(),
		                         genode_signal_handler_ptr(state_task_handler.handler)) };

	bool updated    { true };
	bool registered { false };
	unsigned long udev { 0 };

	Device(Env &env, Registry<Device> &registry, Label label)
	:
		Registry<Device>::Element(registry, *this),
		env(env), label(label)
	{
		genode_usb_client_sigh_ack_avail(usb_handle,
		                                 genode_signal_handler_ptr(urb_task_handler.handler));
	}

	~Device()
	{
		state_task_handler.destroy_task();
		urb_task_handler.destroy_task();
	}

	/* non-copyable */
	Device(const Device&) = delete;
	Device & operator=(const Device&) = delete;

	void register_device()
	{
		warning("register device");
		registered = true;
		udev = lx_usb_register_device(usb_handle);
		if (!udev) return;
	}

	void unregister_device() { }
	bool deinit() { return false; }

	/**********
	 ** Task **
	 **********/

	static int state_task_entry(void *arg)
	{
		Device &device = *reinterpret_cast<Device *>(arg);
		Genode::warning("State task");

		while (device.state_task_handler.running) {
			while (device.state_task_handler.signal_pending()) {
				if (genode_usb_client_plugged(device.usb_handle) && !device.registered)
					device.register_device();

				if (!genode_usb_client_plugged(device.usb_handle) && device.registered)
					device.unregister_device();
			}
			device.state_task_handler.block_and_schedule();
		}
		lx_user_destroy_usb_task(device.state_task_handler.task);
		return 0;
	}

	static int urb_task_entry(void *arg)
	{
		Device &device = *reinterpret_cast<Device *>(arg);

		while (device.urb_task_handler.running) {
			Genode::warning("URB task");
			if (device.registered) {
				warning("call completions");
				genode_usb_client_execute_completions(device.usb_handle);
			}

			device.urb_task_handler.block_and_schedule();
		}
		lx_user_destroy_usb_task(device.urb_task_handler.task);
		return 0;
	}
};


struct Driver
{
	Env &env;

	Task_handler task_handler;

	Heap &heap { Lx_kit::env().heap };

	/* multi-touch */
	unsigned long screen_x { 0 };
	unsigned long screen_y { 0 };
	bool          multi_touch { false };
	bool          use_report  { false };

	Attached_rom_dataspace report_rom { env, "report" };
	Attached_rom_dataspace config_rom { env, "config" };

	Registry<Device> devices { };

	Driver(Env &env, task_struct *task)
	: env(env), task_handler(env.ep(), task)
	{
		report_rom.sigh(task_handler.handler);

		try {
			Xml_node config = config_rom.xml();
			use_report      = config.attribute_value("use_report", false);
			multi_touch     = config.attribute_value("multitouch", false);
			config.attribute("width").value(screen_x);
			config.attribute("height").value(screen_y);
		} catch(...) { }

		if (use_report)
			warning("use compatibility mode: ",
			        "will claim all HID devices from USB report");

		log("Configured HID screen with ",
		    screen_x, "x", screen_y,
		    " (multitouch=", multi_touch ? "true" : "false", ")");
	}

	void scan_report()
	{
		report_rom.update();

		devices.for_each([&] (Device & d) { d.updated = false; });

		try {
			Xml_node report_node = report_rom.xml();
			report_node.for_each_sub_node([&] (Xml_node & dev_node)
			{
				unsigned long c = 0;
				dev_node.attribute("class").value(c);
				if (c != 0x3 /* USB_CLASS_HID */) return;

				Device::Label label;
				dev_node.attribute("label").value(label);

				bool found = false;

				devices.for_each([&] (Device & d) {
					if (d.label == label) d.updated = found = true; });

				if (!found) {
					error("NEW device: ", label);
					new (heap) Device(env, devices, label);
				}
			});
		} catch(...) {
			error("Error parsing USB devices report");
			throw;
		};

		devices.for_each([&] (Device & d) {
			if (!d.updated && d.deinit())
				destroy(heap, &d);
		});
	}
};


void Component::construct(Env & env)
{
	Lx_kit::initialize(env);
	env.exec_static_constructors();
	lx_emul_start_kernel(nullptr);
}


/**********
 ** Task **
 **********/

int lx_user_main_task(void *data)
{
	task_struct *task = *static_cast<task_struct **>(data);
	error("Main task: ", task);
	static Driver driver { Lx_kit::env().env, task };

	for (;;) {
		while (driver.task_handler.signal_pending()) {
			if (!driver.use_report)
				static Device dev(driver.env, driver.devices, Device::Label(""));
			else
				driver.scan_report();
		}
		driver.task_handler.block_and_schedule();
	}
	return 0;
}
