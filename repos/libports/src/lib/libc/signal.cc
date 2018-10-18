/*
 * \brief  POSIX signals
 * \author Emery Hemingway
 * \author Josef Soentgen
 * \date   2015-10-30
 */

/*
 * Copyright (C) 2006-2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* libc includes */
extern "C" {
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
}

/* libc-internal includes */
#include <internal/call_func.h>
#include <internal/signal.h>
#include "libc_errno.h"


/*
 * Signal mask functionality is not fully implemented yet.
 * TODO: - actually block delivery of to be blocked signals
 */
static sigset_t            _signal_mask;
static struct sigaction    _signal_action[NSIG+1];
static Libc::Signal_buffer _pending_signals;


extern "C" int __attribute__((weak)) _sigprocmask(int how, const sigset_t *set, sigset_t *old_set)
{
	/* no signals should be expected, so report all signals blocked */
	if (old_set) { sigfillset(old_set); }

	if (!set) { return 0; }

	switch (how) {
	case SIG_BLOCK:
		for (int sig = 1; sig < NSIG; sig++) {
			if (sigismember(set, sig)) { sigaddset(&_signal_mask, sig); }
		}
	break;
	case SIG_UNBLOCK:
		for (int sig = 1; sig < NSIG; sig++) {
			if (sigismember(set, sig)) { sigdelset(&_signal_mask, sig); }
		}
		break;
	case SIG_SETMASK:
		_signal_mask = *set;
		break;
	default: break;
	}
	return Libc::Errno(EINVAL);
}


extern "C" int __attribute__((weak)) sigprocmask(int how, const sigset_t *set, sigset_t *old_set)
{
	return _sigprocmask(how, set, old_set);
}


extern "C" int __attribute__((weak)) _sigaction(int signum, const struct sigaction *act,
                                               struct sigaction *oldact)
{
	if ((signum < 1) || (signum > NSIG)) { return Libc::Errno(EINVAL); }

	if (oldact) { *oldact = _signal_action[signum]; }
	if (act)    { _signal_action[signum] = *act; }

	return 0;
}


extern "C" int __attribute__((weak)) sigaction(int signum, const struct sigaction *act,
                                               struct sigaction *oldact)
{
	return _sigaction(signum, act, oldact);
}


int Libc::dispatch_pending_signals(jmp_buf &ctx)
{
	static jmp_buf saved_ctx;
	static bool in_sigh = false; /* true if called from signal handler */

	if (in_sigh) { return 0; }

	while (!_pending_signals.empty()) {
		in_sigh = true;
		Libc::Signal signal = _pending_signals.get();

		if (_signal_action[signal].sa_handler == SIG_DFL) {
			switch (signal) {
			case SIGWINCH:
				break;
			default:
				exit((signal << 8) | EXIT_FAILURE);
			}
		} else if (_signal_action[signal].sa_handler == SIG_IGN) {
			/* do nothing */
		} else {
			memcpy(&saved_ctx, &ctx, sizeof(jmp_buf));
			_signal_action[signal].sa_handler(signal);
			memcpy(&ctx, &saved_ctx, sizeof(jmp_buf));
		}
	}
	in_sigh = false;

	return 0;
}


int Libc::submit_signal(Libc::Signal sig)
{
	try {
		_pending_signals.add(sig);
		return 0;
	} catch (...) { }

	return -1;
}
