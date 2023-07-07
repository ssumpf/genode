
#include <base/attached_rom_dataspace.h>
#include <base/component.h>
#include <base/env.h>

#include <genode_c_api/uplink.h>
#include <genode_c_api/mac_address_reporter.h>

#include <lx_kit/env.h>
#include <lx_emul/task.h>
#include <lx_emul/init.h>

/* C-interface */
#include <usb_net.h>

using namespace Genode;

extern task_struct *user_task_struct_ptr;

struct Device : private Entrypoint::Io_progress_handler
{
	using Label = String<64>;

	Env   &env;
	Label  label;

	Attached_rom_dataspace config_rom { env, "config" };

	/*
	 * Dedicated allocator per device to notice dangling
	 * allocations on device destruction.
	 */
	Allocator_avl alloc { &Lx_kit::env().heap };

	task_struct *state_task { lx_user_new_usb_task(state_task_entry, this) };
	task_struct *urb_task   { lx_user_new_usb_task(urb_task_entry, this)   };

	Signal_handler<Device> task_state_handler { env.ep(), *this, &Device::handle_task_state };
	Io_signal_handler<Device> urb_handler     { env.ep(), *this, &Device::handle_urb        };

	genode_usb_client_handle_t usb_handle {
		genode_usb_client_create(genode_env_ptr(env),
		                         genode_allocator_ptr(Lx_kit::env().heap),
		                         genode_range_allocator_ptr(alloc),
		                         label.string(),
		                         genode_signal_handler_ptr(task_state_handler)) };

	Signal_handler<Device> nic_handler    { env.ep(), *this, &Device::handle_nic    };
	Signal_handler<Device> config_handler { env.ep(), *this, &Device::handle_config };

	bool registered { false };

	void *lx_device_handle { nullptr };

	Device(Env &env, Label label)
	:
		env(env), label(label)
	{
		genode_usb_client_sigh_ack_avail(usb_handle,
		                                 genode_signal_handler_ptr(urb_handler));

		genode_mac_address_reporter_init(env, Lx_kit::env().heap);

		genode_uplink_init(genode_env_ptr(env),
		                   genode_allocator_ptr(Lx_kit::env().heap),
		                   genode_signal_handler_ptr(nic_handler));

		config_rom.sigh(config_handler);
		handle_config();

		env.ep().register_io_progress_handler(*this);
	}

	/* non-copyable */
	Device(const Device&) = delete;
	Device & operator=(const Device&) = delete;

	void register_device()
	{
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

	void handle_io_progress() override
	{
		genode_uplink_notify_peers();
	}

	void handle_task_state()
	{
		lx_emul_task_unblock(state_task);
		Lx_kit::env().scheduler.schedule();
	}

	void handle_urb()
	{
		lx_emul_task_unblock(urb_task);
		Lx_kit::env().scheduler.schedule();
	}

	void handle_nic()
	{
		if (!user_task_struct_ptr)
			return;

		lx_emul_task_unblock(user_task_struct_ptr);
		Lx_kit::env().scheduler.schedule();
	}

	void handle_config()
	{
		config_rom.update();
		genode_mac_address_reporter_config(config_rom.xml());
	}


	/**********
	 ** Task **
	 **********/

	static int state_task_entry(void *arg)
	{
		Device &device = *reinterpret_cast<Device *>(arg);

		while (true) {
			if (genode_usb_client_plugged(device.usb_handle) && !device.registered)
				device.register_device();

			if (!genode_usb_client_plugged(device.usb_handle) && device.registered)
				device.unregister_device();
			lx_emul_task_schedule(true);
		}

		return 0;
	}

	static int urb_task_entry(void *arg)
	{
		Device &device = *reinterpret_cast<Device *>(arg);

		while (true) {
			if (device.registered) {
				genode_usb_client_execute_completions(device.usb_handle);
			}

			lx_emul_task_schedule(true);
		}

		return 0;
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

int lx_user_main_task(void *)
{
	/* one device only */
	static Device dev(Lx_kit::env().env, Device::Label("usb-nic"));

	return 0;
}
