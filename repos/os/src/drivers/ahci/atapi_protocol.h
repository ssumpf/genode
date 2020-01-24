/*
 * \brief  AHCI-port driver for ATAPI devices
 * \author Sebastian Sumpf
 * \date   2015-04-29
 */

/*
 * Copyright (C) 2015-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _AHCI__ATAPI_PROTOCOL_H_
#define _AHCI__ATAPI_PROTOCOL_H_

#include "ahci.h"
#include <util/endian.h>

namespace Atapi {
class Protocol;
using namespace Ahci;
using namespace Genode;
}

class Atapi::Protocol : public Ahci::Protocol, Noncopyable
{
	private:

		Block::Request _pending { };

#if 0
	Atapi_driver(Genode::Ram_allocator &ram,
	             Ahci_root             &root,
	             unsigned              &sem,
	             Genode::Region_map    &rm,
	             Hba                   &hba,
	             Platform::Hba         &platform_hba,
	             unsigned               number)
	: Port_driver(ram, root, sem, rm, hba, platform_hba, number)
	{
		Port::init();
		Port::write<Cmd::Atapi>(1);
		read_sense();
	}
#endif

		size_t _block_size() const
		{
			return 2048;
		}

		size_t _block_count() const
		{
			return 0;
		}

		void _atapi_command(Port &port)
		{
			Command_header header(port.command_header_addr(0));
			header.atapi_command();
			header.clear_byte_count();
			port.execute(0);
		}

		void _read_sense(Port &port)
		{
			addr_t phys   = Dataspace_client(port.device_info_ds).phys_addr();

			Command_table table(port.command_table_addr(0), phys, 0x1000);
			table.fis.atapi();
			table.atapi_cmd.read_sense();

			_atapi_command(port);
		}

		void _test_unit_ready(Port &port)
		{
			Command_table table(port.command_table_addr(0), 0, 0);
			table.fis.atapi();
			table.atapi_cmd.test_unit_ready();

			_atapi_command(port);
		}

		void _read_capacity(Port &port)
		{
			addr_t phys = Dataspace_client(port.device_info_ds).phys_addr();

			Command_table table(port.command_table_addr(0), phys, 0x1000);
			table.fis.atapi();
			table.atapi_cmd.read_capacity();

			_atapi_command(port);
		}

	public:

		unsigned init(Port &port) override
		{
			port.write<Port::Cmd::Atapi>(1);

			/* read sense */
			retry<Port::Polling_timeout>(
				[&] {
					_read_sense(port);
					port.wait_for_any(port.hba.delayer(),
					                  Port::Is::Dss::Equal(1), Port::Is::Pss::Equal(1),
					                  Port::Is::Dhrs::Equal(1));
					port.ack_irq();

						/* test unit ready */
					_test_unit_ready(port);
					port.wait_for(port.hba.delayer(), Port::Is::Dhrs::Equal(1));
					log("Unit ready");

					Device_fis f(port.fis_base);
					log("Status: ", f.read<Device_fis::Status::Device_ready>(), " E: ", f.read<Device_fis::Error>());
					port.ack_irq();

					/* check if devic is ready */
					if (!f.read<Device_fis::Status::Device_ready>() || f.read<Device_fis::Error>())
						throw Port::Polling_timeout();

					_read_capacity(port);
					port.wait_for_any(port.hba.delayer(),
					                  Port::Is::Dss::Equal(1), Port::Is::Pss::Equal(1),
					                  Port::Is::Dhrs::Equal(1));
					port.ack_irq();
				},
				[&] {}, 3);
			log("DONE");

			return 1;
		}

		Block::Session::Info info() const override
		{
			return { .block_size  = _block_size(),
			         .block_count = _block_count(),
			         .align_log2  = 1,
			         .writeable   = false };
		}

		void handle_irq(Port &port) override
		{
		}

		Response submit(Port &port, Block::Request const request) override
		{
			return Response::REJECTED;
		}

		Block::Request completed(Port &port, size_t const index) override
		{
			return Block::Request();
		}

