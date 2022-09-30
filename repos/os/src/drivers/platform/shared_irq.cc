/*
 * \brief  Platform driver - shared interrupts
 * \author Stefan Kalkowski
 * \date   2022-09-27
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <shared_irq.h>

using Driver::Shared_interrupt;
using Driver::Shared_interrupt_session;


void Shared_interrupt::_handle()
{
	_sessions.for_each([&] (Shared_interrupt_session & session) {
		if (session.signal()) _wait_for_acks++; });
}


void Shared_interrupt::enable(Irq_session::Trigger  mode,
                              Irq_session::Polarity polarity)
{
	if (_irq.constructed())
		return;

	_irq.construct(_env, _number, mode, polarity);
	_irq->sigh(_handler);
	_irq->ack_irq();
}


void Shared_interrupt::disable()
{
	unsigned session_count = 0;
	_sessions.for_each([&] (Shared_interrupt_session &) {
		session_count++; });

	/* if it is the last session, close the upstream connection */
	if (session_count <= 1)
		_irq.destruct();
}


void Shared_interrupt::ack()
{
	if (_wait_for_acks && ((--_wait_for_acks) == 0))
		_irq->ack_irq();
}


bool Shared_interrupt_session::signal()
{
	if (!_cap.valid())
		return false;

	Signal_transmitter(_cap).submit(1);
	return true;
}
