/*
 * \brief  Capability slab management
 * \author Norman Feske
 * \date   2023-06-20
 */

/*
 * Copyright (C) 2023 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <util/retry.h>
#include <base/internal/globals.h>
#include <base/internal/native_env.h>
#include <hw_native_pd/client.h>

using namespace Genode;

using Native_pd_capability = Genode::Capability<Genode::Pd_session::Native_pd>;


static Parent *parent_ptr;
static Pd_session *pd_ptr;
static Native_pd_capability native_pd_cap;


void Genode::init_cap_slab(Pd_session &pd, Parent &parent)
{
	parent_ptr    = &parent;
	pd_ptr        = &pd;
	native_pd_cap = pd.native_pd();
}


void Genode::upgrade_capability_slab()
{
	if (!native_pd_cap.valid() || !parent_ptr) {
		error("missing call of 'init_cap_slab'");
		return;
	}

	auto request_resources_from_parent = [&] (Ram_quota ram, Cap_quota caps)
	{
		/*
		 * The call of 'resource_request' is handled synchronously by
		 * 'Expanding_parent_client'.
		 */
		String<100> const args("ram_quota=", ram, ", cap_quota=", caps);
		parent_ptr->resource_request(args.string());
	};

	retry<Genode::Out_of_caps>(
		[&] () {
			retry<Genode::Out_of_ram>(
				[&] () {
					Genode::Hw_native_pd_client pd(native_pd_cap);
					pd.upgrade_cap_slab();
				},
				[&] () {
					request_resources_from_parent(Ram_quota{8192}, Cap_quota{0});
				});
		},
		[&] () {
			request_resources_from_parent(Ram_quota{0}, Cap_quota{2});
		});
}
