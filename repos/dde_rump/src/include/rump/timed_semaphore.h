/*
 * \brief  Semaphore implementation with timeout facility
 * \author Christian Prochaska
 * \date   2022-04-06
 *
 * This semaphore implementation allows to block on a semaphore for a
 * given time instead of blocking indefinitely.
 *
 */

/*
 * Copyright (C) 2022 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _INCLUDE__RUMP__TIMED_SEMAPHORE_H_
#define _INCLUDE__RUMP__TIMED_SEMAPHORE_H_

#include <base/entrypoint.h>
#include <timer_session/connection.h>

class Ep_blockade
{
	private:

		Genode::Entrypoint &_ep;

		Genode::Io_signal_handler<Ep_blockade> _wakeup_handler
		{ _ep, *this, &Ep_blockade::_handle_wakeup };

		bool _signal_handler_called { false };

		void _handle_wakeup()
		{
			_signal_handler_called = true;
		}

	public:

		Ep_blockade(Genode::Entrypoint &ep) : _ep(ep) { }

		void block()
		{
			while (!_signal_handler_called)
				_ep.wait_and_dispatch_one_io_signal();

			_signal_handler_called = false;
		}

		void wakeup()
		{
			_wakeup_handler.local_submit();
		}
};


struct Timed_semaphore_blockade
{
	virtual void block() = 0;
	virtual void wakeup() = 0;
};


class Timed_semaphore_ep_blockade : public Timed_semaphore_blockade
{
	private:

		Ep_blockade _blockade;

	public:

		Timed_semaphore_ep_blockade(Genode::Entrypoint &ep)
		: _blockade(ep) { }
	
		void block() override
		{
			_blockade.block();
		}

		void wakeup() override
		{
			_blockade.wakeup();
		}
};


class Timed_semaphore_thread_blockade : public Timed_semaphore_blockade
{
	private:

		Genode::Blockade _blockade;

	public:

		Timed_semaphore_thread_blockade() { }
	
		void block() override
		{
			_blockade.block();
		}

		void wakeup() override
		{
			_blockade.wakeup();
		}
};


class Timed_semaphore
{
	private:

		Genode::Env &_env;
		Genode::Thread const *_ep_thread_ptr;
		Timer::Connection &_timer;

		int           _cnt;
		Genode::Mutex _meta_lock { };

		struct Element : Genode::Fifo<Element>::Element
		{
			Timed_semaphore_blockade &blockade;
			Timer::One_shot_timeout<Element> timeout;
			bool timed_out = false;

			void handle_timeout(Genode::Duration)
			{
				timed_out = true;
				blockade.wakeup();
			}

			Element(Timed_semaphore_blockade &blockade,
			        Timer::Connection &timer,
			        bool use_timeout = false,
			        Genode::Microseconds timeout_us = Genode::Microseconds(0))
			: blockade(blockade),
			  timeout(timer, *this, &Element::handle_timeout)
			{
				if (use_timeout) {
					timeout.schedule(timeout_us);
				}
			}
		};

		Genode::Fifo<Element> _queue { };

		void _down_internal(Timed_semaphore_blockade &blockade,
		                    bool use_timeout, Genode::Microseconds timeout_us)
		{
			/*
			 * Create semaphore queue element representing the thread
			 * in the wait queue.
			 */
			Element queue_element { blockade, _timer, use_timeout, timeout_us };
			_queue.enqueue(queue_element);
			_meta_lock.release();

			/*
			 * The thread is going to block now,
			 * waiting for getting waked from another thread
			 * calling 'up()'
			 * */
			queue_element.blockade.block();

			if (queue_element.timed_out)
				throw Timeout_exception();
		}

	public:

		class Timeout_exception : public Genode::Exception { };

		/**
		 * Constructor
		 *
		 * \param env   Genode environment
		 * \param timer timer connection
		 * \param n     initial counter value of the semphore
		 *
		 * Note: currently it is assumed that the constructor is called
		 *       by the ep thread.
		 */
		Timed_semaphore(Genode::Env &env, Timer::Connection &timer, int n = 0)
		: _env(env), _ep_thread_ptr(Genode::Thread::myself()),
		  _timer(timer), _cnt(n) { }

		~Timed_semaphore()
		{
			/* synchronize destruction with unfinished 'up()' */
			try { _meta_lock.acquire(); } catch (...) { }
		}

		/**
		 * Increment semaphore counter
		 *
		 * This method may wake up another thread that currently blocks on
		 * a 'down' call at the same semaphore.
		 */
		void up()
		{
			Element * element = nullptr;

			{
				Genode::Mutex::Guard guard(_meta_lock);

				if (++_cnt > 0)
					return;

				/*
				 * Remove element from queue and wake up the corresponding
				 * blocking thread
				 */
				_queue.dequeue([&element] (Element &head) {
					element = &head; });
			}

			/* do not hold the lock while unblocking a waiting thread */
			if (element) element->blockade.wakeup();
		}

		/**
		 * Decrement semaphore counter, block if the counter reaches zero
		 */
		void down(bool use_timeout = false,
		          Genode::Microseconds timeout_us = Genode::Microseconds(0))
		{
			if (use_timeout && (timeout_us.value == 0))
				throw Timeout_exception();

			_meta_lock.acquire();

			if (--_cnt < 0) {

				if (Genode::Thread::myself() == _ep_thread_ptr) {
					Timed_semaphore_ep_blockade blockade { _env.ep() };
					_down_internal(blockade, use_timeout, timeout_us);
				} else {
					Timed_semaphore_thread_blockade blockade;
					_down_internal(blockade, use_timeout, timeout_us);
				}

			} else {
				_meta_lock.release();
			}
		}
};

#endif /* _INCLUDE__RUMP__TIMED_SEMAPHORE_H_ */
