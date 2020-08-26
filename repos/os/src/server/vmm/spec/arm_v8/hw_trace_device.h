/*
 * \brief  VMM dedicated hardware device passed-through to VM
 * \author Stefan Kalkowski
 * \date   2019-09-25
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__SERVER__VMM__HW_TRACE_DEVICE_H_
#define _SRC__SERVER__VMM__HW_TRACE_DEVICE_H_

#include <exception.h>
#include <mmio.h>
#include <gic.h>

#include <base/attached_io_mem_dataspace.h>
#include <irq_session/connection.h>

namespace Vmm {
	template <unsigned, unsigned> class Hw_trace_device;
}


template <unsigned MMIO_COUNT, unsigned IRQ_COUNT>
class Vmm::Hw_trace_device
{
	private:

		class Irq : Gic::Irq::Irq_handler
		{
			private:

				using Session = Genode::Constructible<Genode::Irq_connection>;

				Gic::Irq               & _irq;
				Genode::Env            & _env;
				unsigned                 _number;
				Session                  _session;
				Cpu::Signal_handler<Irq> _handler;

				void _assert()
				{
	//				Genode::log("IRQ: ", _number);
					_irq.assert();
				}

			public:

				void enabled() override
				{
					if (!_session.constructed()) {
						_session.construct(_env, _irq.number(),
						                   _irq.level() ?
						                   Genode::Irq_session::TRIGGER_LEVEL :
						                   Genode::Irq_session::TRIGGER_EDGE);
						_session->sigh(_handler);
						_session->ack_irq();
					}
				}

				void disabled() override
				{
					if (_session.constructed())
						_session.destruct();
				}

				void eoi() override
				{
					if (_session.constructed()) _session->ack_irq();
				}

				Irq(Gic::Irq & irq, Cpu & cpu, Genode::Env & env, unsigned number)
				: _irq(irq),
				  _env(env),
				  _number(number),
				  _handler(cpu, env.ep(), *this, &Irq::_assert)
				{
					_irq.handler(*this);
				}
		};

		class Mmio_trace : public Vmm::Mmio_device
		{
			private:

				Genode::addr_t _local_addr;
				void          *_buffer;
				unsigned long &_index;
				bool           _trace;
				bool           _write { true };

			public:

				Mmio_trace(Name             name,
				           Genode::uint64_t start,
				           Genode::uint64_t size,
				           Genode::uint64_t local_addr,
				           void            *buffer,
				           unsigned long   &index,
				           bool trace = true)
				: Mmio_device(name, start, size),
				  _local_addr(local_addr), _buffer(buffer), _index(index),  _trace(trace)
				{
				}
		
				void log_buffer(unsigned a, unsigned b, unsigned c)
				{
					unsigned *addr = (unsigned *)_buffer;
					if (_index * 4 + 12 > 1 * 1024 * 1024) {
						Genode::error("Tracebuffer full");
						return;
					}
					addr[_index] = a;
					addr[_index+1] = b;
					addr[_index+2] = c;
					addr[_index+3] = 0;

					_index += 4;
				}

				Register read(Address_range  & access, Cpu&) override
				{
					using namespace Genode;
					addr_t *target = (addr_t *)(_local_addr + access.start);


					Register ret;
					switch (access.size) {
						case 1: ret =  *(uint8_t *)target; break;
						case 2: ret =  *(uint16_t *)target; break;
						case 4: ret = *(uint32_t *)target; break;
						case 8: ret =  *target; break;
						default: return 0;
					}

					if (_trace)
						log_buffer(0, start + access.start, ret);

					return ret;
				}

				void write(Address_range & access, Cpu & cpu, Register value) override
				{
					using namespace Genode;
					addr_t *target = (addr_t *)(_local_addr + access.start);

					if (_write == false) return;

					if (_trace)
						log_buffer(1, start + access.start, value);

					switch (access.size) {
						case 1: *((uint8_t  *)target) = value; break;
						case 2: *((uint16_t *)target) = value; break;
						case 4: *((uint32_t *)target) = value; break;
						case 8: *target = value;
					}
				}

				void disable_trace() { _trace = false; }
				void disable_write() { _write = false; }
		};

		Genode::Env           & _env;
		Mmio_bus              & _bus;
		Cpu                   & _cpu;
		void                  * _buffer;
		unsigned long         & _index;

		Genode::Constructible<Genode::Attached_io_mem_dataspace> _ds[MMIO_COUNT];
		Genode::Constructible<Mmio_trace>                        _mmio[MMIO_COUNT];
		Genode::Constructible<Irq> _irqs[IRQ_COUNT];

		void mmio() { }
		void irqs() { }

	public:

		Hw_trace_device(Genode::Env &env,
		                Mmio_bus &bus,
		                Cpu & cpu, void *buffer, unsigned long &index)
		: _env(env), _bus(bus), _cpu(cpu), _buffer(buffer), _index(index) { };

		void disable_trace()
		{
			for (unsigned i = 0; i < MMIO_COUNT; i++) {
				if (_mmio[i].constructed())
					_mmio[i]->disable_trace();
			}
		}

		void disable_write()
		{
			for (unsigned i = 0; i < MMIO_COUNT; i++) {
				if (_mmio[i].constructed())
					_mmio[i]->disable_write();
			}
		}

		template <typename... ARGS>
		void mmio(Genode::addr_t start, Genode::size_t size, ARGS &&... args)
		{
			mmio(args...);
			for (unsigned i = 0; i < MMIO_COUNT; i++) {
				if (_ds[i].constructed()) continue;
				_ds[i].construct(_env, start, size);
				Genode::addr_t local_addr = _env.rm().attach(_ds[i]->cap());
				_mmio[i].construct("hw_trace", start, size, local_addr, _buffer, _index);
				_bus.add(*_mmio[i]);
				return;
			}
		}

		template <typename... ARGS>
		void irqs(unsigned irq, ARGS &&... args)
		{
			irqs(args...);
			for (unsigned i = 0; i < IRQ_COUNT; i++) {
				if (_irqs[i].constructed()) continue;
				_irqs[i].construct(_cpu.gic().irq(irq), _cpu, _env, irq);
				return;
			}
		}
};

#endif /* _SRC__SERVER__VMM__HW_DEVICE_H_ */
