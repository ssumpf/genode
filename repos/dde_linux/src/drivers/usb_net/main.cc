
#include <base/attached_rom_dataspace.h>
#include <base/component.h>
#include <base/env.h>

#include <lx_kit/env.h>
#include <lx_emul/task.h>
#include <lx_emul/init.h>

/* C-interface */
#include <usb_net.h>

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

	Task_handler(Entrypoint & ep, task_struct *task)
	: task(task), handler(ep, *this, &Task_handler::handle_signal) { }

	/* non-copyable */
	Task_handler(const Task_handler&) = delete;
	Task_handler & operator=(const Task_handler&) = delete;
};


struct Device
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

	bool registered { false };

	void *lx_device_handle { nullptr };

	Device(Env &env, Label label)
	:
		env(env), label(label)
	{
		genode_usb_client_sigh_ack_avail(usb_handle,
		                                 genode_signal_handler_ptr(urb_task_handler.handler));
	}

	/* non-copyable */
	Device(const Device&) = delete;
	Device & operator=(const Device&) = delete;

	void register_device()
	{
		error("REGISTER");

		registered = true;
		lx_device_handle = lx_emul_usb_client_register_device(usb_handle, label.string());
		if (!lx_device_handle) {
			registered = false;
			return;
		}

	}

	void unregister_device()
	{
#if 0
		lx_emul_usb_client_unregister_device(usb_handle, lx_device_handle);
		registered = false;
#endif
	}

	/**********
	 ** Task **
	 **********/

	static int state_task_entry(void *arg)
	{
		Device &device = *reinterpret_cast<Device *>(arg);

		while (device.state_task_handler.running) {
			while (device.state_task_handler.signal_pending()) {
				if (genode_usb_client_plugged(device.usb_handle) && !device.registered)
					device.register_device();

				if (!genode_usb_client_plugged(device.usb_handle) && device.registered)
					device.unregister_device();
			}
			device.state_task_handler.block_and_schedule();
		}

		while (true)
			device.state_task_handler.block_and_schedule();

		return 0;
	}

	static int urb_task_entry(void *arg)
	{
		Device &device = *reinterpret_cast<Device *>(arg);

		while (device.urb_task_handler.running) {
			if (device.registered)
				genode_usb_client_execute_completions(device.usb_handle);

			device.urb_task_handler.block_and_schedule();
		}
		while (true)
			device.state_task_handler.block_and_schedule();

		return 0;
	}
};


void Component::construct(Env & env)
{
	Lx_kit::initialize(env);

	env.exec_static_constructors();

	//genode_event_init(genode_env_ptr(env),
	 //                 genode_allocator_ptr(Lx_kit::env().heap));

	lx_emul_start_kernel(nullptr);
}


/**********
 ** Task **
 **********/

int lx_user_main_task(void *)
{
	/* one device only */
	static Device dev(Lx_kit::env().env, Device::Label(""));

	return 0;
}
