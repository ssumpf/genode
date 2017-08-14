/*
 * \brief  Connection to block service
 * \author Stefan Kalkowski
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

namespace Drm { struct Connection; }

struct Drm::Connection : Genode::Connection<Session>, Session_client
{
	/**
	 * Issue session request
	 *
	 * \noapi
	 */
	Capability<Drm::Session> _session(Genode::Parent &parent,
	                                    char const *label, Genode::size_t tx_buf_size)
	{
		return session(parent, "ram_quota=%ld, cap_quota=%ld, tx_buf_size=%ld, label=\"%s\"",
		               14*1024 + tx_buf_size, CAP_QUOTA, tx_buf_size, label);
	}

	/**
	 * Constructor
	 *
	 * \param tx_buffer_alloc  allocator used for managing the
	 *                         transmission buffer
	 * \param tx_buf_size      size of transmission buffer in bytes
	 */
	Connection(Genode::Env             &env,
	           Genode::Range_allocator *tx_block_alloc,
	           Genode::size_t           tx_buf_size = 16*1024,
	           const char              *label = "")
	:
		Genode::Connection<Session>(env, _session(env.parent(), label, tx_buf_size)),
		Session_client(cap(), *tx_block_alloc, env.rm())
	{ }
};

#endif /* _INCLUDE__GPU__CONNECTION_H_ */
