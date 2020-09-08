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
#include <event_session/connection.h>
#include <gpio_session/connection.h>
#include <i2c.h>

using namespace Genode;

enum Gpio_irq { IRQ = 135 };

struct Finger_data
{
	uint8_t status;
	uint8_t x_lsb;
	uint8_t x_msb;
	uint8_t y_lsb;
	uint8_t y_msb;
	uint8_t wx;
	uint8_t wy;

	unsigned x() const
	{
		return 1080 - ((x_msb << 8) | x_lsb);
	}

	unsigned y() const
	{
		return 1920 - ((y_msb << 8) | y_lsb);
	}

	void dump() const
	{
		log("status: ", Hex(status),
		    " x_lsb: ", x_lsb, " x_msb: ", x_msb,
		    " y_lsb: ", y_lsb, " y_msb: ", y_msb,
		    " wx: ", wx, " wy: ", wy,
		    " x: ", x(),
		    " y: ", y());
	}
};

struct Main
{
	enum { FINGERS = 5, I2C_ADDR = 0x20 };

	Genode::Env &env;
	Irq_handler               _i2c_irq_handler { env, Imx8::I2C_1_IRQ };
	Attached_io_mem_dataspace _i2c_ds { env, Imx8::I2C_1_BASE, Imx8::I2C_1_SIZE };
	I2c::I2c                  _i2c { (addr_t)_i2c_ds.local_addr<addr_t>(), _i2c_irq_handler };
	Gpio::Connection          _gpio { env, IRQ };
	Irq_session_client        _irq { _gpio.irq_session(Gpio::Session::LOW_LEVEL) };
	Io_signal_handler<Main>   _irq_dispatcher { env.ep(), *this, &Main::_handle_irq };
	Event::Connection         _event { env };
	uint8_t                   _buf[10];
	bool                      _button[FINGERS] { };

	void _handle_event(Event::Session_client::Batch &batch)
	{
		/* retrieve status */
		Finger_data fingers[FINGERS];
		_buf[0] = 6;
		_i2c.send(I2C_ADDR, _buf, 1);
		_i2c.recv(I2C_ADDR, (uint8_t *)fingers, sizeof(fingers));

		for (int i = 0; i < FINGERS; i++) {
			Finger_data &current = fingers[i];

			Input::Touch_id id { i };

			if (current.status == 0) {
				if (_button[i]) {
					batch.submit(Input::Release{Input::BTN_LEFT});
					batch.submit(Input::Touch_release{id});
					_button[i] = false;
				}
				continue;
			}

			batch.submit(Input::Absolute_motion { (int)current.x(), (int)current.y() });
			batch.submit(Input::Touch { id, (float)current.x(), (float)current.y() });

			if (_button[i] == false) {
				batch.submit(Input::Press { Input::BTN_LEFT });
			}
			_button[i] = true;
		}
	}

	void _handle_irq()
	{
		/* read device IRQ */
		_buf[0] = 4;
		_i2c.send(I2C_ADDR, _buf, 1);
		_i2c.recv(I2C_ADDR, _buf, 2);

		_event.with_batch([&] (Event::Session_client::Batch &batch) {
			_handle_event(batch);
		});

		_irq.ack_irq();
	}

	Main(Genode::Env &env) : env(env)
	{
		/* set page 0 */
		_buf[0] = 0xff;
		_buf[1] = 0;
		_i2c.send(I2C_ADDR, _buf, 2);


		/*enable interrupt */
		_buf[0] = 0xf;
		_buf[1] = 0x16;
		_i2c.send(I2C_ADDR, _buf, 2);

		/* set configured */
		_buf[0] = 0xe;
		_buf[1] = 0x84;
		_i2c.send(I2C_ADDR, _buf, 2);

		/* GPIO touchscreen handling */
		_gpio.direction(Gpio::Session::IN);

		_irq.sigh(_irq_dispatcher);
		_irq.ack_irq();
	}
};


void Component::construct(Genode::Env &env) { static Main main(env); }
