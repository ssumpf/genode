/*
 * \brief  Platform driver root component
 * \author Stefan Kalkowski
 * \date   2020-04-13
 */

/*
 * Copyright (C) 2020-2026 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _SRC__DRIVER__PLATFORM__ROOT_H_
#define _SRC__DRIVER__PLATFORM__ROOT_H_

#include <base/attached_rom_dataspace.h>
#include <base/registry.h>
#include <root/component.h>

#include <device.h>
#include <pd.h>
#include <session_component.h>
#include <dma_component.h>

namespace Driver { template <typename> class Root; }

template <typename SESSION>
class Driver::Root : public Root_component<SESSION>
{
	private:

		using Create_result = Root_component<SESSION>::Create_result;
		using Create_error = Root_component<SESSION>::Create_error;
		using Version = Driver::Session_component::Policy_version;

		Env &_env;

		Attached_rom_dataspace const &_config;

		Device_model &_devices;

		Pd_allocator  &_pd_alloc;
		Pd_dictionary &_pds;

		bool _warn_once { true };

		Create_result _create_session(const char * args) override;

		void _upgrade_session(SESSION &sc, const char *args) override
		{
			sc.upgrade(ram_quota_from_args(args));
			sc.upgrade(cap_quota_from_args(args));
		}

		void _destroy_session(SESSION &sc) override
		{
			Pd &pd = sc._pd;
			Root_component<SESSION>::_destroy_session(sc);

			if (pd.empty()) _pd_alloc.destroy(pd);
		}

	public:

		Root(Env                          &env,
		     Sliced_heap                  &sliced_heap,
		     Pd_allocator                 &pd_alloc,
		     Pd_dictionary                &pds,
		     Attached_rom_dataspace const &config,
		     Device_model                 &devices)
		:
			Root_component<SESSION>(env.ep(), sliced_heap),
			_env(env), _config(config), _devices(devices),
			_pd_alloc(pd_alloc), _pds(pds)
		{ }

		void update_policy();
};


template <typename SESSION>
void Driver::Root<SESSION>::update_policy()
{
	_pds.for_each([&] (auto &pd) {
		with_matching_policy(pd.label(), _config.node(),
			[&] (auto const &policy) {
				pd.update_policy(policy.attribute_value("info", false),
				                 policy.attribute_value("version", Version()));
			},
			[&] {
				error("No matching policy for '", pd.label().string(),
				      "' anymore, will close all related sessions!");
				pd.close_all_sessions(*this);
				_pd_alloc.destroy(pd);
			});
	});
}


template <typename SESSION>
Driver::Root<SESSION>::Create_result
Driver::Root<SESSION>::_create_session(const char *args)
{
	enum {
		PD_RAM_OVERHEAD = sizeof(Pd) + 4096,
		PD_CAP_OVERHEAD = 2
	};

	Session_label      label     = label_from_args(args);
	Session::Resources resources = session_resources_from_args(args);

	if (resources.cap_quota.value < PD_CAP_OVERHEAD)
		return Create_error::OUT_OF_CAPS;

	if (resources.ram_quota.value < PD_RAM_OVERHEAD)
		return Create_error::OUT_OF_RAM;

	resources.cap_quota.value -= PD_CAP_OVERHEAD;
	resources.ram_quota.value -= PD_RAM_OVERHEAD;

	auto no_pd_found = [&] (Node const &policy) -> Create_result {

		bool    info    = policy.attribute_value("info", false);
		Version version = policy.attribute_value("version", Version());

		return _pd_alloc.create(_env, _config, _devices, _pds, label,
		                        info, version).template convert<Create_result>(
			[&] (auto &a) {
				a.deallocate = false;
				return Root_component<SESSION>::_alloc_obj(_env, a.obj,
				                                           _devices, resources);
			},
			/*
			 * The platform driver needs to pay for PD objects  out of
			 * its own resources, because they are potentially shared in
			 * between different device and dma sessions, so in case
			 * of resource shortage, it just fails!
			 */
			[&] (auto) {
				if (_warn_once) {
				error("Platform driver out of resources, cannot create PD");
				_warn_once = false;
				}
				return Create_error::DENIED;
			});
	};

	return with_matching_policy(label, _config.node(),
		[&] (Node const &policy) -> Create_result {
			return _pds.with_element(label,
				[&] (Pd &pd) {
					return Root_component<SESSION>::_alloc_obj(_env, pd,
					                                           _devices,
					                                           resources);
				},
				[&] { return no_pd_found(policy); });
		},
		[&] () -> Create_result {
			error("Invalid session request, no matching policy for ",
			      "'", label_from_args(args), "'");
			return Create_error::DENIED;
		});
}

#endif /* _SRC__DRIVER__PLATFORM__ROOT_H_ */
