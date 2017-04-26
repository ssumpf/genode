/*
 * \brief  Gpu session test
 * \author Josef Soentegn
 * \date   2017-05-02
 */

/*
 * Copyright (C) 2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <base/attached_rom_dataspace.h>
#include <base/component.h>
#include <base/heap.h>
#include <base/log.h>
#include <gpu_session/connection.h>
#include <util/retry.h>

/* XXX */
#include <commands.h>


#if 0
struct Test_sequence_number
{
	void _handle_completion()
	{
		Genode::log(__func__, ": ", _cnt);
	}

	Genode::Signal_handler<Main> _completion_handler {
		_env.ep(), *this, &Main::_handle_completion };

	Test_sequence_number(Gpu::Connection &gpu, uint32_t *cmdbuf)
	{
		/*
		 * IHD-OS-BDW-Vol 2d-11.15 p. 199 ff.
		 *
		 * HWS page layout dword 48 - 1023 for driver usage
		 */
		{
			enum { CMD_NUM = 8, HWS_DATA = 0xc0, };
			Genode::uint32_t cmd[8] = {};
			Igd::Pipe_control pc(4);
			cmd[0] = pc.value;
			cmd[1] = (1u<<24 /* dest address type */|1u<<20 /* CS STALL */|1u<<14 /* post sync op */);
			cmd[2] = (rcs.hw_status_page() + HWS_DATA) & 0xffffffff;
			cmd[3] = 0; /* upper addr 0 */
			cmd[4] = seqno & 0xffffffff;
			cmd[5] = seqno >> 32;
			Igd::Mi_user_interrupt ui;
			cmd[6] = ui.value;
			cmd[7] = 0; /* MI_NOOP */

			for (size_t i = 0; i < CMD_NUM; i++) {
				cmdbuf[i] = cmd[i];
			}
		}

		_gpu.execute(8);
	}
};
#endif


struct Main
{
	Genode::Env                    &_env;
	Genode::Attached_rom_dataspace  _config_rom { _env, "config" };

	Gpu::Connection             _gpu { _env };
	Genode::Attached_dataspace  _gpu_command_buffer { _env.rm(), _gpu.command_buffer() };
	Igd::uint32_t              *_command_buffer { _gpu_command_buffer.local_addr<Igd::uint32_t>() };

	Genode::Dataspace_capability _buffer;
	Genode::Dataspace_capability _map_buffer;

	unsigned _limit { 0 };
	unsigned _cnt   { 0 };

	void _try_execute()
	{
		if (_cnt++ < _limit) {
			Genode::log(__func__, ": ", _cnt);
			_command_buffer[7] = 0x1000000;
			_gpu.execute(10);
		} else {
			_env.parent().exit(0);
		}
	}

	void _handle_completion()
	{
		Genode::log(__func__, ": ", _cnt);

		// _try_execute();
	}

	Genode::Signal_handler<Main> _completion_handler {
		_env.ep(), *this, &Main::_handle_completion };

	Genode::Dataspace_capability _alloc_buffer(Genode::size_t size)
	{
		enum { RETRY_COUNT = 2, };
		Genode::size_t donate = size;
		return Genode::retry<Gpu::Session::Out_of_ram>(
			[&] () { return _gpu.alloc_buffer(size); },
			[&] () {
				_gpu.upgrade_ram(donate);
				donate /= 4;
			},
			RETRY_COUNT
		);
	}

	Main(Genode::Env &env) : _env(env)
	{
		_limit = _config_rom.xml().attribute_value("limit", 1UL);

		_gpu.completion_sigh(_completion_handler);

		/* (un-)map a 1 MiB large buffer */
		{
			_buffer = _alloc_buffer(1u << 20);
			_map_buffer = _gpu.map_buffer(_buffer, true);
			_gpu.unmap_buffer(_map_buffer);
			_gpu.free_buffer(_buffer);
		}

		_try_execute();
	}

	~Main()
	{
		_gpu.free_buffer(_buffer);
	}
};


void Component::construct(Genode::Env &env) { static Main main(env); }
