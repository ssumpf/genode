/**
 * \brief  Linux Kernel eulation platform device functions
 * \author Stefan Kalkowski
 * \date   2021-03-16
 */

#include <lx_emul/debug.h>
#include <linux/platform_device.h>

int __platform_driver_register(struct platform_driver * drv,
                               struct module          * owner)
{
	lx_emul_trace(__func__);

	return 0;
}
