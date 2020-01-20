/*
 * \brief  AHCI-port driver for ATA devices
 * \author Sebastian Sumpf
 * \date   2015-04-29
 */

/*
 * Copyright (C) 2015-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _ATA_DRIVER_H_
#define _ATA_DRIVER_H_

#include <base/log.h>
#include "ahci.h"
#include "util.h"

using namespace Genode;

/**
 * Return data of 'identify_device' ATA command
 */
struct Identity : Genode::Mmio
{
	Identity(Genode::addr_t base) : Mmio(base) { }

	struct Serial_number : Register_array<0x14, 8, 20, 8> { };
	struct Model_number : Register_array<0x36, 8, 40, 8> { };

	struct Queue_depth : Register<0x96, 16>
	{
		struct Max_depth : Bitfield<0, 5> { };
	};

	struct Sata_caps   : Register<0x98, 16>
	{
		struct Ncq_support : Bitfield<8, 1> { };
	};

	struct Sector_count : Register<0xc8, 64> { };

	struct Logical_block  : Register<0xd4, 16>
	{
		struct Per_physical : Bitfield<0,  3> { }; /* 2^X logical per physical */
		struct Longer_512   : Bitfield<12, 1> { };
		struct Multiple     : Bitfield<13, 1> { }; /* multiple logical blocks per physical */
	};

	struct Logical_words : Register<0xea, 32> { }; /* words (16 bit) per logical block */

	struct Alignment : Register<0x1a2, 16>
	{
		struct Logical_offset : Bitfield<0, 14> { }; /* offset first logical block in physical */
	};

	void info()
	{
		using Genode::log;

		log("  queue depth: ", read<Queue_depth::Max_depth>() + 1, " "
		    "ncq: ", read<Sata_caps::Ncq_support>());
		log("  numer of sectors: ", read<Sector_count>());
		log("  multiple logical blocks per physical: ",
		    read<Logical_block::Multiple>() ? "yes" : "no");
		log("  logical blocks per physical: ",
		    1U << read<Logical_block::Per_physical>());
		log("  logical block size is above 512 byte: ",
		    read<Logical_block::Longer_512>() ? "yes" : "no");
		log("  words (16bit) per logical block: ",
		    read<Logical_words>());
		log("  offset of first logical block within physical: ",
		    read<Alignment::Logical_offset>());
	}
};


/**
 * 16-bit word big endian device ASCII characters
 */
template <typename DEVICE_STRING>
struct String
{
	char buf[DEVICE_STRING::ITEMS + 1];

	String(Identity & info)
	{
		long j = 0;
		for (unsigned long i = 0; i < DEVICE_STRING::ITEMS; i++) {
			/* read and swap even and uneven characters */
			char c = (char)info.read<DEVICE_STRING>(i ^ 1);
			if (Genode::is_whitespace(c) && j == 0)
				continue;
			buf[j++] = c;
		}

		buf[j] = 0;

		/* remove trailing white spaces */
		while ((j > 0) && (buf[--j] == ' '))
			buf[j] = 0;
	}

	bool operator == (char const *other) const
	{
		return strcmp(buf, other) == 0;
	}

	void print(Genode::Output &out) const { Genode::print(out, (char const *)buf); }
	char const *cstring() { return buf; }
};

#if 0
/**
 * Commands to distinguish between ncq and non-ncq operation
 */
struct Io_command : Interface
{
	virtual void command(Port           &por,
	                     Command_table  &table,
	                     bool            read,
	                     Block::sector_t block_number,
	                     size_t          count,
	                     unsigned        slot) = 0;

	virtual void handle_irq(Port &port, Port::Is::access_t status) = 0;
};

struct Ncq_command : Io_command
{
	void command(Port           &port,
	             Command_table  &table,
	             bool            read,
	             Block::sector_t block_number,
	             size_t          count,
	             unsigned        slot) 
	{
		table.fis.fpdma(read, block_number, count, slot);
		/* ensure that 'Cmd::St' is 1 before writing 'Sact' */
		port.start();
		/* set pending */
		port.write<Port::Sact>(1U << slot);
	}
};

