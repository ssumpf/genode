/*
 * \brief  Libc-internal kernel API
 * \author Josef Soentgen
 * \date   2018-10-16
 */

/*
 * Copyright (C) 2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _LIBC__INTERNAL_SIGNAL_H_
#define _LIBC__INTERNAL_SIGNAL_H_

#include <os/ring_buffer.h>

namespace Libc {

	/*
	 * Handled signals
	 *
	 * The numbers must match original libc signal numbers.
	 */
	enum Signal {
		SIG_WINCH = 28
	};

	enum { SIGNAL_QUEUE_SIZE = 32 };
	using Signal_buffer = Genode::Ring_buffer<enum Signal, SIGNAL_QUEUE_SIZE,
	                                          Genode::Ring_buffer_unsynchronized>;

	/**
	 * Submit signal
	 */
	int submit_signal(Signal sig);

	/**
	 * Dispatch signal-handler
	 */
	int dispatch_pending_signals(jmp_buf &ctx);
}

#endif /* _LIBC__INTERNAL_SIGNAL_H_ */
