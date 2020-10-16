#include <terminal.h>
#include <lx_emul.h>

#include <lx_emul/extern_c_begin.h>
#include <linux/usb.h>
#include <lx_emul/extern_c_end.h>

using namespace Terminal;

void Session_component::_run_wdm_task(void *args)
{
	Genode::log("WDM task started");
	Session_component *session = static_cast<Session_component *>(args);

	usb_class_driver *driver = session->_class_driver;

	int err = -1;
	struct file file { };

	if ((err = driver->fops->open(nullptr, &file))) {
		Genode::error("Could not open WDM device: ", err);
		return;
	}

	Genode::log("WDM device successfully opened");
	while (1) {
		Lx::scheduler().current()->block_and_schedule();
		Genode::log("WDM unblocked");

		ssize_t length = driver->fops->write(&file, session->buffer(),
		                                     session->_data_avail, nullptr);
		session->_data_avail = 0;
		if (length < 0) {
			Genode::error("WDM write error: ", length);
			continue;
		}

		Genode::log("WDM try read");
		length = driver->fops->read(&file, session->buffer(), 0x1000, nullptr);
		if (length <= 0) continue;

		session->_data_avail = length;
		session->signal_data_avail();
	}
}
