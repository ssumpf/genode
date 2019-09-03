/*
 * \brief  VMM PL011 serial device model
 * \author Stefan Kalkowski
 * \date   2019-07-18
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__SERVER__VMM__PL011_H_
#define _SRC__SERVER__VMM__PL011_H_

#include <terminal_session/connection.h>

#include <device.h>
#include <gic.h>

class Cpu;

class Pl011 : public Device
{
	private:

		using Ring_buffer =
			Genode::Ring_buffer<char, 1024,
			                    Genode::Ring_buffer_unsynchronized>;

		class Wrong_offset {};

		enum {
			UARTDR        = 0x0,
			UARTFR        = 0x18,
			UARTIBRD      = 0x24,
			UARTFBRD      = 0x28,
			UARTLCR_H     = 0x2c,
			UARTCR        = 0x30,
			UARTIFLS      = 0x34,
			UARTIMSC      = 0x38,
			UARTMIS       = 0x40,
			UARTICR       = 0x44,
			UARTPERIPHID0 = 0xfe0,
			UARTPERIPHID1 = 0xfe4,
			UARTPERIPHID2 = 0xfe8,
			UARTPERIPHID3 = 0xfec,
			UARTPCELLID0  = 0xff0,
			UARTPCELLID1  = 0xff4,
			UARTPCELLID2  = 0xff8,
			UARTPCELLID3  = 0xffc,
		};

		Terminal::Connection       _terminal;
		Cpu::Signal_handler<Pl011> _handler;
		Gic::Irq                  &_irq;
		Ring_buffer                _rx_buf;
		Genode::uint16_t           _ibrd  = 0;
		Genode::uint16_t           _fbrd  = 0;
		Genode::uint16_t           _lcr_h = 0;
		Genode::uint16_t           _imsc  = 0b1111;
		Genode::uint16_t           _ris   = 0;
		Genode::uint16_t           _cr    = 0x300;

		void             _out_char(unsigned char c);
		unsigned char    _get_char();
		Genode::uint16_t _get(Genode::uint64_t off);
		void             _mask_irqs(Genode::uint32_t mask);
		void             _read();

		using Error = Exception;

	public:

		Pl011(const char * const       name,
		      const Genode::uint64_t   addr,
		      const Genode::uint64_t   size,
		      Cpu                     &cpu,
		      Gic::Irq                &irq,
		      Genode::Env             &env);

		void read(Genode::uint16_t * reg, Genode::uint64_t off,
		          Cpu & cpu) override;
		void read(Genode::uint32_t * reg, Genode::uint64_t off,
		          Cpu & cpu) override {
			read((Genode::uint16_t*) reg, off, cpu); }

		void write(Genode::uint8_t * reg, Genode::uint64_t off,
		           Cpu & cpu) override;
		void write(Genode::uint16_t * reg, Genode::uint64_t off,
		           Cpu & cpu) override;
};

#endif /* _SRC__SERVER__VMM__PL011_H_ */
