/**
 * \brief  Block driver session creation
 * \author Sebastian Sumpf
 * \date   2015-09-29
 */

/*
 * Copyright (C) 2016-2017 Genode Labs GmbH
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
#include <ata_driver.h>

namespace Ahci {
	using namespace Genode;
	struct Driver;
	struct Main;
	struct Block_session_component;
}

#if 0
struct Block::Factory : Driver_factory
{
	long device_num;

	Block::Driver *create() override
	{
		return Ahci_driver::claim_port(device_num);
	}

	void destroy(Block::Driver *) override
	{
		Ahci_driver::free_port(device_num);
	}

	Factory(long device_num) : device_num(device_num) { }
};

class Session_component : public Block::Session_component
{
	public:

		Session_component(Block::Driver_factory &driver_factory,
		                  Genode::Entrypoint    &ep,
		                  Genode::Region_map    &rm,
		                  Genode::size_t         buf_size,
		                  bool                   writeable)
		: Block::Session_component(driver_factory, ep, rm, buf_size, writeable) { }

		Block::Driver_factory &factory() { return _driver_factory; }
};


class Block::Root_multiple_clients : public Root_component< ::Session_component>,
                                     public Ahci_root
{
	private:

		Genode::Env       &_env;
		Genode::Allocator &_alloc;
		Genode::Xml_node   _config;

	protected:

		::Session_component *_create_session(const char *args) override
		{
			Session_label const label = label_from_args(args);
			Session_policy const policy(label, _config);

			size_t ram_quota =
					Arg_string::find_arg(args, "ram_quota").ulong_value(0);
			size_t tx_buf_size =
				Arg_string::find_arg(args, "tx_buf_size").ulong_value(0);

			if (!tx_buf_size)
				throw Service_denied();

			size_t session_size = sizeof(::Session_component)
			                    + sizeof(Factory) +	tx_buf_size;

			if (max((size_t)4096, session_size) > ram_quota) {
				error("insufficient 'ram_quota' from '", label, "',"
				      " got ", ram_quota, ", need ", session_size);
				throw Insufficient_ram_quota();
			}

			/* try read device port number attribute */
			long num = policy.attribute_value("device", -1L);

			/* try read device model and serial number attributes */
			auto const model  = policy.attribute_value("model",  String<64>());
			auto const serial = policy.attribute_value("serial", String<64>());

			/* sessions are not writeable by default */
			bool writeable = policy.attribute_value("writeable", false);

			/* prefer model/serial routing */
			if ((model != "") && (serial != ""))
				num = Ahci_driver::device_number(model.string(), serial.string());

			if (num < 0) {
				error("rejecting session request, no matching policy for '", label, "'",
				      model == "" ? ""
				      : " (model=", model, " serial=", serial, ")");
				throw Service_denied();
			}

			if (!Ahci_driver::avail(num)) {
				error("Device ", num, " not available");
				throw Service_denied();
			}

			if (writeable)
				writeable = Arg_string::find_arg(args, "writeable").bool_value(true);

			Block::Factory *factory = new (&_alloc) Block::Factory(num);
			::Session_component *session = new (&_alloc)
				::Session_component(*factory, _env.ep(), _env.rm(), tx_buf_size, writeable);
			log(
				writeable ? "writeable " : "read-only ",
				"session opened at device ", num, " for '", label, "'");
			return session;
		}

		void _destroy_session(::Session_component *session) override
		{
			Driver_factory &factory = session->factory();
			Genode::destroy(&_alloc, session);
			Genode::destroy(&_alloc, &factory);
		}

	public:

		Root_multiple_clients(Genode::Env &env, Genode::Allocator &alloc,
		                      Genode::Xml_node config)
		:
			Root_component(&env.ep().rpc_ep(), &alloc),
			_env(env), _alloc(alloc), _config(config)
		{ }

		Genode::Entrypoint &entrypoint() override { return _env.ep(); }

		void announce() override
		{
			_env.parent().announce(_env.ep().manage(*this));
		}
};

#endif
struct Ahci::Driver : Noncopyable
{
	Env       &env;

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

	Platform::Hba &platform_hba { Platform::init(env, _delayer) };
	Hba            hba          { env, platform_hba, _delayer };

  Constructible<Ata_protocol> ata[MAX_PORTS];
	Constructible<Port>         ports[MAX_PORTS];

	Signal_handler<Driver> irq { env.ep(), *this, &Driver::handle_irq };
	bool                         enable_atapi;

	Driver(Genode::Env &env, bool support_atapi)
	:
		env(env), enable_atapi(support_atapi)
	{
		info();

		/* register irq handler */
		platform_hba.sigh_irq(irq);

		/* initialize HBA (IRQs, memory) */
		hba.init();

		/* search for devices */
		scan_ports(env.rm(), env.ram());
	}

	/**
	 * Forward IRQs to ports
	 */
	void handle_irq()
	{
		unsigned port_list = hba.read<Hba::Is>();
		while (port_list) {
			unsigned port = log2(port_list);
			port_list    &= ~(1U << port);

			//XXX: handle
			/*
			ports[port]->handle_irq(); */
		}

		/* clear status register */
		hba.ack_irq();

		/* ack at interrupt controller */
		platform_hba.ack_irq();
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

	void scan_ports(Genode::Region_map &rm, Genode::Ram_allocator &ram)
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
						ports[index].construct(*ata[index], rm, hba, platform_hba, index);
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
		if (device >= 0 && device < MAX_PORTS) return *ports[device];

		throw -1;
	}

	void report_ports(Genode::Reporter &reporter)
	{
		//XXX:
	}
};


struct Ahci::Block_session_component : Rpc_object<Block::Session>,
                                       Block::Request_stream
{
	Env &_env;

	Block_session_component(Env &env, Port &port, Dataspace_capability ds,
	                        Signal_context_capability sigh)
	:
		Request_stream(env.rm(), ds, env.ep(), sigh, port.info()),
		_env(env)
	{
		_env.ep().manage(*this);
	}

	~Block_session_component() { _env.ep().dissolve(*this); }

	Info info() const override { return Request_stream::info(); }

	Capability<Tx> tx_cap() override { return Request_stream::tx_cap(); }
};


struct Ahci::Main : Rpc_object<Typed_root<Block::Session>>
{
	Env  &env;

	Attached_rom_dataspace config { env, "config" };

	Constructible<Ahci::Driver> driver { };
	Constructible<Reporter> reporter { };
	Constructible<Block_session_component> block_session[Ahci::Driver::MAX_PORTS];

	Main(Env &env)
	: env(env)
	{
		log("--- Starting AHCI driver ---");
		bool support_atapi  = config.xml().attribute_value("atapi", false);
		try {
			driver.construct(env, support_atapi);
			report_ports();
		} catch (Ahci::Missing_controller) {
			error("no AHCI controller found");
			env.parent().exit(~0);
		} catch (Service_denied) {
			error("hardware access denied");
			env.parent().exit(~0);
		}
		//XXX: remove
		env.parent().announce(env.ep().manage(*this));
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
			warning("CONSTRUCT block session");
			block_session[port.index].construct(env, port, Dataspace_capability(), Signal_context_capability());
			return block_session[port.index]->cap();
		} catch (...) {
			error("rejecting session request, no matching policy for '", label, "'",
			      " (model=", model, " serial=", serial, " device index=", device, ")");
		}

		throw Service_denied();
	}

	void upgrade(Session_capability, Root::Upgrade_args const&) override { }
	void close(Session_capability) override { }

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
