/*
 * \brief  VMM example for ARMv8 virtualization
 * \author Stefan Kalkowski
 * \date   2019-07-18
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__SERVER__VMM__VMM_H_
#define _SRC__SERVER__VMM__VMM_H_

#include <ram.h>
#include <exception.h>
#include <cpu.h>
#include <pl011.h>

#include <base/attached_ram_dataspace.h>
#include <base/attached_rom_dataspace.h>
#include <vm_session/connection.h>

class Vmm
{
	private:

		enum {
			RAM_ADDRESS   = 0x40000000,
			RAM_SIZE      = 128 * 1024 *1024,
			KERNEL_OFFSET = 0x80000,
			DTB_OFFSET    = 64 * 1024 * 1024,
		};

		Genode::Vm_connection          _vm;
		Genode::Attached_rom_dataspace _kernel_rom;
		Genode::Attached_rom_dataspace _dtb_rom;
		Genode::Attached_ram_dataspace _vm_ram;
		Ram                            _ram;
		Genode::Heap                   _heap;
		Cpu::Signal_handler<Vmm>       _vm_handler;
		Cpu                            _cpu;
		Genode::Avl_tree<Device>       _device_tree;
		Pl011                          _uart;

		void _load_kernel();
		void _load_dtb();
		void _handle() {} /* dummy handler */

	public:

		Vmm(Genode::Env & env);

		void  handle_data_abort(Genode::uint64_t ipa);
		void  handle_hyper_call() { throw Exception("Unknown hyper call!"); }
		Cpu & cpu()               { return _cpu;                            }
};

#endif /* _SRC__SERVER__VMM__VMM_H_ */
