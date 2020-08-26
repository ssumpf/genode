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

#ifndef _SRC__SERVER__VMM__VM_H_
#define _SRC__SERVER__VMM__VM_H_

#include <ram.h>
#include <exception.h>
#include <cpu.h>
#include <gic.h>
#include <hw_trace_device.h>
#include <pl011.h>
#include <virtio_console.h>

#include <base/attached_io_mem_dataspace.h>
#include <base/attached_rom_dataspace.h>
#include <vm_session/connection.h>

namespace Vmm { class Vm; }

class Vmm::Vm
{
	private:

		using Ep = Genode::Entrypoint;

		enum {
			RAM_ADDRESS   = 0x60000000,
			RAM_SIZE      = 0x90000000,
			KERNEL_OFFSET = 0x80000,
			INITRD_OFFSET = 48 * 1024 * 1024,
			DTB_OFFSET    = 80 * 1024 * 1024,
			MAX_CPUS      = 1,
			STACK_SIZE    = sizeof(unsigned long) * 2048,
		};

		Genode::Env                  & _env;
		Genode::Vm_connection          _vm         { _env           };
		Genode::Attached_rom_dataspace _kernel_rom { _env, "linux"  };
		Genode::Attached_rom_dataspace _dtb_rom    { _env, "dtb"    };
		Genode::Attached_rom_dataspace _initrd_rom { _env, "initrd" };
		Genode::Attached_io_mem_dataspace _vm_ram  { _env, RAM_ADDRESS, RAM_SIZE };
		Genode::Attached_io_mem_dataspace _vm_trace { _env, 0xf0000000, 1 * 1024 * 1024 };
		Ram                            _ram        { RAM_ADDRESS, RAM_SIZE,
		                                             (Genode::addr_t)_vm_ram.local_addr<void>()};
		Genode::Heap                   _heap       { _env.ram(), _env.rm() };
		Mmio_bus                       _bus;
		Gic                            _gic;
		Genode::Constructible<Ep>      _eps[MAX_CPUS];
		Genode::Constructible<Cpu>     _cpus[MAX_CPUS];
		Pl011                          _uart;
		Virtio_console                 _virtio_console;
		unsigned long                  _index { 0 };

		void _load_kernel();
		void _load_dtb();
		void _load_initrd();

		typedef Hw_trace_device<2,4> Direct_device;
		typedef void (*Resources)(Direct_device &);

		enum { NUMBER_HW_DESCR = 9 };

		/* pass-through devices in order of appearance */
		Resources const _hw_descriptors[NUMBER_HW_DESCR] {
		/* MINIMAL */
			[](Direct_device &device) {                                   device.irqs(39); }, /* pmu */
			[](Direct_device &device) {                                   device.irqs(134, 141, 142, 143); }, /* busfreq */
			[](Direct_device &device) { device.mmio(0x32e2d000, 0x1000);  device.irqs(50); device.disable_trace(); }, /* irqsteer */
			[](Direct_device &device) { device.mmio(0x30a00000, 0x1000); device.irqs(66); }, /* mipi_dsi_bridge, dsi_phy */
			[](Direct_device &device) { device.mmio(0x30340000, 0x10000); device.disable_write(); }, /* iomux-gpr */
			[](Direct_device &device) { device.mmio(0x30360000, 0x10000); device.irqs(81); device.disable_trace(); device.disable_write(); }, /* anatop */
			[](Direct_device &device) { device.mmio(0x30380000, 0x10000); device.irqs(117, 118); device.disable_trace(); device.disable_write(); }, /* ccm */
			[](Direct_device &device) { device.mmio(0x30390000, 0x10000); device.irqs(121); }, /* src */
			[](Direct_device &device) { device.mmio(0x303a0000, 0x10000); device.irqs(119); }, /* gpc (GENERAL POWER CONTROLLER!) */
		/* END MINIMAL */
		};

		Genode::Constructible<Direct_device> _hw_devices[NUMBER_HW_DESCR];
		Hw_trace_device<1,8>                 _dcss { _env, _bus, boot_cpu(), _vm_trace.local_addr<void>(), _index };

		void _construct_hw()
		{
			void *trace = _vm_trace.local_addr<void>();
			Genode::memset(trace, 0, 1024*1024);
			Genode::warning("Creating devices");
			for (unsigned index = 0; index < NUMBER_HW_DESCR; index++) {
				_hw_devices[index].construct(_env, _bus, boot_cpu(), _vm_trace.local_addr<void>(), _index);
				_hw_descriptors[index](*_hw_devices[index]);
			}

			/* dcss */
			_dcss.mmio(0x32e00000, 0x2d000);
			_dcss.irqs(35, 36, 37, 38, 40, 41, 48, 49); /* CAUTION 41 is EDGE */
		}

	public:

		Vm(Genode::Env & env);

		Mmio_bus & bus() { return _bus; }
		Cpu      & boot_cpu();

		template <typename F>
		void cpu(unsigned cpu, F func)
		{
			if (cpu >= MAX_CPUS) Genode::error("Cpu number out of bounds ");
			else                 func(*_cpus[cpu]);
		}

		static unsigned last_cpu() { return MAX_CPUS - 1; }
};

#endif /* _SRC__SERVER__VMM__VM_H_ */
