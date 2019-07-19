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

#include <vmm.h>

void Vmm::_load_kernel()
{
	Genode::memcpy((void*)(_ram.local() + KERNEL_OFFSET),
	               _kernel_rom.local_addr<void>(),
	               _kernel_rom.size());
}

void Vmm::_load_dtb()
{
	Genode::memcpy((void*)(_ram.local() + DTB_OFFSET),
	               _dtb_rom.local_addr<void>(),
	               _dtb_rom.size());
}


void Vmm::handle_data_abort(Genode::uint64_t ipa)
{
	Device * device = _device_tree.first()
		? _device_tree.first()->find_by_addr(ipa) : nullptr;
	if (!device)
		throw Exception("No device at IPA=%llx", ipa);
	device->handle_memory_access(_cpu.state());
	_cpu.state().ip += sizeof(Genode::addr_t);
}


Vmm::Vmm(Genode::Env & env)
: _vm(env),
  _kernel_rom(env, "linux"),
  _dtb_rom(env, "dtb"),
  _vm_ram(env.ram(), env.rm(), RAM_SIZE, Genode::UNCACHED),
  _ram(RAM_ADDRESS, RAM_SIZE, (Genode::addr_t)_vm_ram.local_addr<void>()),
  _heap(env.ram(), env.rm()),
  _vm_handler(_cpu, env.ep(), *this, &Vmm::_handle),
  _cpu(*this, _vm, env, _heap, _vm_handler,
       _ram.base() + KERNEL_OFFSET,
       _ram.base() + DTB_OFFSET),
  _uart("Pl011", 0x1c090000, 0x1000, _cpu, env)
{
	_device_tree.insert(&_uart);
	_vm.attach(_vm_ram.cap(), RAM_ADDRESS);
	// XXX _vm.attach_pic(0x2C002000);
	_load_kernel();
	_load_dtb();

	Genode::log("Start virtual machine ...");

	_cpu.run();
};
