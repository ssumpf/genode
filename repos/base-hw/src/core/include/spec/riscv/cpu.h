/*
 * \brief  CPU driver for core
 * \author Martin stein
 * \date   2011-11-03
 */

/*
 * Copyright (C) 2011-2013 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#ifndef _CPU_H_
#define _CPU_H_

#include <base/stdint.h>
#include <cpu/cpu_state.h>

namespace Genode
{
	/** * Part of CPU state that is not switched on every mode transition
	 */
	class Cpu_lazy_state { };

	/**
	 * CPU driver for core
	 */
	class Cpu;

	typedef __uint128_t sizet_arithm_t;
}

namespace Kernel 
{
	using Genode::Cpu_lazy_state;
	class Pd;
}

class Genode::Cpu
{
	public:

		static constexpr addr_t mtc_size = 0x1000;
		static constexpr addr_t exception_entry = (~0ULL) & ~(0xfff);

		/**
		 * Extend basic CPU state by members relevant for 'base-hw' only
		 */
		struct Context : Cpu_state
		{
			addr_t sptbr = 0; /* supervisor page table register */

			/**
			 * Return base of assigned translation table
			 */
			addr_t translation_table() const {
				return sptbr; }

			/**
			 * Assign translation-table base 'table'
			 */
			void translation_table(addr_t const table) {
				sptbr = table; }

			/**
			 * Assign protection domain
			 */
			void protection_domain(Genode::uint8_t const id)
			{
				asm volatile("csrw sasid, %0" : : "r"(id));
			}
		};

		struct Pd
		{
			Genode::uint8_t asid; /* address space id */

			Pd(Genode::uint8_t id) : asid(id) {}
		};

		/**
		 * An usermode execution state
		 */
		struct User_context : Context
		{
			/**
			 * Constructor
			 */
			User_context();

			/**
			 * Support for kernel calls
			 */
			void user_arg_0(unsigned const arg) { PDBG("not impl"); }
			void user_arg_1(unsigned const arg) { PDBG("not impl"); }
			void user_arg_2(unsigned const arg) { PDBG("not impl"); }
			void user_arg_3(unsigned const arg) { PDBG("not impl"); }
			void user_arg_4(unsigned const arg) { PDBG("not impl"); }
			void user_arg_5(unsigned const arg) { PDBG("not impl"); }
			void user_arg_6(unsigned const arg) { PDBG("not impl"); }
			void user_arg_7(unsigned const arg) { PDBG("not impl"); }
			addr_t user_arg_0() const { PDBG("not impl"); return 0; }
			addr_t user_arg_1() const { PDBG("not impl"); return 0; }
			addr_t user_arg_2() const { PDBG("not impl"); return 0; }
			addr_t user_arg_3() const { PDBG("not impl"); return 0; }
			addr_t user_arg_4() const { PDBG("not impl"); return 0; }
			addr_t user_arg_5() const { PDBG("not impl"); return 0; }
			addr_t user_arg_6() const { PDBG("not impl"); return 0; }
			addr_t user_arg_7() const { PDBG("not impl"); return 0; }

			/**
			 * Initialize thread context
			 *
			 * \param table  physical base of appropriate translation table
			 * \param pd_id  kernel name of appropriate protection domain
			 */
			void init_thread(addr_t const table, unsigned const pd_id)
			{
				protection_domain(pd_id);
				translation_table(table);
			}

			/**
			 * Return if the context is in a page fault due to translation miss
			 *
			 * \param va  holds the virtual fault-address if call returns 1
			 * \param w   holds wether it's a write fault if call returns 1
			 */
			bool in_fault(addr_t & va, addr_t & w) const
			{
				PDBG("not impl");
				return false;
			}
		};

		static void wait_for_interrupt() { asm volatile ("wfi"); };


		/**
		 * Ensure that TLB insertions get applied
		 */
		static void tlb_insertions() { PDBG("not impl"); }

		/**
		 * Return wether to retry an undefined user instruction after this call
		 */
		bool retry_undefined_instr(Cpu_lazy_state *) { return false; }

		/**
		 * Post processing after a translation was added to a translation table
		 *
		 * \param addr  virtual address of the translation
		 * \param size  size of the translation
		 */
		static void translation_added(addr_t const addr, size_t const size)
		{
			PDBG("not impl");
		}

		/**
		 * Return kernel name of the executing CPU
		 */
		static unsigned executing_id() { return primary_id(); }

		/**
		 * Return kernel name of the primary CPU
		 */
		static unsigned primary_id() { return 0; }

		static void flush_tlb_by_pid(unsigned const pid)
		{
			PDBG("not impl");
		}

		/**
		 * Set page table
		 */
		static void init_virt_kernel(Kernel::Pd * pd);
		static void init_phys_kernel();

		/*************
		 ** Dummies **
		 *************/

		static void prepare_proceeding(Cpu_lazy_state *, Cpu_lazy_state *) { }

		static void start_secondary_cpus(void * const ip) { }

		static void invalidate_instr_caches() { }

		static void invalidate_data_caches() { }
		static void flush_data_caches() { }
		static void
		flush_data_caches_by_virt_region(addr_t base, size_t const size) { }
		static void
		invalidate_instr_caches_by_virt_region(addr_t base, size_t const size) { }

		static void data_synchronization_barrier()
		{
			asm volatile ("fence\n" : : : "memory");
		}

};

#endif /* _CPU_H_ */