struct Dma_ext_command : Io_command
{
	void command(Port           &,
	             Command_table  &table,
	             bool            read,
	             Block::sector_t block_number,
	             size_t          count,
	             unsigned     /* slot */) 
	{
		table.fis.dma_ext(read, block_number, count);
};

#endif
/**
 * Drivers using ncq- and non-ncq commands
 */
struct Ata_protocol : Protocol, Noncopyable
{
	using block_number_t = Block::block_number_t;

	struct Request : Block::Request
	{
		bool valid() const { return operation.valid(); }
		void invalidate() { operation.type = Block::Operation::Type::INVALID; }

		Request & operator=(const Block::Request &request)
		{
			operation = request.operation;
			success = request.success;
			offset = request.offset;
			tag = request.tag;

			return *this;
		}
	};

	Util::Slots<Request, 32> slots { };

	typedef ::String<Identity::Serial_number> Serial_string;
	typedef ::String<Identity::Model_number>  Model_string;

	Genode::Constructible<Identity>      identity { };
	Genode::Constructible<Serial_string> serial   { };
	Genode::Constructible<Model_string>  model    { };

	unsigned init(Port &port) override
	{
		/* identify device */
		addr_t phys = Dataspace_client(port.device_info_ds).phys_addr();

		Command_table table(port.command_table_addr(0), phys, 0x1000);
		table.fis.identify_device();
		port.execute(0);

		port.wait_for_any(port.hba.delayer(), Port::Is::Dss::Equal(1),
		                                      Port::Is::Pss::Equal(1),
		                                      Port::Is::Dhrs::Equal(1));

		Genode::error("Identified ATA device: ", (unsigned)port.read<Port::Is>());
		identity.construct(port.device_info);
		serial.construct(*identity);
		model.construct(*identity);

		if (verbose) {
			Genode::log("  model number: ",  Genode::Cstring(model->buf));
			Genode::log("  serial number: ", Genode::Cstring(serial->buf));
			identity->info();
		}

		/* read number of command slots of ATA device */
		unsigned cmd_slots = identity->read<Identity::Queue_depth::Max_depth >() + 1;

		/* no native command queueing */
		if (!ncq_support(port))
			cmd_slots = 1;

		slots.limit((size_t)cmd_slots);
		port.ack_irq();

		return cmd_slots;
	}

	unsigned find_free_cmd_slot()
	{
#if 0
		for (unsigned slot = 0; slot < cmd_slots; slot++)
			if (!pending[slot].size())
				return slot;
  
		throw Block::Driver::Request_congestion();
#endif
		return 0;
	}
#if 0
	void ack_packets()
	{
		unsigned slots =  Port::read<Ci>() | Port::read<Sact>();

		for (unsigned slot = 0; slot < cmd_slots; slot++) {
			if ((slots & (1U << slot)) || !pending[slot].size())
				continue;

			Block::Packet_descriptor p = pending[slot];
			pending[slot] = Block::Packet_descriptor();
			ack_packet(p, true);
		}
	}
#endif

	bool overlap_check(Block::Request const &request)
	{
		block_number_t block_number = request.operation.block_number;
		block_number_t end = block_number + request.operation.count - 1;

		auto overlap_check = [&] (Request const &req) {
			block_number_t pending_start = req.operation.block_number;
			block_number_t pending_end   = pending_start + req.operation.count - 1;

			/* check if a pending packet overlaps */
			if ((block_number >= pending_start && block_number <= pending_end) ||
			    (end          >= pending_start && end          <= pending_end) ||
			    (pending_start >= block_number && pending_start <= end) ||
			    (pending_end   >= block_number && pending_end   <= end)) {

				Genode::warning("overlap: "
				                "pending ", pending_start,
				                " + ", req.operation.count, ", "
				                "request: ", block_number, " + ", request.operation.count);
				return true;
			}

			return false;
		};

		return slots.for_each(overlap_check);
	}

