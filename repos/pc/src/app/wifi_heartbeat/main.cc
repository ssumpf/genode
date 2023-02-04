/*
 * \brief  Wifi heartbeat sandbbox
 * \author Stefan Kalkowski
 * \date   2023-02-03
 *
 * This components starts the Wifi driver with hertbeats enabled. After 3
 * consecutive missed heartbeats, it restarts the driver by incrementing its.
 * version.
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <base/component.h>
#include <os/buffered_xml.h>
#include <sandbox/sandbox.h>

using namespace Genode;

enum {
	HEARTBEAT_RATE_MS             = 1000, /* expect heartbeat after y ms */
	RESTART_AFTER_HEARBEAT_MISSES = 3,    /* restart driver atfer x missed heartbeats */
	DELAY_REPORT_MS = RESTART_AFTER_HEARBEAT_MISSES * HEARTBEAT_RATE_MS + 100 /* check missed beats after x beats with y rate */
};


struct Main : Sandbox::State_handler
{
	Env      &_env;
	Heap      _heap { _env.ram(), _env.rm() };
	Sandbox   _sandbox { _env, *this };
	uint32_t  _version { 0 };
	uint32_t  _last_heartbeat { 0 };

	void _generate_sandbox_config(Xml_generator &xml, uint32_t version) const
	{
		xml.node("parent-provides", [&] () {

			auto service_node = [&] (char const *name) {
				xml.node("service", [&] () {
					xml.attribute("name", name); }); };

			service_node("ROM");
			service_node("CPU");
			service_node("PD");
			service_node("RM");
			service_node("LOG");
			service_node("Rtc");
			service_node("IRQ");
			service_node("IO_MEM");
			service_node("IO_PORT");
			service_node("Platform");
			service_node("Uplink");
			service_node("Report");
			service_node("Timer");
		});

		xml.node("heartbeat", [&] () {
			xml.attribute("rate_ms", HEARTBEAT_RATE_MS); });
		xml.node("report", [&] () {
			xml.attribute("delay_ms", DELAY_REPORT_MS); });

		xml.node("start", [&] () {
			xml.attribute("name", "pc_wifi_drv");
			xml.attribute("caps", 250);
			xml.attribute("version", version);
			xml.node("resource", [&] () {
				xml.attribute("name", "RAM");
				xml.attribute("quantum", "32M");
			});

			xml.node("heartbeat", [] () { });

			xml.node("config", [&] () {
				xml.node("report", [&] () {
					xml.attribute("mac_address", "true"); });
				xml.node("libc", [&] () {
					xml.attribute("stdout", "/dev/log");
					xml.attribute("stderr", "/dev/log");
					xml.attribute("rtc", "/dev/rtc");
					xml.attribute("rng", "/dev/urandom"); });
				xml.node("vfs", [&] () {
					xml.node("dir", [&] () {
						xml.attribute("name", "dev");
						xml.node("log", [] () {});
						xml.node("null", [] () {});
						xml.node("rtc", [] () {});
						xml.node("wifi", [] () {});
						xml.node("jitterentropy", [&] () {
							xml.attribute("name", "urandom"); });
						xml.node("jitterentropy", [&] () {
							xml.attribute("name", "random"); });
					});
				});
			});

			xml.node("route", [&] () {
				xml.node("any-service", [&] () {
					xml.node("parent", [&] () { }); });
			});
		});
	}

	void _update_sandbox_config()
	{
		Buffered_xml const config { _heap, "config", [&] (Xml_generator &xml) {
			_generate_sandbox_config(xml, ++_version); } };

		config.with_xml_node([&] (Xml_node const &config) {
			_sandbox.apply_config(config);
		});
	}

	void handle_sandbox_state() override
	{
		using Name = String<32>;
		Buffered_xml state(_heap, "state", [&] (Xml_generator &xml) {
			_sandbox.generate_state_report(xml);
		});

		state.xml().for_each_sub_node("child", [&] (Xml_node &child) {
			if (child.attribute_value("name", Name()) != Name("pc_wifi_drv"))
				return;

			uint32_t skipped = child.attribute_value("skipped_heartbeats", 0u);

			if (skipped == 0) {
				_last_heartbeat = 0;
				return;
			}

			if (skipped - _last_heartbeat >= RESTART_AFTER_HEARBEAT_MISSES)
				_update_sandbox_config();

			_last_heartbeat = skipped;
		});
	}

	Main(Env &env) : _env(env)
	{
		_update_sandbox_config();
	}
};


void Component::construct(Genode::Env &env) { static Main main(env); }
