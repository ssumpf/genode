#include <terminal.h>
#include <lx_emul.h>

#include <lx_emul/extern_c_begin.h>
#include <linux/usb.h>
#include <lx_emul/extern_c_end.h>

using namespace Terminal;

void Session_component::_run_wdm_task(void *args)
{
	Genode::log("WDM task started");
	usb_class_driver *driver = static_cast<usb_class_driver *>(args);

	int err = -1;
	struct file file { };

	if ((err = driver->fops->open(nullptr, &file))) {
		Genode::error("Could not open WDM device: ", err);
		return;
	}

	Genode::log("WDM device successfully opened");
	while (1) {
		Lx::scheduler().current()->block_and_schedule();
	}
}