	void io(bool                      read,
	        Block::sector_t           block_number,
	        size_t                    count,
	        addr_t                    phys,
	        Block::Packet_descriptor &packet)
	{
#if 0
		sanity_check(block_number, count);
		overlap_check(block_number, count);

		unsigned slot = find_free_cmd_slot();
		pending[slot] = packet;

		/* setup fis */
		Command_table table(command_table_addr(slot), phys, count * block_size());

		/* set ATA command */
		//io_cmd->command(*this, table, read, block_number, count, slot);

		/* set or clear write flag in command header */
		Command_header header(command_header_addr(slot));
		header.write<Command_header::Bits::W>(read ? 0 : 1);
		header.clear_byte_count();

		execute(slot);
#endif
	}


	/*****************
	 ** Port_driver **
	 *****************/

	void handle_irq(Port &port)
	{
		Genode::log("ATA irq");
		/* ncg */
		if (ncq_support(port))
			while (Port::Is::Sdbs::get(port.read<Port::Is>()))
				port.ack_irq();
		/* normal dma */
		else if (Port::Is::Dma_ext_irq::get(port.read<Port::Is>()))
			port.ack_irq();

		port.stop();
	}

	bool ncq_support(Port &port)
	{
		return identity->read<Identity::Sata_caps::Ncq_support>() && port.hba.ncq();
	}

	Genode::size_t block_size() const 
	{
		Genode::size_t size = 512;

		if (identity->read<Identity::Logical_block::Longer_512>())
			size = identity->read<Identity::Logical_words>() / 2;

		return size;
	}

	Block::sector_t block_count() const 
	{
		return identity->read<Identity::Sector_count>();
	}

	/*****************************
	 ** Block::Driver interface **
	 *****************************/

	Block::Session::Info info() const override
	{
		return { .block_size  = block_size(),
		         .block_count = block_count(),
		         .align_log2  = log2(2ul), ///XXX: check
		         .writeable   = true };
	}

	Response submit(Port &port,Block::Request const request)
	{
		if (port.sanity_check(request) == false || port.dma_base == 0)
			return Response::REJECTED;

		if (overlap_check(request))
			return Response::RETRY;

		Request *r = slots.get();

		if (r == nullptr)
			return Response::RETRY;

		log("Request: ", request.operation, " valid: ", r->valid(), " index: ", slots.index(*r));
		*r = request;

		Block::Operation op = request.operation;
		size_t slot         = slots.index(*r);

		/* setup fis */
		Command_table table(port.command_table_addr(slot),
		                    port.dma_base + request.offset, /* physical address */
		                    op.count * block_size());

		/* setup ATA command */
		bool read = op.type == Block::Operation::Type::READ;

		if (ncq_support(port)) {
			table.fis.fpdma(read, op.block_number, op.count, slot);
			/* ensure that 'Cmd::St' is 1 before writing 'Sact' */
			port.start();
			/* set pending */
			port.write<Port::Sact>(1U << slot);
		} else {
			table.fis.dma_ext(read, op.block_number, op.count);
		}

		/* set or clear write flag in command header */
		Command_header header(port.command_header_addr(slot));
		header.write<Command_header::Bits::W>(read ? 0 : 1);
		header.clear_byte_count();

		port.execute(slot);

		return Response::ACCEPTED;
	}

	Block::Request completed(Port &port, size_t const index)
	{
		Request *request     = slots.pending(index);
		unsigned slot_states = port.read<Port::Ci>() | port.read<Port::Sact>();

		/* request not active or still pending */
		if (request == nullptr || (slot_states & (1u << index)))
			return Block::Request();

		Block::Request r = *request;
		request->invalidate();

		return r;
	}
};

#endif /* _ATA_DRIVER_H_ */
