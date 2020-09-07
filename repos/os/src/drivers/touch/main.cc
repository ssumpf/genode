/**
 * \brief  Synaptic touch input
 * \author Sebastian Sumpf
 * \date   2020-09-03
 */

/*
 * Copyright (C) 2020 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <base/attached_io_mem_dataspace.h>
#include <base/component.h>
#include <base/env.h>

#include <drivers/defs/imx8q_evk.h>
#include <gpio_session/connection.h>
#include <i2c.h>

using namespace Genode;

enum Gpio_irq { IRQ = 135 };

struct Main
{
	Genode::Env &env;
	Irq_handler               _i2c_irq_handler { env, Imx8::I2C_1_IRQ };
	Attached_io_mem_dataspace _i2c_ds { env, Imx8::I2C_1_BASE, Imx8::I2C_1_SIZE };
	I2c::I2c                  _i2c { (addr_t)_i2c_ds.local_addr<addr_t>(), _i2c_irq_handler };
	Gpio::Connection          _gpio { env, IRQ };
	Irq_session_client        _irq { _gpio.irq_session(Gpio::Session::LOW_LEVEL) };
	Io_signal_handler<Main>   _irq_dispatcher { env.ep(), *this, &Main::_handle_irq };
	uint8_t                   _buf[10];

	void _handle_irq()
	{
		static unsigned long c = 0;
		Genode::log("IRQ", c++);

		/* read device IRQ */
		_buf[0] = 4;
		_i2c.send(0x20, _buf, 1);
		_i2c.recv(0x20, _buf, 2);
		Genode::log("IRQ read: ", Genode::Hex(_buf[0]), Genode::Hex(_buf[1]));
		_irq.ack_irq();
	}

	Main(Genode::Env &env) : env(env)
	{
		log("Driver constructed");
		uint8_t buf[21] { };

		/* set page 0 */
		buf[0] = 0xff;
		buf[1] = 0;
		_i2c.send(0x20, buf, 2);

		/* synaptics_rmi4_query_device:2660 addr: 42 (0x2a) query size: 21 */
		buf[0] = 0x2a;
		_i2c.send(0x20, buf, 1);
		_i2c.recv(0x20, buf, 21);
		log("RCV finished");
		buf[16] = 0;
		log("buf: ", (char const *)(&buf[11]));

		/*enable interrupt */
		buf[0] = 0xf;
		buf[1] = 0x16;
		_i2c.send(0x20, buf, 2);

		/* set configured */
		buf[0] = 0xe;
		buf[1] = 0x84;
		_i2c.send(0x20, buf, 2);

		/* GPIO touchscreen handling */
		_gpio.direction(Gpio::Session::IN);

		_irq.sigh(_irq_dispatcher);
		_irq.ack_irq();
	}
};


void Component::construct(Genode::Env &env) { static Main main(env); }
