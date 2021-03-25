/*
 * \brief  Connection to DRM service
 * \author Sebastian Sumpf
 * \date   2010-07-07
 */

/*
 * Copyright (C) 2010-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__GPU__CONNECTION_H_
#define _INCLUDE__GPU__CONNECTION_H_

#include <gpu/client.h>
#include <base/connection.h>
#include <base/allocator.h>

namespace Drm {

	using namespace Genode;

	struct Connection;
}

struct Drm::Connection : Genode::Connection<Session>, Session_client
{
	/**
	 * Issue session request
	 *
	 * \noapi
	 */
	Genode::Capability<Drm::Session> _session(Parent &parent,
	                                          char const *label,
	                                          size_t tx_buf_size)
	{
		return session(parent, "ram_quota=%ld, tx_buf_size=%ld, label=\"%s\"",
		               14*1024 + tx_buf_size, tx_buf_size, label);
	}

	/**
	 * Constructor
	 *
	 * \param tx_buffer_alloc  allocator used for managing the
	 *                         transmission buffer
	 * \param tx_buf_size      size of transmission buffer in bytes
	 */
	Connection(Env             &env,
	           Range_allocator *tx_block_alloc,
	           size_t           tx_buf_size = 16*1024,
	           const char              *label = "")
	:
		Genode::Connection<Session>(env, _session(env.parent(), label, tx_buf_size)),
		Session_client(cap(), *tx_block_alloc, env.rm())
	{ }
};

#endif /* _INCLUDE__GPU__CONNECTION_H_ */
