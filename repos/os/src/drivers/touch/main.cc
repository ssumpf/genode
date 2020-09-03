/**
 * \brief  Input driver front-end
 * \author Norman Feske
 * \author Christian Helmuth
 * \author Stefan Kalkowski
 * \date   2006-08-30
 */

/*
 * Copyright (C) 2006-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <base/attached_io_mem_dataspace.h>
#include <base/component.h>
#include <base/env.h>

#include <drivers/defs/imx8q_evk.h>
#include <i2c.h>

using namespace Genode;

struct Main
{
	Genode::Env &env;
	Irq_handler               _i2c_irq_handler { env, Imx8::I2C_1_IRQ };
	Attached_io_mem_dataspace _i2c_ds { env, Imx8::I2C_1_BASE, Imx8::I2C_1_SIZE };
	I2c::I2c                  _i2c { (addr_t)_i2c_ds.local_addr<addr_t>(), _i2c_irq_handler };

	Main(Genode::Env &env) : env(env)
	{
		log("Driver constructed");
	}
};


void Component::construct(Genode::Env &env) { static Main main(env); }
