/*
 * \brief  VMM device object
 * \author Stefan Kalkowski
 * \date   2019-07-18
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__SERVER__VMM__DEVICE_H_
#define _SRC__SERVER__VMM__DEVICE_H_

#include <cpu.h>
#include <exception.h>
#include <os/ring_buffer.h>
#include <util/avl_tree.h>

class Device : public Genode::Avl_node<Device>
{
	protected:

		const char * const     _name;
		const Genode::uint64_t _addr;
		const Genode::uint64_t _size;
		Cpu                  & _cpu;

		using Error = Exception;

	public:

		Device(const char * const       name,
		       const Genode::uint64_t   addr,
		       const Genode::uint64_t   size,
		       Cpu                    & cpu)
		: _name(name), _addr(addr), _size(size), _cpu(cpu) { }

		Genode::uint64_t addr() { return _addr; }
		Genode::uint64_t size() { return _size; }
		const char *     name() { return _name; }

		virtual void read  (Genode::uint64_t * reg,
		                    Genode::uint64_t   off) {
			throw Error("Device %s: doubleword-wise read of %llx not allowed",
			            name(), off); }

		virtual void write (Genode::uint64_t * reg,
		                    Genode::uint64_t   off) {
			throw Error("Device %s: doubleword-wise write of %llx not allowed",
			            name(), off); }

		virtual void read  (Genode::uint32_t * reg,
		                    Genode::uint64_t   off) {
			throw Error("Device %s: word-wise read of %llx not allowed",
			            name(), off); }

		virtual void write (Genode::uint32_t * reg,
		                    Genode::uint64_t   off) {
			throw Error("Device %s: word-wise write of %llx not allowed",
			            name(), off); }

		virtual void read  (Genode::uint16_t * reg,
		                    Genode::uint64_t   off) {
			throw Error("Device %s: halfword read of %llx not allowed",
			            name(), off); }

		virtual void write (Genode::uint16_t * reg,
		                    Genode::uint64_t   off) {
			throw Error("Device %s: halfword write of %llx not allowed",
			            name(), off); }

		virtual void read  (Genode::uint8_t  * reg,
		                    Genode::uint64_t   off) {
			throw Error("Device %s: byte-wise read of %llx not allowed",
			            name(), off); }

		virtual void write (Genode::uint8_t  * reg,
		                    Genode::uint64_t   off) {
			throw Error("Device %s: byte-wise write of %llx not allowed",
			            name(), off); }

		virtual void irq_enabled (unsigned irq) { }
		virtual void irq_disabled(unsigned irq) { }
		virtual void irq_handled (unsigned irq) { }

		void handle_memory_access(Cpu::State & state);


		/************************
		 ** Avl node interface **
		 ************************/

		bool higher(Device *d) { return d->addr() > addr(); }

		Device *find_by_addr(Genode::uint64_t a)
		{
			if ((a >= addr()) && (a < (addr()+size())))
				return this;

			Device *d = Avl_node<Device>::child(a > addr());
			return d ? d->find_by_addr(a) : nullptr;
		}
};

#endif /* _SRC__SERVER__VMM__DEVICE_H_ */
