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
#include <hw_device.h>
#include <pl011.h>
#include <virtio_console.h>

#include <base/attached_ram_dataspace.h>
#include <base/attached_rom_dataspace.h>
#include <vm_session/connection.h>

namespace Vmm { class Vm; }

class Vmm::Vm
{
	private:

		using Ep = Genode::Entrypoint;

		enum {
			RAM_ADDRESS   = 0x60000000,
			RAM_SIZE      = 900 * 1024 * 1024,
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
		Genode::Attached_ram_dataspace _vm_ram     { _env.ram(), _env.rm(),
		                                             RAM_SIZE, Genode::CACHED };
		Ram                            _ram        { RAM_ADDRESS, RAM_SIZE,
		                                             (Genode::addr_t)_vm_ram.local_addr<void>()};
		Genode::Heap                   _heap       { _env.ram(), _env.rm() };
		Mmio_bus                       _bus;
		Gic                            _gic;
		Genode::Constructible<Ep>      _eps[MAX_CPUS];
		Genode::Constructible<Cpu>     _cpus[MAX_CPUS];
		Pl011                          _uart;
		Virtio_console                 _virtio_console;

		void _load_kernel();
		void _load_dtb();
		void _load_initrd();

		typedef Hw_device<2,4> Direct_device;
		typedef void (*Resources)(Direct_device &);

		enum { NUMBER_HW_DESCR = 38 };

		/* pass-through devices in order of appearance */
		Resources const _hw_descriptors[NUMBER_HW_DESCR] {
			[](Direct_device &device) { device.mmio(0x30360000, 0x10000); device.irqs(63); }, /* anatop */
			[](Direct_device &device) { device.mmio(0x30380000, 0x10000); device.irqs(117, 118); }, /* ccm */
			[](Direct_device &device) { device.mmio(0x306a0000, 0x30000); device.irqs(79, 80); }, /* system counter */
			[](Direct_device &device) { device.mmio(0x30350000, 0x10000);                      }, /* ocotp-ctrl */
			[](Direct_device &device) { device.mmio(0x30330000, 0x10000);                      }, /* iomuxc */
			[](Direct_device &device) { device.mmio(0x30200000, 0x10000); device.irqs(96, 97);   }, /* gpio */
			[](Direct_device &device) { device.mmio(0x30210000, 0x10000); device.irqs(98, 99);   }, /* gpio */
			[](Direct_device &device) { device.mmio(0x30220000, 0x10000); device.irqs(100, 101); }, /* gpio */
			[](Direct_device &device) { device.mmio(0x30230000, 0x10000); device.irqs(102, 103); }, /* gpio */
			[](Direct_device &device) { device.mmio(0x30240000, 0x10000); device.irqs(104, 105); }, /* gpio */
			[](Direct_device &device) { device.mmio(0x30a20000, 0x10000); device.irqs(67); }, /* i2c */
			[](Direct_device &device) { device.mmio(0x30a30000, 0x10000); device.irqs(68); }, /* i2c */
			[](Direct_device &device) { device.mmio(0x30a40000, 0x10000); device.irqs(69); }, /* i2c */
			[](Direct_device &device) { device.mmio(0x30a50000, 0x10000); device.irqs(70); }, /* i2c */
			[](Direct_device &device) { device.mmio(0x30bd0000, 0x10000); device.irqs(34); }, /* sdma */
			[](Direct_device &device) { device.mmio(0x302c0000, 0x10000); device.irqs(135); }, /* sdma */
			[](Direct_device &device) { device.mmio(0x33000000, 0x2000);  device.irqs(44); }, /* dma-apbh */
			[](Direct_device &device) { device.mmio(0x303a0000, 0x10000); device.irqs(119); }, /* gpc (GENERAL POWER CONTROLLER!) */
			[](Direct_device &device) {                                   device.irqs(39); }, /* pmu */
			[](Direct_device &device) { device.mmio(0x30b40000, 0x10000); device.irqs(54); }, /* usdhc */
			[](Direct_device &device) { device.mmio(0x30b50000, 0x10000); device.irqs(55); }, /* usdhc */
			[](Direct_device &device) { device.mmio(0x302d0000, 0x10000); device.irqs(87); }, /* gpt */
			[](Direct_device &device) { device.mmio(0x33002000, 0x6000);  device.irqs(46); }, /* gpmi-nand */
			[](Direct_device &device) { device.mmio(0x38100000, 0x10000); device.irqs(72); }, /* usb */
			[](Direct_device &device) { device.mmio(0x38200000, 0x10000); device.irqs(73); }, /* usb */
			[](Direct_device &device) {                                   device.irqs(134, 141, 142, 143); }, /* busfreq */
			[](Direct_device &device) { device.mmio(0x30370000, 0x10000); device.irqs(51, 52, 148); }, /* snvs */
			[](Direct_device &device) { device.mmio(0x30820000, 0x10000); device.irqs(63); }, /* espi */
			[](Direct_device &device) { device.mmio(0x30830000, 0x10000); device.irqs(64); }, /* espi */
			[](Direct_device &device) { device.mmio(0x30840000, 0x10000); device.irqs(65); }, /* espi */
			[](Direct_device &device) { device.mmio(0x30be0000, 0x10000); device.irqs(118, 119, 120); }, /* network */
			[](Direct_device &device) { device.mmio(0x3d800000, 0x400000); device.irqs(132); }, /* ddr_pmu */
			[](Direct_device &device) { device.mmio(0x30260000, 0x10000); device.irqs(81); }, /* tmu */
			[](Direct_device &device) { device.mmio(0x32e2d000, 0x1000);  device.irqs(50); }, /* tmu */
			[](Direct_device &device) { device.mmio(0x30280000, 0x10000);  device.irqs(110); }, /* wdog */
			[](Direct_device &device) { device.mmio(0x30290000, 0x10000);  device.irqs(111); }, /* wdog */
			[](Direct_device &device) { device.mmio(0x302a0000, 0x10000);  device.irqs(32); }, /* wdog */
			[](Direct_device &device) { device.mmio(0x38300000, 0x200000);  device.irqs(39, 40); }, /* vpu */
			//[](Direct_device &device) { device.mmio(0x33800000, 0x400000);  device.irqs(154, 159); }, /* pci */
			//[](Direct_device &device) { device.mmio(0x33c00000, 0x400000);  device.irqs(106, 112); }, /* pci */
			//[](Direct_device &device) { device.mmio(0x30bb0000, 0x10000, 0x8000000, 0x10000000); device.irqs(139); }, /* qspi */
		};

		Genode::Constructible<Direct_device> _hw_devices[NUMBER_HW_DESCR];

		void _construct_hw()
		{
			for (unsigned index = 0; index < NUMBER_HW_DESCR; index++) {
				_hw_devices[index].construct(_env, _vm, boot_cpu());
				_hw_descriptors[index](*_hw_devices[index]);
			}
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
