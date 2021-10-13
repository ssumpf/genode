/*
 * \brief  PPGTT translation table allocator
 * \author Josef Soentgen
 * \data   2017-03-15
 */

/*
 * Copyright (C) 2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _PPGTT_ALLOCATOR_H_
#define _PPGTT_ALLOCATOR_H_

/* local includes */
#include <types.h>
#include <utils.h>


namespace Igd {

	class Ppgtt_allocator;
}


class Igd::Ppgtt_allocator : public Genode::Translation_table_allocator
{
	private:

		Genode::Region_map      &_rm;
		Utils::Backend_alloc    &_backend;

		enum { ELEMENTS = 128, }; /* max 128M for page tables */
		Utils::Address_map<ELEMENTS> _map { };

		Genode::Cap_quota_guard &_caps_guard;
		Genode::Ram_quota_guard &_ram_guard;

		Genode::Allocator_avl    _range;

	public:

		Ppgtt_allocator(Genode::Allocator       &md_alloc,
		                Genode::Region_map      &rm,
		                Utils::Backend_alloc    &backend,
		                Genode::Cap_quota_guard &caps_guard,
		                Genode::Ram_quota_guard &ram_guard)
		:
			_rm         { rm },
			_backend    { backend },
			_caps_guard { caps_guard },
			_ram_guard  { ram_guard },
			_range      { &md_alloc }
		{ }

		~Ppgtt_allocator()
		{
			_map.for_each([&](Utils::Address_map<ELEMENTS>::Element &elem) {
				_rm.detach(elem.va);
				_backend.free(elem.ds_cap);
				elem.invalidate();
			});
		}

		/*************************
		 ** Allocator interface **
		 *************************/

		bool alloc(size_t size, void **out_addr) override
		{
			if (_range.alloc_aligned(size, out_addr, 12).ok()) {
				return true;
			}

			size_t alloc_size = 1024*1024;

			Genode::Ram_dataspace_capability ds =
				_backend.alloc(alloc_size, _caps_guard, _ram_guard);

			*out_addr = _rm.attach(ds);
			bool added = _map.add(ds, *out_addr);

			if (!added) {
				Genode::error("Could not add ", *out_addr, " to PPGTT map");
				return false;
			}

			_range.add_range((Genode::addr_t)*out_addr, alloc_size);

			if (_range.alloc_aligned(size, out_addr, 12).error()) {
				Genode::log("alloc PPGTT error: size: ", Genode::Hex(size));
				return false;
			}

			return true;
		}

		void free(void *addr, size_t size) override
		{
			if (addr == nullptr) { return; }

			_range.free(addr, size);
		}

		bool   need_size_for_free() const override { return false; }
		size_t overhead(size_t)     const override { return 0; }

		/*******************************************
		 ** Translation_table_allocator interface **
		 *******************************************/

		void *phys_addr(void *va) override
		{
			if (va == nullptr) { return nullptr; }
			addr_t pa = _map.phys_addr(va);
			return pa ? (void *)pa : nullptr;
		}

		void *virt_addr(void *pa) override
		{
			if (pa == nullptr) { return nullptr; }
			addr_t virt = _map.virt_addr(pa);
			return virt ? (void*)virt : nullptr;
		}
};

#endif /* _PPGTT_ALLOCATOR_H_ */
