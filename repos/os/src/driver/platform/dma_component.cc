/*
 * \brief  Platform driver - dma session component
 * \author Stefan Kalkowski
 * \date   2026-05-05
 */

/*
 * Copyright (C) 2026 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <dataspace/client.h>

#include <dma_component.h>

using Driver::Dma_component;

void Dma_component::_free(Dma_buffer &buf)
{
	Ram_dataspace_capability cap = buf.cap;

	with_io_mmu_domain([&] (auto &domain) {
		domain.remove_range({ buf.dma_addr(), buf.phys_range.size });
		for_each_io_mmu([&] (auto &io_mmu) {
			io_mmu.iotlb_flush(domain); });
	});

	_dma_buffer_alloc.destroy(buf);
}


Genode::Attempt<Genode::Ok, Genode::Alloc_error> Dma_component::_update_iommu_costs()
{
	using Result = Attempt<Ok, Alloc_error>;

	if (!_pd._dma_remapable())
		return Ok();

	auto costs = _pd._domain.costs(_dma_address_list);
	Ram_quota const ram  { (costs.ram  > _costs.ram)  ? costs.ram-_costs.ram   : 0 };
	Cap_quota const caps { (costs.caps > _costs.caps) ? costs.caps-_costs.caps : 0 };

	return _ram_quota_guard().reserve(ram).convert<Result>(
		[&] (Ram_quota_guard::Reservation &reserved_ram) {
			return _cap_quota_guard().reserve(caps).convert<Result>(
				[&] (Cap_quota_guard::Reservation &reserved_caps) {
					reserved_ram.deallocate  = false;
					reserved_caps.deallocate = false;
					_costs = costs;
					return Ok();
				},
				[&] (Cap_quota_guard::Error) {
					return Alloc_error::OUT_OF_CAPS;
				});
		},
		[&] (Ram_quota_guard::Error) {
			return Alloc_error::OUT_OF_RAM;
		});
}


Dma::Session::Alloc_result Dma_component::alloc(size_t const size, Cache cache)
{
	auto res = _dma_buffer_alloc.create(_dma_buffers, _env_ram, size, cache,
	                                    _env.pd(), _pd._dma_address_alloc,
	                                    _dma_address_list, _pd._dma_remapable());

	return res.convert<Alloc_result>(
		[&] (auto &a) {
			return a.obj.constructed().template convert<Alloc_result>(
				[&] (auto) {
					return _update_iommu_costs().convert<Alloc_result>(
					[&] (auto) {
						auto &buf = a.obj;
						if (_pd._domain.add_range({buf.dma_addr(),
						                          buf.phys_range.size},
						                          buf.phys_range.start,
						                          buf.cap).failed())
							Genode::error("Inserting DMA buffer into ",
							              "IOMMU table failed!");
						a.deallocate = false;
						return a.obj.cap;
					},
					[&] (auto e) { return e; });
				},
				[&] (auto e) { return e; });
		},
		[&] (auto &e) { return e; });
}


void Dma_component::free(Ram_dataspace_capability ram_cap)
{
	if (!ram_cap.valid()) { return; }

	_dma_buffers.with_element({ram_cap},
		[&] (Dma_buffer &buf) { _free(buf); },
		[] () { /* ignore wrong capability argument */ });
}


Genode::addr_t Dma_component::bus_addr(Ram_dataspace_capability ram_cap)
{
	addr_t ret = 0;

	if (!ram_cap.valid())
		return ret;

	_dma_buffers.with_element({ram_cap},
		[&] (Dma_buffer &buf) { ret = buf.dma_addr(); },
		[] () { /* ignore wrong capability argument */ });

	return ret;
}


Dma_component::Dma_component(Env &env, Pd &pd, Device_model &devices,
                             Resources const &resources)
:
	Session_object<Dma::Session>(env.ep(), resources, pd.label()),
	Session_registry::Element(pd._dma_sessions, *this),
	_env(env), _pd(pd), _devices(devices)
{ }


Dma_component::~Dma_component()
{
	/* free up dma buffers */
	while (_dma_buffers.with_any_element([&] (Dma_buffer &buf) {
		_free(buf); })) ;

	_cap_quota_guard().replenish({_costs.caps});
	_ram_quota_guard().replenish({_costs.ram});
}
