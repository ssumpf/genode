#include <base/log.h>
#include <terminal_session/connection.h>
#include <util/mmio.h>
#include <util/reconstructible.h>

#include <gic.h>
#include <ram.h>
#include <mmio.h>

namespace Vmm {
	class  Virtio_device;
	class  Virtio_queue;
	struct Virtio_queue_data;
	class  Virtio_descriptor;
	class  Virtio_avail;
	class  Virtio_used;
}

using uint32_t = Genode::uint32_t;

struct Vmm::Virtio_queue_data
{
	uint32_t descr_low     { 0 };
	uint32_t descr_high    { 0 };
	uint32_t driver_low    { 0 };
	uint32_t driver_high   { 0 };
	uint32_t device_low    { 0 };
	uint32_t device_high   { 0 };
	uint32_t num           { 0 };
	uint32_t ready         { 0 };

	Genode::addr_t descr()  const { return ((Genode::addr_t)descr_high  << 32) | descr_low; }
	Genode::addr_t driver() const { return ((Genode::addr_t)driver_high << 32) | driver_low; }
	Genode::addr_t device() const { return ((Genode::addr_t)device_high << 32) | device_low; }
};


class Vmm::Virtio_descriptor : Genode::Mmio
{
	public:

		Virtio_descriptor(Genode::addr_t base)
		: Mmio(base) {  }


		struct Address : Register<0x0, 64> { };
		struct Length  : Register<0x8, 32> { };

		struct Flags : Register<0xc, 16>
		{
			struct Next     : Bitfield<0, 1> { };
			struct Write    : Bitfield<1, 1> { };
			struct Indirect : Bitfield<2, 1> { };
		};

		struct Next  : Register<0xe, 16> { };

		constexpr Genode::size_t size() { return 16; }

		Virtio_descriptor index(unsigned idx)
		{
			return Virtio_descriptor(base() + (size() * idx));
		}

		Genode::addr_t address() const { return read<Address>(); }
		Genode::size_t length () const { return read<Length>(); }
		Genode::uint16_t flags() const { return read<Flags>(); }
		Genode::uint16_t next() const { return read<Next>(); }
};


class Vmm::Virtio_avail : public Genode::Mmio
{
	public:

		Virtio_avail(Genode::addr_t base)
		: Mmio(base) { };

		struct Flags : Register<0x0, 16> { };
		struct Idx   : Register<0x2, 16> { };
		struct Ring  : Register_array<0x4, 16, 8, 16> { };
};


class Vmm::Virtio_used : public Genode::Mmio
{
	public:

		Virtio_used(Genode::addr_t base)
		: Mmio(base) { };

		struct Flags : Register<0x0, 16> { };
		struct Idx   : Register<0x2, 16> { };

		struct Elem : Register_array<0x4, 64, 8, 64>
		{
			struct Id     : Bitfield<0, 32> { };
			struct Length : Bitfield<32,32> { };
		};
};

/** 
 * Split queue implementation
 */
class Vmm::Virtio_queue
{
	private:

		Virtio_queue_data &_data;
		Ram               &_ram;

		Virtio_descriptor _descr { _ram.local_address(_data.descr()) };
		Virtio_avail      _avail { _ram.local_address(_data.driver())};
		Virtio_used       _used  { _ram.local_address(_data.device())};

	public:

		Virtio_queue(Virtio_queue_data &data, Ram &ram)
		: _data(data), _ram(ram) { }


	template <typename FUNC>
	void notify(FUNC func, bool tx)
	{
#if 0
		for (unsigned idx = 0; idx < 8; idx++) {
		Virtio_descriptor descr = _descr.index(idx);

		Genode::log("notify: idx: ", idx, " a: ", Genode::Hex(descr.address()), 
		            " l: ", descr.length(), " f: ", Genode::Hex(descr.flags()),
		            " next: ", Genode::Hex(descr.next()));
		}

		for (unsigned i = 0; i < 8; i++) {
			unsigned flags = _avail.read<Virtio_avail::Flags>();
			unsigned idx  = _avail.read<Virtio_avail::Idx>();
			unsigned ring = _avail.read<Virtio_avail::Ring>(i);
			Genode::log("avail: i: ", i, " f: ", Genode::Hex(flags),
			            " idx: ", idx, " r: ", Genode::Hex(ring));
		}
#endif
		Virtio_descriptor descr = _descr.index(0);
		if (!descr.address()) return;

		Genode::addr_t data   = _ram.local_address(descr.address());
		Genode::size_t length = func(data, descr.length());

		if (length == 0) return;

		Genode::uint16_t idx = 0;
		if (tx)
			idx = _avail.read<Virtio_avail::Idx>();
		else
			idx = _used.read<Virtio_used::Idx>() + 1;

		_used.write<Virtio_used::Flags>(0);
		Virtio_used::Elem::access_t elem = 0;
		Virtio_used::Elem::Id::set(elem,  0);
		Virtio_used::Elem::Length::set(elem, length);
		_used.write<Virtio_used::Elem>(elem, 0);
		_used.write<Virtio_used::Idx>(idx);
	}
};

