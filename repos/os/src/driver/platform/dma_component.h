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

#ifndef _SRC__DRIVER__PLATFORM__DMA_COMPONENT_H_
#define _SRC__DRIVER__PLATFORM__DMA_COMPONENT_H_

#include <base/env.h>
#include <base/heap.h>
#include <base/quota_guard.h>
#include <base/registry.h>
#include <base/session_object.h>
#include <dma_session/dma_session.h>

#include <device.h>
#include <dma_buffer.h>
#include <io_mmu.h>
#include <pd.h>

namespace Driver {
	class Dma_component;
	template <typename> class Root;
}


class Driver::Dma_component
:
	public  Session_object<Dma::Session>,
	private Registry<Driver::Dma_component>::Element
{
	private:

		friend class Root<Dma_component>;

		Env          &_env;
		Pd           &_pd;
		Device_model &_devices;

		Accounted_ram_allocator _env_ram { _env.ram(), _ram_quota_guard(),
		                                   _cap_quota_guard()  };

		Heap _md_alloc { _env_ram, _env.rm() };

		Memory::Constrained_obj_allocator<Dma_buffer>
			_dma_buffer_alloc { _md_alloc };

		Dma_address_list _dma_address_list { };

		Dictionary<Dma_buffer, Dma_buffer_name> _dma_buffers {};

		Cost _costs { 0, 0 };

		Attempt<Ok, Alloc_error> _update_iommu_costs();

		void _free(Dma_buffer &buf);

		/*
		 * Noncopyable
		 */
		Dma_component(Session_component const &);
		Dma_component &operator = (Session_component const &);

	public:

		using Session_registry = Registry<Dma_component>;

		Dma_component(Env &env, Pd &pd, Device_model &devices,
		              Resources const &resources);

		~Dma_component();

		void with_io_mmu_domain(auto const &fn) {
			_pd.with_io_mmu_domain(fn); }

		void for_each_io_mmu(auto const &fn) {
			_pd.for_each_io_mmu(fn); }


		/*****************
		 ** Session API **
		 *****************/

		Alloc_result alloc(size_t, Cache) override;
		void free(Ram_dataspace_capability ram_cap) override;
		addr_t bus_addr(Ram_dataspace_capability) override;
};

#endif /* _SRC__DRIVER__PLATFORM__DMA_COMPONENT_H_ */
