/*
 * \brief  Utility to allocate and locally attach a DMA buffer
 * \author Norman Feske
 * \author Stefan Kalkowski
 * \date   2022-02-02
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__DMA_SESSION__BUFFER_H_
#define _INCLUDE__DMA_SESSION__BUFFER_H_

/* Genode includes */
#include <base/attached_dataspace.h>
#include <dma_session/connection.h>

class Dma::Buffer : Noncopyable
{
	private:

		struct Allocation
		{
			Dma::Connection &con;

			size_t const size;
			Cache  const cache;

			Ram_dataspace_capability _alloc()
			{
				Ram_dataspace_capability cap;
				con.alloc(size, cache).with_result(
					[&] (auto c) { cap = c; },
					[]  (auto) { /* do nothing */ });
				return cap;
			}

			Ram_dataspace_capability cap = _alloc();

			addr_t const bus_addr = con.bus_addr(cap);

			Allocation(Connection &con, size_t size, Cache cache)
			: con(con), size(size), cache(cache) { }

			~Allocation() { con.free(cap); }

		} _allocation;

		Attached_dataspace _ds { _allocation.con._env.rm(), _allocation.cap };

	public:

		/**
		 * Constructor
		 *
		 * \param con  dma session used for the buffer allocation
		 * \param size DMA buffer size in bytes
		 *
		 * \throw Region_map::Region_conflict
		 */
		Buffer(Dma::Connection &con, size_t size, Cache cache)
		:
			_allocation(con, size, cache)
		{ }

		/**
		 * Return component-local base address
		 */
		template <typename T> T       *local_addr()       { return _ds.local_addr<T>(); }
		template <typename T> T const *local_addr() const { return _ds.local_addr<T>(); }

		/**
		 * Return bus address to be used for DMA operations
		 */
		addr_t bus_addr() const { return _allocation.bus_addr; }

		/**
		 * Return DMA-buffer size in bytes
		 */
		size_t size() const { return _allocation.size; }

		/**
		 * Return DMA-buffer as dataspace capability
		 */
		Dataspace_capability cap() { return _ds.cap(); }
};

#endif /* _INCLUDE__DMA_SESSION__BUFFER_H_ */