class Vmm::Virtio_device : public Vmm::Mmio_device
{
	private:

		enum { RX = 0, TX = 1, NUM = 2 };
		Virtio_queue_data _data[NUM];
		uint32_t          _current { RX };

		Genode::Constructible<Virtio_queue> _queue[NUM];
		Gic::Irq                           &_irq;
		Ram                                &_ram;
		Terminal::Connection                _terminal;
		Cpu::Signal_handler<Virtio_device>  _handler;

		struct Dummy {
			Mmio_register regs[7];
		} _reg_container { .regs = {
			{ "MagicValue", Mmio_register::RO, 0x0, 4, 0x74726976            },
			{ "Version",    Mmio_register::RO, 0x4, 4, 0x2                   },
			{ "DeviceID",   Mmio_register::RO, 0x8, 4, 0x3 /* console */     },
			{ "VendorID",   Mmio_register::RO, 0xc, 4, 0x554d4551 /* QEMU */ },
			{ "DeviceFeatureSel", Mmio_register::RW, 0x14, 4, 0 },
			{ "DriverFeatureSel", Mmio_register::RW, 0x24, 4, 0 },
			{ "QueueNumMax", Mmio_register::RO, 0x34, 4, 8 }
		}};


		void               _queue_select(uint32_t sel) { _current = sel; }
		Virtio_queue_data &_queue_data() { return _data[_current]; }

		void _queue_state(bool const construct)
		{
			if (construct && !_queue[_current].constructed())
				_queue[_current].construct(_queue_data(), _ram);

			if (!construct && _queue[_current].constructed())
				_queue[_current].destruct();
		}

		void _assert_irq()
		{
			_interrupt_status.set(0x1);
			_irq.assert();
		}

		void _deassert_irq()
		{
			_interrupt_status.set(0);
			_irq.deassert();
		}

		void _read()
		{
			auto read = [&] (Genode::addr_t data, Genode::size_t size)
			{
				Genode::size_t length = _terminal.read((void *)data, size);
				return length;
			};

			if (!_terminal.avail()) return;

			_queue[RX]->notify(read, false);
			_assert_irq();
		}

		void notify(unsigned idx)
		{
			if (idx != TX) return;

			auto write = [&] (Genode::addr_t data, Genode::size_t size)
			{
				_terminal.write((void *)data, size);
				return size;
			};

			_queue[TX]->notify(write, true);
			_assert_irq();
		}

	private:

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

		struct DriverFeatures : Mmio_register
		{
			Mmio_register    &_selector;
			Genode::uint32_t  _lower { 0 };
			Genode::uint32_t  _upper { 0 };

			void write(Address_range&, Cpu&, Register reg) override
			{
				Genode::log("driver features WRITE sel: ", _selector.value(), " reg: ", Genode::Hex((uint32_t)reg));
				if (_selector.value() == 0) _lower = reg;
				_upper = reg;
			}

			DriverFeatures(Mmio_register &selector)
			: Mmio_register("DriverFeatures", Mmio_register::WO, 0x20, 4),
			  _selector(selector)
			{ }
		} _driver_features { _reg_container.regs[5] };

		struct Status : Mmio_register
		{
			Register read(Address_range&,  Cpu&)           override;
			void     write(Address_range&, Cpu&, Register) override;

			Status()
			: Mmio_register("Status", Mmio_register::RW, 0x70, 4, 0)
			{ }
		} _status;

		struct QueueSel : Mmio_register
		{
			Virtio_device &device;

			void write(Address_range&, Cpu&, Register reg) override
			{
				Genode::log("QueueSel: ", reg);
				if (reg >= device.NUM) return;
				device._queue_select(reg);
			}

			QueueSel(Virtio_device &device)
			: Mmio_register("QueueSel", Mmio_register::WO, 0x30, 4),
			  device(device) { }
		} _queue_sel { *this };

		struct QueueNum : Mmio_register
		{
			Virtio_device &device;

			void write(Address_range&, Cpu&, Register reg) override
			{
				Genode::log("QueueNum: ", reg);
				device._queue_data().num = reg;
			}

			QueueNum(Virtio_device &device)
			: Mmio_register("QueueNum", Mmio_register::WO, 0x38, 4),
			  device(device) { }
		} _queue_num { *this };

		struct QueueReady : Mmio_register
		{
			Virtio_device &device;

			Register read(Address_range&,  Cpu&) override
			{
				Genode::log("QueueReady read: ", value());
				return device._queue_data().ready; 
			}

