/*
 * \brief  Programmable interrupt controller for core
 * \author Stefan Kalkowski
 * \date   2012-10-24
 */

/*
 * Copyright (C) 2012-2013 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#ifndef _PIC_H_
#define _PIC_H_

#include <base/printf.h>

namespace Genode
{
	/**
	 * Programmable interrupt controller for core
	 */
	class Pic;
}

class Genode::Pic
{
	public:

		enum {
			/*
			 * FIXME: dummy ipi value on non-SMP platform, should be removed
			 *        when SMP is an aspect of CPUs only compiled where necessary
			 */
			IPI       = 0,
			NR_OF_IRQ = 15,
		};

		/**
		 * Constructor
		 */
		Pic() { PDBG("not impl"); }

		/**
		 * Receive a pending request number 'i'
		 */
		bool take_request(unsigned & i)
		{
			PDBG("not impl");
			return false;
		}

		/**
		 * Validate request number 'i'
		 */
		bool valid(unsigned const i) const { return i < NR_OF_IRQ; }

		/**
		 * Unmask interrupt 'i'
		 */
		void unmask(unsigned const i, unsigned) {
			PDBG("not impl"); }

		/**
		 * Mask interrupt 'i'
		 */
		void mask(unsigned const i) {
			PDBG("not impl"); }

		/*************
		 ** Dummies **
		 *************/

		void trigger_ip_interrupt(unsigned) { }
		void init_cpu_local() { }
		void finish_request() { }
};

namespace Kernel { class Pic : public Genode::Pic { }; }

#endif /* _PIC_H_ */
