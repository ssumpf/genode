/**
 * \brief  Block driver session creation
 * \author Sebastian Sumpf
 * \date   2015-09-29
 */

/*
 * Copyright (C) 2016-2020 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* Genode includes */
#include <base/attached_rom_dataspace.h>
#include <base/component.h>
#include <base/log.h>
#include <block/request_stream.h>
#include <os/session_policy.h>
#include <timer_session/connection.h>
#include <util/xml_node.h>
#include <os/reporter.h>

/* local includes */
#include <ahci.h>
#include <ata_protocol.h>

namespace Ahci {
	using namespace Genode;
	struct Dispatch;
	struct Driver;
	struct Main;
	struct Block_session_handler;
	struct Block_session_component;
}


struct Ahci::Dispatch
{
	virtual void session(unsigned index) = 0;
};


struct Ahci::Driver : Noncopyable
{
	Env      &env;
	Dispatch &dispatch;

	/* read device signature */
	enum Signature {
		ATA_SIG        = 0x101,
		ATAPI_SIG      = 0xeb140101,
		ATAPI_SIG_QEMU = 0xeb140000, /* will be fixed in Qemu */
	};

	enum {  MAX_PORTS = 32 };

	struct Timer_delayer : Mmio::Delayer, Timer::Connection
	{
		Timer_delayer(Genode::Env &env)
		: Timer::Connection(env) { }

		void usleep(uint64_t us) override { Timer::Connection::usleep(us); }
	} _delayer { env };

	Hba            hba          { env, _delayer };

  Constructible<Ata_protocol> ata[MAX_PORTS];
	Constructible<Port>         ports[MAX_PORTS];

	Signal_handler<Driver> irq { env.ep(), *this, &Driver::handle_irq };
	bool                         enable_atapi;

	Driver(Genode::Env &env, Dispatch &dispatch, bool support_atapi)
	:
		env(env), dispatch(dispatch), enable_atapi(support_atapi)
	{
		info();

		/* register irq handler */
		hba.sigh_irq(irq);

		/* initialize HBA (IRQs, memory) */
		hba.init();

		/* search for devices */
		scan_ports(env.rm());
	}

	/**
	 * Forward IRQs to ports/block sessions
	 */
	void handle_irq()
	{
		unsigned port_list = hba.read<Hba::Is>();
		while (port_list) {
			unsigned port = log2(port_list);
			port_list    &= ~(1U << port);

			/* handle (pending) requests */
			dispatch.session(port);

			/* ack irq */
			ports[port]->handle_irq();
		}

		/* clear status register */
		hba.ack_irq();
	}

	/*
	 * Least significant bit
	 */
	unsigned lsb(unsigned bits) const
	{
		for (unsigned i = 0; i < 32; i++)
			if (bits & (1u << i)) {
				return i;
			}

		return 0;
	}

	void info()
	{
		log("version: "
		    "major=", Genode::Hex(hba.read<Hba::Version::Major>()), " "
		    "minor=", Genode::Hex(hba.read<Hba::Version::Minor>()));
		log("command slots: ", hba.command_slots());
		log("native command queuing: ", hba.ncq() ? "yes" : "no");
		log("64-bit support: ", hba.supports_64bit() ? "yes" : "no");
	}

	void scan_ports(Genode::Region_map &rm)
	{
		log("number of ports: ", hba.port_count(), " pi: ",
		    Hex(hba.read<Hba::Pi>()));

		unsigned available = hba.read<Hba::Pi>();
		for (unsigned i = 0; i < hba.port_count(); i++) {

			/* check if port is implemented */
			if (!available) break;
			unsigned index = lsb(available);
			available ^= (1u << index);

			bool enabled = false;
			switch (Port_base(index, hba).read<Port_base::Sig>()) {
				case ATA_SIG:
					try {
						ata[index].construct();
						ports[index].construct(*ata[index], rm, hba, index);
						enabled = true;
					} catch (...) { }

					log("\t\t#", index, ":", enabled ? " ATA" : " off (ATA)");
					break;

				case ATAPI_SIG:
				case ATAPI_SIG_QEMU:
					if (enable_atapi)
					/*
						try {
							ports[index] = new (&alloc)
								Atapi_driver(ram, root, ready_count, rm, hba,
								             platform_hba, index);
							enabled = true;
						} catch (...) { }*/

					log("\t\t#", index, ":", enabled ? " ATAPI" : " off (ATAPI)");
					break;

				default:
					log("\t\t#", index, ": off (unknown device signature)");
			}
		}
	}

	Port &port(long device, char const *model_num, char const *serial_num)
	{
		/* check for model/device */
		if (model_num && serial_num) {
			for (long index = 0; index < MAX_PORTS; index++) {
				if (!ata[index].constructed()) continue;

				Ata_protocol &protocol = *ata[index];
				if (*protocol.model == model_num && *protocol.serial == serial_num)
					return *ports[index];
			}
		}

		/* check for device number */
		if (device >= 0 && device < MAX_PORTS && ports[device].constructed())
			return *ports[device];

		throw -1;
	}

	template <typename FN> void for_each_port(FN const &fn)
	{
		for (unsigned index = 0; index < MAX_PORTS; index++) {
			if (!ports[index].constructed()) continue;
			fn(*ports[index], index, !ata[index].constructed());
		}
	}

