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

#include <cpu.h>
#include <pl011.h>

void Pl011::_out_char(unsigned char c) {
	_terminal.write(&c, 1);
}


unsigned char Pl011::_get_char()
{
	_ris &= ~RX_MASK;

	if (!_rx_buf.empty()) return _rx_buf.get();

	return 0;
}


Genode::uint16_t Pl011::_get(Genode::uint64_t off)
{
	switch (off) {
	case UARTDR:        return _get_char();
	case UARTPERIPHID0: return 0x11;
	case UARTPERIPHID1: return 0x10;
	case UARTPERIPHID2: return 0x14;
	case UARTPERIPHID3: return 0x0;
	case UARTPCELLID0:  return 0xd;
	case UARTPCELLID1:  return 0xf0;
	case UARTPCELLID2:  return 0x5;
	case UARTPCELLID3:  return 0xb1;
	case UARTFR:        return _rx_buf.empty() ? 16 : 64;
	case UARTCR:        return _cr;
	case UARTIMSC:      return _imsc;
	case UARTRIS:       return _ris;
	case UARTMIS:       return _ris & _imsc;
	case UARTFBRD:      return _fbrd;
	case UARTIBRD:      return _ibrd;
	case UARTLCR_H:     return _lcr_h;
	default:
		throw Wrong_offset();
	};
}


void Pl011::_mask_irqs(Genode::uint32_t mask)
{
	if ((mask & RX_MASK) && !(_imsc & RX_MASK) && (_ris & RX_MASK))
		_irq.assert();

	_imsc = mask;
}


void Pl011::_read()
{
	if (!_terminal.avail()) return;

	while (_terminal.avail()) {
		unsigned char c = 0;
		_terminal.read(&c, 1);
		_rx_buf.add(c);
	}

	_ris |= RX_MASK;
	if (_imsc & RX_MASK) _irq.assert();
}


Pl011::Pl011(const char * const       name,
             const Genode::uint64_t   addr,
             const Genode::uint64_t   size,
             Cpu                     &cpu,
             Gic::Irq                &irq,
             Genode::Env             &env)
: Device(name, addr, size),
  _terminal(env),
  _handler(cpu, env.ep(), *this, &Pl011::_read),
  _irq(irq)
{
	_terminal.read_avail_sigh(_handler);
}


void Pl011::read(Genode::uint16_t * reg, Genode::uint64_t off, Cpu&)
{
	try {
		*reg = _get(off);
	} catch(Wrong_offset &e) {
		throw Error("UART: halfword read of offset %llx", off);
	}
}


void Pl011::write(Genode::uint8_t * reg, Genode::uint64_t off, Cpu&)
{
	if (off != UARTDR)
		throw Error("UART: byte write %x to offset %llx",
		            *reg, off);
	_terminal.write(reg, 1);
}


void Pl011::write(Genode::uint16_t * reg, Genode::uint64_t off, Cpu&)
{
	switch (off) {
	case UARTDR:
		_terminal.write(reg, 1);
		return;
	case UARTFBRD:
		_fbrd = *reg;
		return;
	case UARTIMSC:
		_mask_irqs(*reg);
		return;
	case UARTIBRD:
		_ibrd = *reg;
		return;
	case UARTLCR_H:
		_lcr_h = *reg;
		return;
	case UARTICR:
		_ris = _ris & ~*reg;
		return;
	case UARTCR:
		_cr = *reg;
		return;
	case UARTIFLS:
		return;
	default:
		throw Error("UART: halfword write %x to offset %llx",
		            *reg, off);
	};
}
