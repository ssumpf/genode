/*
 * \brief  VMM ARM Generic Interrupt Controller device model
 * \author Stefan Kalkowski
 * \date   2019-08-05
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__SERVER__VMM__GIC_H_
#define _SRC__SERVER__VMM__GIC_H_

#include <device.h>
#include <exception.h>
#include <base/env.h>
#include <drivers/defs/arm_v7.h>
#include <util/list.h>
#include <util/register.h>
#include <util/reconstructible.h>

class Gic : public Device
{
	public:

		enum Irqs {
			MAX_SGI  = 16,
			MAX_PPI  = 16,
			MAX_SPI  = 992,
			MAX_IRQ  = 1020,
			SPURIOUS = 1023,
		};

		class Irq : public Genode::List<Irq>::Element
		{
			public:

				struct List : Genode::List<Irq>
				{
					void insert(Irq & irq);
					Irq * highest_enabled();
				};

				struct Irq_handler {
					virtual void eoi()   {};
					virtual void level() {};
				};

				enum Type   { SGI, PPI, SPI };
				enum State  { INACTIVE, ACTIVE, PENDING, ACTIVE_PENDING };
				enum Config { LEVEL, EDGE };

				Irq(unsigned num, Type t, List &pending_list);

				bool     enabled() const;
				bool     active()  const;
				bool     pending() const;
				bool     level()   const;
				unsigned number()  const;
				Genode::uint8_t priority() const;
				Genode::uint8_t target() const;

				void enable();
				void disable();
				void activate();
				void deactivate();
				void assert();
				void deassert();
				void level(bool l);
				void priority(Genode::uint8_t p);
				void target(Genode::uint8_t t);
				void handler(Irq_handler & handler);

			private:

				Irq(Irq const &);
				Irq &operator = (Irq const &);

				bool            _enabled { false    };
				Type            _type    { SPI      };
				State           _state   { INACTIVE };
				Config          _config  { LEVEL    };
				unsigned        _num     { 0 };
				Genode::uint8_t _prio    { 0 };
				Genode::uint8_t _target  { 1 };
				List          & _pending_list;
				Irq_handler   * _handler { nullptr };
		};

		struct Gicd_banked
		{
			Cpu                      & cpu;
			Gic                      & gic;
			Genode::Constructible<Irq> sgi[MAX_SGI];
			Genode::Constructible<Irq> ppi[MAX_PPI];
			Irq::List                  pending_list;

			Gicd_banked(Cpu & cpu, Gic & gic);

			template <typename func>
			void for_each_sgi(func const &fn) {
				for (unsigned i = 0; i < MAX_SGI; i++) fn(*sgi[i]); }

			template <typename FUNC>
			void for_each_ppi(FUNC const &fn) {
				for (unsigned i = 0; i < MAX_PPI; i++) fn(*ppi[i]); }

			template <typename FUNC>
			void for_each(FUNC const &fn)
			{
				for_each_sgi(fn);
				for_each_ppi(fn);
			}

			template <typename func>
			void for_range_irq(Genode::uint64_t off, Genode::uint32_t reg,
			                   unsigned irq_per_reg, func const &fn)
			{
				unsigned idx = (off - reg) / 4 * irq_per_reg;
				for (unsigned i = 0; i < irq_per_reg; i++)
					fn((idx >= MAX_SGI) ? *ppi[i+idx-MAX_SGI]
					                    : *sgi[i+idx]);
			}

			void handle_irq();
			bool pending_irq();
		};

		Gic(const char * const     name,
		    const Genode::uint64_t   addr,
		    const Genode::uint64_t   size,
		    Genode::Env            & env);

		void read(Genode::uint32_t * reg, Genode::uint64_t off,
		          Cpu & cpu) override;
		void write(Genode::uint32_t * reg, Genode::uint64_t off,
		           Cpu & cpu) override;

		Irq & spi(unsigned num);

	private:

		friend struct Gicd_banked;

		enum Offsets {
			GICD_CTLR        = 0x0,
			GICD_TYPER       = 0x4,
			GICD_IIDR        = 0x8,
			GICD_ISENABLER0  = 0x100,
			GICD_ISENABLER1  = 0x104,
			GICD_ICENABLER0  = 0x180,
			GICD_ICENABLER1  = 0x184,
			GICD_ISPENDR0    = 0x200,
			GICD_ISPENDR1    = 0x204,
			GICD_ICPENDR0    = 0x280,
			GICD_ICPENDR1    = 0x284,
			GICD_ISACTIVER0  = 0x300,
			GICD_ISACTIVER1  = 0x304,
			GICD_ICACTIVER0  = 0x380,
			GICD_ICACTIVER1  = 0x384,
			GICD_IPRIORITYR0 = 0x400,
			GICD_IPRIORITYR8 = 0x420,
			GICD_ITARGETSR0  = 0x800,
			GICD_ITARGETSR8  = 0x820,
			GICD_ICFGR0      = 0xc00,
			GICD_ICFGR1      = 0xc04,
			GICD_ICFGR2      = 0xc08,
			GICD_SGIR        = 0xf00,
			GICD_CPENDSGIR0  = 0xf10,
			GICD_SPENDSGIR0  = 0xf20,
		};

		static unsigned _reg_idx(Offsets reg_off, Genode::uint64_t off) {
			return (off - reg_off) / 4; }

		static unsigned _reg_offset(Offsets off, unsigned irq, unsigned bits) {
			return off + 4 * ((irq * bits) / 32); }

		static bool _in_reg_range(Genode::uint64_t off, Offsets reg_off,
		                          unsigned irq, unsigned bits) {
			return off >= reg_off && off < _reg_offset(reg_off, irq, bits); }

		struct Ctlr : Genode::Register<32>
		{
			struct Enable : Bitfield<0, 1> {};
		};

		struct Typer : Genode::Register<32>
		{
			struct It_lines_number : Bitfield<0, 5> {};
			struct Cpu_number      : Bitfield<5, 3> {};
		};

		struct Iidr : Genode::Register<32>
		{
			struct Implementer : Bitfield<0, 12> {};
			struct Revision    : Bitfield<12, 4> {};
			struct Variant     : Bitfield<16, 4> {};
			struct Product_id  : Bitfield<24, 8> {};
		};

		bool                       _enabled { false };
		Genode::Constructible<Irq> _spi[MAX_SPI];
		Irq::List                  _pending_list;
		unsigned                   _cpu_cnt { 1 };

		void _enable();
		void _disable();

		template <typename func>
		void _for_range_spi(Genode::uint64_t off, Genode::uint32_t reg,
		                    unsigned irq_per_reg, func const &fn)
		{
			unsigned idx = (off - reg) / 4 * irq_per_reg;
			for (unsigned i = 0; i < irq_per_reg; i++) fn(*_spi[i+idx]);
		}
};

#endif /* _SRC__SERVER__VMM__GIC_H_ */
