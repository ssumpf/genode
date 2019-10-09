#ifndef _VIRTIO_CONSOLE_H_
#define _VIRTIO_CONSOLE_H_

#include <terminal_session/connection.h>

#include <virtio_device.h>

namespace Vmm
{
	class Virtio_console;
}

class Vmm::Virtio_console : public Virtio_device
{
	private:

		Terminal::Connection                _terminal;
		Cpu::Signal_handler<Virtio_console> _handler;

		void _read()
		{
			auto read = [&] (Genode::addr_t data, Genode::size_t size)
			{
				Genode::size_t length = _terminal.read((void *)data, size);
				return length;
			};

			if (!_terminal.avail()) return;

			_queue[RX]->notify(read);
			_assert_irq();
		}

		void _notify(unsigned idx) override
		{
			if (idx != TX) return;

			auto write = [&] (Genode::addr_t data, Genode::size_t size)
			{
				_terminal.write((void *)data, size);
				return size;
			};

			_queue[TX]->notify(write);
			_assert_irq();
		}

		struct DeviceFeatures : Mmio_register
		{
			enum {
				VIRTIO_F_VERSION_1    = 1,
				VIRTIO_CONSOLE_F_SIZE = 1
			};

			Mmio_register &_selector;

			Register read(Address_range&,  Cpu&) override
			{
				/* lower 32 bit */
				if (_selector.value() == 0) return VIRTIO_CONSOLE_F_SIZE;

				/* upper 32 bit */
				return VIRTIO_F_VERSION_1;
			}

			DeviceFeatures(Mmio_register &selector)
			: Mmio_register("DeviceFeatures", Mmio_register::RO, 0x10, 4),
			  _selector(selector)
			{ }
		} _device_features { _reg_container.regs[4] };

	public:

		Virtio_console(const char * const     name,
		               const Genode::uint64_t addr,
		               const Genode::uint64_t size,
		               unsigned irq,
		               Cpu &cpu,
		               Ram &ram,
		               Genode::Env &env)
		: Virtio_device(name, addr, size, irq, cpu, ram),
		  _terminal(env, "console"),
		  _handler(cpu, env.ep(), *this, &Virtio_console::_read)
		{
			/* set device ID to console */
			_reg_container.regs[2].set(0x3);

			add(_device_features);

			_terminal.read_avail_sigh(_handler);
		}
};

#endif /* _VIRTIO_CONSOLE_H_ */