#if 0
	void atapi_command()
	{
		Command_header header(command_header_addr(0));
		header.atapi_command();
		header.clear_byte_count();
		execute(0);
	}

	void test_unit_ready()
	{
		state = TEST_READY;

		Command_table table(command_table_addr(0), 0, 0);
		table.fis.atapi();
		table.atapi_cmd.test_unit_ready();

		atapi_command();
	}

	void read_sense()
	{
		state = STATUS;

		if (sense_tries++ >= 3) {
			Genode::error("could not power up device");
			state_change();
			return;
		}

		addr_t phys   = (addr_t)Dataspace_client(device_info_ds).phys_addr();

		Command_table table(command_table_addr(0), phys, 0x1000);
		table.fis.atapi();
		table.atapi_cmd.read_sense();

		atapi_command();
	}

	void read_capacity()
	{
		state       = IDENTIFY;
		addr_t phys = (addr_t)Dataspace_client(device_info_ds).phys_addr();

		Command_table table(command_table_addr(0), phys, 0x1000);
		table.fis.atapi();
		table.atapi_cmd.read_capacity();

		atapi_command();
	}

	void ack_packets()
	{
		unsigned slots = Port::read<Ci>();

		if (slots & 1 || !pending.size())
			return;

		Block::Packet_descriptor p = pending;
		pending  = Block::Packet_descriptor();
		ack_packet(p, true);
	}


	/*****************
	 ** Port_driver **
	 *****************/

	void handle_irq() override
	{
		Is::access_t status = Port::read<Is>();

		if (verbose) {
			Genode::log("irq: "
			            "is: ",    Genode::Hex(status), " "
			            "ci: ",    Genode::Hex(Port::read<Ci>()), " "
			            "state: ", (int)state);
			Device_fis f(fis_base);
			Genode::log("d2h: "
			            "status: ", f.read<Device_fis::Status>(), " "
			            "error: ", Genode::Hex(f.read<Device_fis::Error>()));
		}

		ack_irq();

		if (state == TEST_READY && Port::Is::Dhrs::get(status)) {
			Device_fis f(fis_base);

			/* check if devic is ready */
			if (f.read<Device_fis::Status::Device_ready>() && !f.read<Device_fis::Error>())
				read_capacity();
			else
				read_sense();
		}

		if (state == READY && Port::Is::Dhrs::get(status)) {
			ack_packets();
		}

		if (Port::Is::Dss::get(status) || Port::Is::Pss::get(status)) {
			switch (state) {

				case STATUS:
					test_unit_ready();
					break;

				case IDENTIFY:
					state = READY;
					state_change();
					break;

				case READY:
					ack_packets();
					return;

				default:
					break;
			}
		}
	}

	Block::Session::Info info() const override
	{
		return { .block_size  = block_size(),
		         .block_count = block_count(),
		         .align_log2  = 11,
		         .writeable   = false };
	}


	/*****************************
	 ** Block::Driver interface **
	 *****************************/

	bool dma_enabled() override { return true; };

	Genode::size_t block_size() const override
	{
		return host_to_big_endian(((unsigned *)device_info)[1]);
	}

	Block::sector_t block_count() const override
	{
		return host_to_big_endian(((unsigned *)device_info)[0]) + 1;
	}

	void read_dma(Block::sector_t           block_number,
	              size_t                    count,
	              addr_t                    phys,
	              Block::Packet_descriptor &packet) override
	{
		if (pending.size())
			throw Block::Driver::Request_congestion();

		sanity_check(block_number, count);

		pending = packet;

		if (verbose)
			Genode::log("add packet read ", block_number, " count ", count, " -> 0");

		/* setup fis */
		Command_table table(command_table_addr(0), phys, count * block_size());
		table.fis.atapi();

		/* setup atapi command */
		table.atapi_cmd.read10(block_number, count);

		/* set and clear write flag in command header */
		Command_header header(command_header_addr(0));
		header.write<Command_header::Bits::W>(0);
		header.clear_byte_count();

		/* set pending */
		execute(0);
	}
#endif
};

#endif /* _AHCI__ATAPI_PROTOCOL_H_ */
