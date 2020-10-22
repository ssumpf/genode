#include <terminal.h>
#include <lx_emul.h>

#include <lx_emul/extern_c_begin.h>
#include <linux/usb.h>
#include <lx_emul/extern_c_end.h>

using namespace Terminal;


Session_component::Session_component(Genode::Env &env,
                  Genode::size_t io_buffer_size,
                  usb_class_driver *class_driver)
:
	_io_buffer(env.ram(), env.rm(), io_buffer_size),
	_io_buffer_size(io_buffer_size),
	_class_driver(class_driver)
{
	if (class_driver == nullptr) {
		Genode::error("No class driver for terminal");
		throw Genode::Service_denied();
	}

	Lx::scheduler().schedule();
}

void Session_component::_run_wdm_device(void *args)
{
	Genode::log("WDM task device started");

	Session_component *session = static_cast<Session_component *>(args);

	usb_class_driver *driver = session->_class_driver;

	int err = -1;
	struct file file { };

	if ((err = driver->fops->open(nullptr, &file))) {
		Genode::error("Could not open WDM device: ", err);
		return;
	}

	session->_wdm_device = file.private_data;
	Genode::log("device opened");
	Lx::scheduler().current()->block_and_schedule();
	//XXX: close

}


void Session_component::_run_wdm_write(void *args)
{
	Lx::scheduler().current()->block_and_schedule();

	Genode::log("WDM task wite started");
	Session_component *session = static_cast<Session_component *>(args);

	usb_class_driver *driver = session->_class_driver;

	struct file file { .private_data = session->_wdm_device };

	Genode::log("WRITE: ", session->_wdm_device);

	while (1) {
		Genode::log("WDM write unblocked");
		ssize_t length = driver->fops->write(&file, session->buffer(),
		                                     session->_data_avail, nullptr);
		Genode::log("WDM write ", length, " bytes");
		if (length < 0) {
			Genode::error("WDM write error: ", length);
		}

		session->_schedule_read();
		Lx::scheduler().current()->block_and_schedule();
	}
}


void Session_component::_run_wdm_read(void *args)
{
	Lx::scheduler().current()->block_and_schedule();
	Genode::log("WDM task read started");
	Session_component *session = static_cast<Session_component *>(args);

	usb_class_driver *driver = session->_class_driver;

	struct file file { .private_data = session->_wdm_device };

	while (1) {
		Genode::log("WDM read unblocked");
		ssize_t length = driver->fops->read(&file, session->buffer(), 0x1000, nullptr);
		Genode::log("WDM read ", length, " bytes");
		if (length > 0) {
			session->_data_avail = length;
			session->signal_data_avail();
		}
		Lx::scheduler().current()->block_and_schedule();
	}
}