			void write(Address_range&, Cpu&, Register reg) override
			{
				Genode::log("QueueReady write: ", reg);
				bool construct = reg == 1 ? true : false;
				device._queue_data().ready = reg;
				device._queue_state(construct);
			}

			QueueReady(Virtio_device &device)
			: Mmio_register("QueueReady", Mmio_register::RW, 0x44, 4),
			  device(device) { }
		} _queue_ready { *this };

		struct QueueNotify : Mmio_register
		{
			Virtio_device &device;

			void write(Address_range&, Cpu&, Register reg) override
			{
				//Genode::log("QueueNotify: ", reg);
				device.notify(reg);
			}

			QueueNotify(Virtio_device &device)
			: Mmio_register("QueueNotify", Mmio_register::WO, 0x50, 4),
			  device(device) { }
		} _queue_notify { *this };

		struct QueueDescrLow : Mmio_register
		{
			Virtio_device &device;

			void write(Address_range&, Cpu&, Register reg) override
			{
				Genode::log("QueueDescrLow: ", Genode::Hex(reg));
				device._queue_data().descr_low = reg;
			}

			QueueDescrLow(Virtio_device &device)
			: Mmio_register("QueuDescrLow", Mmio_register::WO, 0x80, 4),
			  device(device) { }
		} _queue_descr_low { *this };

		struct QueueDescrHigh : Mmio_register
		{
			Virtio_device &device;

			void write(Address_range&, Cpu&, Register reg) override
			{
				Genode::log("QueueDescrHigh: ", Genode::Hex(reg));
				device._queue_data().descr_high = reg;
			}

			QueueDescrHigh(Virtio_device &device)
			: Mmio_register("QueuDescrHigh", Mmio_register::WO, 0x84, 4),
			  device(device) { }
		} _queue_descr_high { *this };

		struct QueueDriverLow : Mmio_register
		{
			Virtio_device &device;

			void write(Address_range&, Cpu&, Register reg) override
			{
				Genode::log("QueueDriverLow: ", Genode::Hex(reg));
				device._queue_data().driver_low = reg;
			}

			QueueDriverLow(Virtio_device &device)
			: Mmio_register("QueuDriverLow", Mmio_register::WO, 0x90, 4),
			  device(device) { }
		} _queue_driver_low { *this };

		struct QueueDriverHigh : Mmio_register
		{
			Virtio_device &device;

			void write(Address_range&, Cpu&, Register reg) override
			{
				Genode::log("QueueDriverHigh: ", Genode::Hex(reg));
				device._queue_data().driver_high = reg;
			}

			QueueDriverHigh(Virtio_device &device)
			: Mmio_register("QueuDriverHigh", Mmio_register::WO, 0x94, 4),
			  device(device) { }
		} _queue_driver_high { *this };

		struct QueueDeviceLow : Mmio_register
		{
			Virtio_device &device;

			void write(Address_range&, Cpu&, Register reg) override
			{
				Genode::log("QueueDeviceLow: ", Genode::Hex(reg));
				device._queue_data().device_low = reg;
			}

			QueueDeviceLow(Virtio_device &device)
			: Mmio_register("QueuDeviceLow", Mmio_register::WO, 0xa0, 4),
			  device(device) { }
		} _queue_device_low { *this };

		struct QueueDeviceHigh : Mmio_register
		{
			Virtio_device &device;

			void write(Address_range&, Cpu&, Register reg) override
			{
				Genode::log("QueueDeviceHigh: ", Genode::Hex(reg));
				device._queue_data().device_high = reg;
			}

			QueueDeviceHigh(Virtio_device &device)
			: Mmio_register("QueuDeviceHigh", Mmio_register::WO, 0xa4, 4),
			  device(device) { }
		} _queue_device_high { *this };

		struct InterruptStatus : Mmio_register
		{
			Register read(Address_range&,  Cpu&) override
			{
				//Genode::log("InterruptStatus: ", Genode::Hex(value()));
				return value();
			}

			InterruptStatus()
			: Mmio_register("InterruptStatus", Mmio_register::RO, 0x60, 4)
			{ }
		} _interrupt_status;

		struct InterruptAck : Mmio_register
		{
			Virtio_device &device;

			void write(Address_range&, Cpu&, Register reg) override
			{
				//Genode::log("InterruptAck: ", Genode::Hex(reg));
				device._deassert_irq();
			}

			InterruptAck(Virtio_device &device)
			: Mmio_register("InterruptAck", Mmio_register::WO, 0x64, 4),
			  device(device) { }
		} _interrupt_ack { *this };

	public:

		Virtio_device(const char * const     name,
		              const Genode::uint64_t addr,
		              const Genode::uint64_t size,
		              unsigned irq,
		              Cpu &cpu,
		              Ram &ram,
		              Genode::Env &env);
};
