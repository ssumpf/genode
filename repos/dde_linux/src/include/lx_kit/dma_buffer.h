/*
 * \brief  Lx_kit dma memory buffer
 * \author Stefan Kalkowski
 * \date   2021-03-25
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2 or later.
 */

#ifndef _LX_KIT__DMA_BUFFER_H_
#define _LX_KIT__DMA_BUFFER_H_

#include <lx_kit/memory.h>
#include <dma_session/buffer.h>

namespace Lx_kit { class Dma_buffer; }


class Lx_kit::Dma_buffer : Dma::Buffer, public Lx_kit::Mem_allocator::Buffer
{
	public:

		using Dma::Buffer::Buffer;

		size_t bus_addr() const override {
			return Dma::Buffer::bus_addr(); }

		size_t size() const override {
			return Dma::Buffer::size(); }

		size_t virt_addr() const override {
			return (size_t) Dma::Buffer::local_addr<void>(); }

		Dataspace_capability cap() override {
			return Dma::Buffer::cap(); }
};

#endif /* _LX_KIT__DMA_BUFFER_H_ */
