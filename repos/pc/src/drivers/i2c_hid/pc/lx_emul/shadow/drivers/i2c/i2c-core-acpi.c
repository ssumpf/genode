/*
 * \brief  Linux emulation environment: I2C ACPI emulation
 * \author Christian Helmuth
 * \date   2022-05-02
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include <lx_emul.h>

#include <linux/i2c.h>


u32 i2c_acpi_find_bus_speed(struct device *dev)
{
	return 400000;
}


int i2c_acpi_get_irq(struct i2c_client *client)
{
	struct acpi_device *adev = ACPI_COMPANION(&client->dev);

	int irq = acpi_dev_gpio_irq_get(adev, 0);
	return irq;
}


void i2c_acpi_register_devices(struct i2c_adapter *adap)
{
	struct i2c_board_info info;
	struct acpi_device *adev;

	memset(&info, 0, sizeof(info));
	info.addr = 0x2c;
	acpi_bus_get_device((acpi_handle)3, &adev);
	info.fwnode = acpi_fwnode_handle(adev);
	strcpy(info.type, "INT34C5:00");
	i2c_new_client_device(adap, &info);
}


static int i2c_acpi_notify(struct notifier_block *nb, unsigned long value, void *arg)
{
	return NOTIFY_OK;
}


struct notifier_block i2c_acpi_notifier = {
	.notifier_call = i2c_acpi_notify,
};
