#include <cpu.h>
#include <virtio_device.h>

#include <base/log.h>

using Vmm::Virtio_device;
using Register = Vmm::Mmio_register::Register;

Virtio_device::Virtio_device(const char * const     name,
                             const Genode::uint64_t addr,
                             const Genode::uint64_t size,
                             unsigned irq,
                             Cpu &cpu,
                             Ram &ram,
                             Genode::Env &env)
: Mmio_device(name, addr, size),
  _irq(cpu.gic().irq(irq)),
  _ram(ram), _terminal(env, "console"),
  _handler(cpu, env.ep(), *this, &Virtio_device::_read)
{
	for (unsigned i = 0; i < (sizeof(Dummy::regs) / sizeof(Mmio_register)); i++)
		add(_reg_container.regs[i]);

	add(_device_features);
	add(_driver_features);
	add(_queue_sel);
	add(_queue_ready);
	add(_queue_num);
	add(_queue_notify);
	add(_queue_descr_low);
	add(_queue_descr_high);
	add(_queue_driver_low);
	add(_queue_driver_high);
	add(_queue_device_low);
	add(_queue_device_high);
	add(_interrupt_status);
	add(_interrupt_ack);
	add(_status);

	_terminal.read_avail_sigh(_handler);
}


Register Virtio_device::Status::read(Address_range&,  Cpu&)
{
	Genode::log("Status read: ", _value);
	return value();
}


void Virtio_device::Status::write(Address_range&, Cpu&, Register reg)
{
	Genode::log("Status write: ", reg);
	set(reg);
}
