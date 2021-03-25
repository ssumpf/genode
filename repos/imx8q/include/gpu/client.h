/*
 * \brief  Client-side DRM session interface
 * \author Sebastian Sumpf
 * \date   2010-07-06
 */

/*
 * Copyright (C) 2010-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__GPU__CLIENT_H_
#define _INCLUDE__GPU__CLIENT_H_

#include <base/rpc_client.h>
#include <gpu/capability.h>
#include <packet_stream_tx/client.h>

namespace Drm { class Session_client; }


class Drm::Session_client : public Genode::Rpc_client<Session>
{
	private:

		Packet_stream_tx::Client<Tx> _tx;

	public:

		/**
		 * Constructor
		 *
		 * \param session          session capability
		 * \param tx_buffer_alloc  allocator used for managing the
		 *                         transmission buffer
		 */
		Session_client(Session_capability       session,
		               Genode::Range_allocator &tx_buffer_alloc,
		               Genode::Region_map      &rm)
		:
			Genode::Rpc_client<Session>(session),
			_tx(call<Rpc_tx_cap>(), rm, tx_buffer_alloc)
		{ }

		Tx *tx_channel() override { return &_tx; }
		Tx::Source *tx() override { return _tx.source(); }

		Genode::Ram_dataspace_capability object_dataspace(unsigned long offset, unsigned long size) override
		{
			return call<Rpc_object_ds_cap>(offset, size);
		}
};

#endif /* _INCLUDE__GPU__CLIENT_H_ */
