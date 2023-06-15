#include <base/attached_rom_dataspace.h>
#include <base/component.h>
#include <base/env.h>
#include <base/registry.h>

#include <usb_session/connection.h>

#include <lx_emul/init.h>
#include <lx_kit/env.h>
#include <lx_user/init.h>

/* C-interface */
#include <usb_hid.h>

using namespace Genode;


struct Task
{
	Lx_kit::Task          task;
	Signal_handler<Task>  handler;
	bool                  handling_signal { false };

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
		task.unblock();
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
		task.block();
		task.schedule();
	}

	template <typename... ARGS>
	Task(Entrypoint & ep, int (*func)(void*), void *data, char const *name)
	: task(func, data, nullptr, -1, name, Lx_kit::env().scheduler,
	       Lx_kit::Task::NORMAL),
	  handler(ep, *this, &Task::handle_signal) {}
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

	Task state_task { env.ep(), state_task_entry, this, "state_task" };
	Task urb_task   { env.ep(), urb_task_entry  , this, "urb_task" };

	Usb::Connection usb { env, &alloc, label.string(),
	                      512 * 1024, state_task.handler };

	genode_usb_device udev_handle { 0 };
	bool          updated     { true };

	Device(Env &env, Registry<Device> &registry, Label label)
	:
		Registry<Device>::Element(registry, *this),
		env(env), label(label)
	{
		usb.tx_channel()->sigh_ack_avail(urb_task.handler);
	}

	~Device() { }

	void register_device()
	{
		warning("register device");

		if (udev_handle) {
			error("device already registered!");
			return;
		}

		Usb::Device_descriptor dev_desc;
		Usb::Config_descriptor config_desc;
		usb.config_descriptor(&dev_desc, &config_desc);

		udev_handle = genode_register_device(&dev_desc, &usb, dev_desc.num,
		                                     dev_desc.speed);
		if (!udev_handle)
			error("could not resgister device ", label);
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
		for (;;) {
			while (device.state_task.signal_pending()) {
				if (device.usb.plugged() && !device.udev_handle)
					device.register_device();

				if (!device.usb.plugged() && device.udev_handle)
					device.unregister_device();
			}
			device.state_task.block_and_schedule();
		}
		return 0;
	}

	static int urb_task_entry(void *arg)
	{
		Device &device = *reinterpret_cast<Device *>(arg);
		Genode::warning("URB task");
		device.urb_task.block_and_schedule();
		return 0;
	}
};


struct Driver
{
	Env &env;

	Heap &heap { Lx_kit::env().heap };

	/* multi-touch */
	unsigned long screen_x { 0 };
	unsigned long screen_y { 0 };
	bool          multi_touch { false };

	Task main_task { env.ep(), main_task_entry, this, "main_task" };

	Attached_rom_dataspace report_rom { env, "report" };
	Attached_rom_dataspace config_rom { env, "config" };

	Registry<Device> devices { };

	Driver(Env &env) : env(env)
	{
		report_rom.sigh(main_task.handler);
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
		};

		devices.for_each([&] (Device & d) {
			if (!d.updated && d.deinit())
				destroy(heap, &d);
		});
	}

	/**********
	 ** Task **
	 **********/

	static int main_task_entry(void *data)
	{
		Driver &driver = *reinterpret_cast<Driver *>(data);

		bool use_report = false;
		try {
			Xml_node config    = driver.config_rom.xml();
			use_report         = config.attribute_value("use_report", false);
			driver.multi_touch = config.attribute_value("multitouch", false);
			config.attribute("width").value(driver.screen_x);
			config.attribute("height").value(driver.screen_y);
		} catch(...) { }

		if (use_report)
			warning("use compatibility mode: ",
			        "will claim all HID devices from USB report");

		log("Configured HID screen with ",
		    driver.screen_x, "x", driver.screen_y,
		    " (multitouch=", driver.multi_touch ? "true" : "false", ")");

		for (;;) {
			while (driver.main_task.signal_pending()) {
				if (!use_report)
					static Device dev(driver.env, driver.devices, Device::Label(""));
				else
					driver.scan_report();
			}
			driver.main_task.block_and_schedule();
		}
		return 0;
	}
};


void lx_user_init()
{
	static Driver driver(Lx_kit::env().env);
}

void Component::construct(Env & env)
{
	Lx_kit::initialize(env);
	env.exec_static_constructors();
	lx_emul_start_kernel(nullptr);
}

