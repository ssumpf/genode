#ifndef _VIRTIO_NET_H_
#define _VIRTIO_NET_H_

#include <nic/packet_allocator.h>
#include <nic_session/connection.h>

#include <virtio_device.h>

namespace Vmm
{
	class Virtio_net;
}

class Vmm::Virtio_net : public Virtio_device
{
	private:

		Genode::Env &_env;

		Genode::Heap          _heap     { _env.ram(), _env.rm() };
		Genode::Allocator_avl _tx_alloc { &_heap };

		enum { BUF_SIZE = Nic::Packet_allocator::DEFAULT_PACKET_SIZE * 128 };

		Nic::Connection _nic { _env, &_tx_alloc, BUF_SIZE, BUF_SIZE };

		Cpu::Signal_handler<Virtio_net> _handler;

		void _free_packets()
		{
			while (_nic.tx()->ack_avail()) {
				Nic::Packet_descriptor packet = _nic.tx()->get_acked_packet();
				_nic.tx()->release_packet(packet);
			}
		}

		void _handle()
		{
			Genode::log("HANDLE");
			/* possbile ready to submit */
			_notify(TX);

			/* RX */
			auto recv = [&] (Genode::addr_t data, Genode::size_t size)
			{
				Nic::Packet_descriptor const rx_packet = _nic.rx()->get_packet();

				Genode::size_t sz = Genode::min(size, rx_packet.size() + 12);
				Genode::memcpy((void *)(data + 12),
				               _nic.rx()->packet_content(rx_packet),
				               sz);
				_nic.rx()->acknowledge_packet(rx_packet);

				return sz;
			};

			bool progress = false;
			while (_nic.rx()->packet_avail() && _nic.rx()->ready_to_ack()) {
				if (!_queue[RX]->notify(recv)) break;
				progress = true;
			}

			if (progress) _assert_irq();
		}

		void _notify(unsigned idx) override
		{
			Genode::log("notify: ", idx);

			if (idx != TX) return;

			auto send = [&] (Genode::addr_t data, Genode::size_t size)
			{
				if (!_nic.tx()->ready_to_submit()) return 0lu;

				char const *buf = (char const *)data;
				Genode::log("header: ", Genode::Hex(data));
				for (int i = 0; i < 12; i++)
					Genode::log(buf[i]);

				data += 12; size -= 12;

				Nic::Packet_descriptor tx_packet;
				try {
					tx_packet = _nic.tx()->alloc_packet(size); }
				catch (Nic::Session::Tx::Source::Packet_alloc_failed) {
				return 0lu; }

				Genode::memcpy(_nic.tx()->packet_content(tx_packet),
				               (void *)data, size);
				_nic.tx()->submit_packet(tx_packet);
				return size;
			};

			if (_queue[idx]->notify(send)) _assert_irq();
			_free_packets();
		}

		struct DeviceFeatures : Mmio_register
		{
			enum {
				VIRTIO_F_VERSION_1 = 1,
			};

			Mmio_register &_selector;

			Register read(Address_range&,  Cpu&) override
			{
				/* lower 32 bit */
				if (_selector.value() == 0) return 0;

				/* upper 32 bit */
				return VIRTIO_F_VERSION_1;
			}

			DeviceFeatures(Mmio_register &selector)
			: Mmio_register("DeviceFeatures", Mmio_register::RO, 0x10, 4),
			  _selector(selector)
			{ }
		} _device_features { _reg_container.regs[4] };

	public:

		Virtio_net(const char * const     name,
		           const Genode::uint64_t addr,
		           const Genode::uint64_t size,
		           unsigned irq,
		           Cpu &cpu,
		           Ram &ram,
		           Genode::Env &env)
		: Virtio_device(name, addr, size, irq, cpu, ram),
		  _env(env),
		  _handler(cpu, _env.ep(), *this, &Virtio_net::_handle)
		{
			/* set device ID to network */
			_reg_container.regs[2].set(0x1);

			add(_device_features);
			_nic.tx_channel()->sigh_ready_to_submit(_handler);
			_nic.tx_channel()->sigh_ack_avail      (_handler);
			_nic.rx_channel()->sigh_ready_to_ack   (_handler);
			_nic.rx_channel()->sigh_packet_avail   (_handler);
		}
};
#endif /* _VIRTIO_NET_H_ */
