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
#include <base/heap.h>
#include <base/log.h>
#include <block/request_stream.h>
#include <os/session_policy.h>
#include <util/xml_node.h>
#include <os/reporter.h>

/* local includes */
#include <ahci.h>


namespace Ahci {
	using namespace Genode;
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
struct Ahci::Block_session_component : Rpc_object<Block::Session>,
                                       Block::Request_stream
{
	Env &_env;

	Block_session_component(Env &env, Dataspace_capability ds,
	                        Signal_context_capability sigh,
	                        Block::Session::Info info)
	:
		Request_stream(env.rm(), ds, env.ep(), sigh, info),
		_env(env)
	{
		_env.ep().manage(*this);
	}

	~Block_session_component() { _env.ep().dissolve(*this); }
};

struct Ahci::Main : Rpc_object<Typed_root<Block::Session>>
{
	Env  &env;
	Heap  heap { env.ram(), env.rm() };

	Attached_rom_dataspace config { env, "config" };

	Constructible<Reporter> reporter { };
	Constructible<Block_session_component> block_session[Ahci_driver::MAX_PORTS];

	Main(Env &env)
	: env(env)
	{
		log("--- Starting AHCI driver ---");
		bool support_atapi  = config.xml().attribute_value("atapi", false);
		try {
			Ahci_driver::init(env, heap, support_atapi);
			report_ports();
		} catch (Ahci_driver::Missing_controller) {
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
			writeable = Arg_string::find_arg(args.string(), "writeable").bool_value(true);

		return Capability<Session>();
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
				Ahci_driver::report_ports(*reporter);
			}
		} catch (Xml_node::Nonexistent_sub_node) { }
	}
};

void Component::construct(Genode::Env &env) { static Ahci::Main server(env); }
