#include <base/log.h>
#include <util/reconstructible.h>
#include <ram.h>
#include <mmio.h>


namespace Vmm {
	class Virtio_device;
	class Virtio_queue;
	struct Virtio_queue_data;
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

	Genode::addr_t descr()  const { return ((Genode::addr_t)descr_high <<  32) | descr_low; }
	Genode::addr_t driver() const { return ((Genode::addr_t)driver_high << 32) | driver_low; }
	Genode::addr_t device() const { return ((Genode::addr_t)device_high << 32) | device_low; }
};

class Vmm::Virtio_queue
{
	private:

		Virtio_queue_data &_data;
		Ram               &_ram;

	public:

		Virtio_queue(Virtio_queue_data &data, Ram &ram)
		: _data(data), _ram(ram) { }
};

class Vmm::Virtio_device : public Vmm::Mmio_device
{
	private:

		enum { RX = 0, TX = 1, NUM = 2 };
		Virtio_queue_data _data[NUM];
		uint32_t          _current { RX };

		Genode::Constructible<Virtio_queue> _queue[NUM];
		Ram                                &_ram;

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
				Genode::log("driver features WRITE sel: ", _selector.value(), " reg: ", Genode::Hex(reg));
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
			void write(Address_range&, Cpu&, Register reg) override
			{
				Genode::log("QueueNotify: ", reg);
			}

			QueueNotify()
			: Mmio_register("QueueNotify", Mmio_register::WO, 0x50, 4) { }
		} _queue_notify;

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

	public:

		Virtio_device(const char * const     name,
		              const Genode::uint64_t addr,
		              const Genode::uint64_t size,
		              Ram &ram);
};