	void report_ports(Genode::Reporter &reporter)
	{
		auto report = [&](Port const &port, unsigned index, bool atapi) {

			Block::Session::Info info = port.info();
			Reporter::Xml_generator xml(reporter, [&] () {

				xml.node("port", [&] () {
					xml.attribute("num", index);
					xml.attribute("type", atapi ? "ATAPI" : "ATA");
					xml.attribute("block_count", info.block_count);
					xml.attribute("block_size", info.block_size);
					if (!atapi) {
						xml.attribute("model", ata[index]->model->cstring());
						xml.attribute("serial", ata[index]->serial->cstring());
					}
				});
			});
		};

		for_each_port(report);
	}
};


struct Ahci::Block_session_handler : Interface
{
	Env                     &env;
	Port                    &port;
	Ram_dataspace_capability ds;

	Signal_handler<Block_session_handler> request_handler
	  { env.ep(), *this, &Block_session_handler::handle};

	Block_session_handler(Env &env, Port &port, size_t buffer_size)
	: env(env), port(port), ds(port.alloc_buffer(buffer_size))
	{ }

	~Block_session_handler()
	{
		port.free_buffer(ds);
	}

	virtual void handle_requests()= 0;

	void handle()
	{
		handle_requests();
	}
};

struct Ahci::Block_session_component : Rpc_object<Block::Session>,
                                       Block_session_handler,
                                       Block::Request_stream
{
	Block_session_component(Env &env, Port &port, size_t buffer_size)
	:
	  Block_session_handler(env, port, buffer_size),
	  Request_stream(env.rm(), ds, env.ep(), request_handler, port.info())
	{
		env.ep().manage(*this);
	}

	~Block_session_component()
	{
		env.ep().dissolve(*this);
	}

	Info info() const override { return Request_stream::info(); }

	Capability<Tx> tx_cap() override { return Request_stream::tx_cap(); }

	void handle_requests() override
	{
		while (true) {

			bool progress = false;

			/*
			 * Acknowledge any pending packets before sending new request to the
			 * controller.
			 */
			try_acknowledge([&](Ack &ack) {
				port.for_one_completed_request([&] (Block::Request request) {
					progress = true;
					ack.submit(request);
				});
			});

			with_requests([&] (Block::Request request) {

				Response response = Response::RETRY;

				/* only READ/WRITE requests, others are noops for now */
				if (Block::Operation::has_payload(request.operation.type) == false) {
					request.success = true;
					progress = true;
					return Response::REJECTED;
				}

				if ((response = port.submit(request)) != Response::RETRY)
					progress = true;

				return response;
			});

			if (progress == false) break;
		}

		/* poke */
		wakeup_client_if_needed();
	}
};


struct Ahci::Main : Rpc_object<Typed_root<Block::Session>>,
                    Dispatch
{
	Env  &env;

	Attached_rom_dataspace config { env, "config" };

	Constructible<Ahci::Driver> driver { };
	Constructible<Reporter> reporter { };
	Constructible<Block_session_component> block_session[Driver::MAX_PORTS];

	Main(Env &env)
	: env(env)
	{
		log("--- Starting AHCI driver ---");
		bool support_atapi  = config.xml().attribute_value("atapi", false);
		try {
			driver.construct(env, *this, support_atapi);
			report_ports();
		} catch (Ahci::Missing_controller) {
			error("no AHCI controller found");
			env.parent().exit(~0);
		} catch (Service_denied) {
			error("hardware access denied");
			env.parent().exit(~0);
		}

		env.parent().announce(env.ep().manage(*this));
	}

	void session(unsigned index)
	{
		if (index > Driver::MAX_PORTS || !block_session[index].constructed()) return;
		block_session[index]->handle_requests();
	}

	Session_capability session(Root::Session_args const &args,
	                            Affinity const &) override
	{
		log("new block session: ", args.string(), " size: ", sizeof(Block_session_component));
		Session_label const label = label_from_args(args.string());
		Session_policy const policy(label, config.xml());

		Ram_quota const ram_quota = ram_quota_from_args(args.string());
		size_t const tx_buf_size =
			Arg_string::find_arg(args.string(), "tx_buf_size").ulong_value(0);

		if (!tx_buf_size)
			throw Service_denied();

		if (tx_buf_size > ram_quota.value) {
			error("insufficient 'ram_quota' from '", label, "',"
			      " got ", ram_quota, ", need ", tx_buf_size);
			throw Insufficient_ram_quota();
		}

		/* try read device port number attribute */
		long device = policy.attribute_value("device", -1L);

		/* try read device model and serial number attributes */
		auto const model  = policy.attribute_value("model",  Genode::String<64>());
		auto const serial = policy.attribute_value("serial", Genode::String<64>());

		try {
			Port &port = driver->port(device, model.string(), serial.string());

			if (block_session[port.index].constructed()) {
				error("Device with number=", port.index, " is already in use");
				throw Service_denied();
			}

			block_session[port.index].construct(env, port, tx_buf_size);
			return block_session[port.index]->cap();
		} catch (...) {
			error("rejecting session request, no matching policy for '", label, "'",
			      " (model=", model, " serial=", serial, " device index=", device, ")");
		}

		throw Service_denied();
	}

	void upgrade(Session_capability, Root::Upgrade_args const&) override { }

	void close(Session_capability cap) override
	{
		for (int index = 0; index < Driver::MAX_PORTS; index++) {
			if (!block_session[index].constructed() || !(cap == block_session[index]->cap()))
				continue;

			block_session[index].destruct();
		}
	}

	void report_ports()
	{
		try {
			Xml_node report = config.xml().sub_node("report");
			if (report.attribute_value("ports", false)) {
				reporter.construct(env, "ports");
				reporter->enabled(true);
				driver->report_ports(*reporter);
			}
		} catch (Xml_node::Nonexistent_sub_node) { }
	}
};

void Component::construct(Genode::Env &env) { static Ahci::Main server(env); }
