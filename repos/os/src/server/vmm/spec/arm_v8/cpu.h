/*
 * \brief  VMM cpu object
 * \author Stefan Kalkowski
 * \date   2019-07-18
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__SERVER__VMM__CPU_H_
#define _SRC__SERVER__VMM__CPU_H_

#include <exception.h>
#include <generic_timer.h>

#include <base/env.h>
#include <base/heap.h>
#include <cpu/vm_state_virtualization.h>
#include <util/mmio.h>
#include <vm_session/connection.h>

class Vmm;

class Cpu
{
	public:

		struct Esr : Genode::Register<32>
		{
			struct Ec : Bitfield<26, 6>
			{
				enum {
					WFI     = 0x1,
					HVC     = 0x16,
					MRS_MSR = 0x18,
					DA      = 0x24
				};
			};
		};

		using State = Genode::Vm_state;

		enum Exception_type {
			AARCH64_SYNC   = 0x400,
			AARCH64_IRQ    = 0x480,
			AARCH64_FIQ    = 0x500,
			AARCH64_SERROR = 0x580,
			AARCH32_SYNC   = 0x600,
			AARCH32_IRQ    = 0x680,
			AARCH32_FIQ    = 0x700,
			AARCH32_SERROR = 0x780,
			NO_EXCEPTION   = 0xffff
		};

		class System_register : public Genode::Avl_node<System_register>
		{
			private:

				const Esr::access_t       _encoding;
				const char               *_name;
				const bool                _writeable;
				Genode::uint64_t          _value;

			public:

				struct Iss : Esr
				{
					struct Direction : Bitfield<0,  1> {};
					struct Crm       : Bitfield<1,  4> {};
					struct Register  : Bitfield<5,  4> {};
					struct Crn       : Bitfield<10, 4> {};
					struct Opcode1   : Bitfield<14, 3> {};
					struct Opcode2   : Bitfield<17, 3> {};
					struct Opcode0   : Bitfield<20, 2> {};

					static access_t value(unsigned op0,
					                      unsigned crn,
					                      unsigned op1,
					                      unsigned crm,
					                      unsigned op2);

					static access_t mask_encoding(access_t v);
				};

				System_register(unsigned         op0,
				                unsigned         crn,
				                unsigned         op1,
				                unsigned         crm,
				                unsigned         op2,
				                const char     * name,
				                bool             writeable,
				                Genode::addr_t   v,
				                Genode::Avl_tree<System_register> & tree);

				const char * name()       const { return _name;      }
				const bool   writeable()  const { return _writeable; }

				System_register * find_by_encoding(Iss::access_t e)
				{
					if (e == _encoding) return this;

					System_register * r =
						Avl_node<System_register>::child(e > _encoding);
					return r ? r->find_by_encoding(e) : nullptr;
				}

				void write(Genode::addr_t v) { _value = (Genode::uint32_t)v; }

				Genode::addr_t read() const { return (Genode::addr_t)(_value); }


				/************************
				 ** Avl node interface **
				 ************************/

				bool higher(System_register *r) {
					return (r->_encoding > _encoding); }
		};

		struct Dbgbvr : System_register
		{
			Dbgbvr(unsigned num, Genode::Avl_tree<System_register> & tree)
			: System_register(2, 0, 0, num, 4, "DBGBVR_EL1", true, 0x0, tree) {}
		};

		struct Dbgbcr : System_register
		{
			Dbgbcr(unsigned num, Genode::Avl_tree<System_register> & tree)
			: System_register(2, 0, 0, num, 5, "DBGBCR_EL1", true, 0x0, tree) {}
		};

	private:

		unsigned                          _cpu_id;
		Vmm                             & _vmm;
		Genode::Vm_connection           & _vm;
		Genode::Heap                    & _heap;
		Genode::Vm_session::Vcpu_id       _vcpu_id;
		State                           & _state;
		bool                              _active { true };
		Genode::Avl_tree<System_register> _reg_tree;
		System_register                   _sr_ctr;
		Genode::Constructible<Dbgbcr>     _sr_dbgbcr[16];
		Genode::Constructible<Dbgbvr>     _sr_dbgbvr[16];
		System_register                   _sr_mdscr;
		System_register                   _sr_osdlr;
		System_register                   _sr_oslar;
		Gic::Gicd_banked                  _gic;
		Generic_timer                     _timer;

		bool _handle_sys_reg();
		void _handle_wfi();
		void _handle_sync();
		void _handle_irq();
		void _update_state();

	public:

		Cpu(Vmm                     & vmm,
		    Genode::Vm_connection   & vm,
		    Gic                     & gic,
		    Genode::Env             & env,
		    Genode::Heap            & heap,
		    Genode::Vm_handler_base & handler,
		    Genode::addr_t            ip,
		    Genode::addr_t            dtb);

		unsigned cpu_id() const   { return _cpu_id;                 }
		void run()                { if (_active) _vm.run(_vcpu_id); }
		void pause()              { _vm.pause(_vcpu_id);            }
		bool active()             { return _active;                 }
		State & state() const     { return _state;                  }
		Gic::Gicd_banked & gic()  { return _gic;                    }
		void dump();

		template <typename FUNC>
		void handle_signal(FUNC handler)
		{
			if (_active) {

				pause();

				/* check exception reason */
				switch (_state.exception_type) {
				case NO_EXCEPTION:                 break;
				case AARCH64_IRQ:  _handle_irq();  break;
				case AARCH64_SYNC: _handle_sync(); break;
				default:
					throw Exception("Curious exception ",
					                _state.exception_type, " occured");
				}
			}

			handler();

			_update_state();

			if (_active) run();
		}

		template <typename T>
		struct Signal_handler : Genode::Vm_handler<Signal_handler<T>>
		{
			using Base = Genode::Vm_handler<Signal_handler<T>>;

			Cpu & cpu;
			T   & obj;
			void (T::*member)();

			void handle()
			{
				try {
					cpu.handle_signal([this] () { (obj.*member)(); });
				} catch(Exception &e) {
					e.print();
					cpu.dump();
				}
			}

			Signal_handler(Cpu                & cpu,
			               Genode::Entrypoint & ep,
			               T                  & o,
			               void                 (T::*f)())
			: Base(ep, *this, &Signal_handler::handle),
			  cpu(cpu), obj(o), member(f) {}
		};
};

#endif /* _SRC__SERVER__VMM__CPU_H_ */
