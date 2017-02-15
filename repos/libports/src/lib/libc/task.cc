/*
 * \brief  Libc kernel for main and pthreads user contexts
 * \author Christian Helmuth
 * \author Emery Hemingway
 * \date   2016-01-22
 */

/*
 * Copyright (C) 2016-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

/* Genode includes */
#include <base/component.h>
#include <base/log.h>
#include <base/thread.h>
#include <base/rpc_server.h>
#include <base/rpc_client.h>
#include <base/heap.h>
#include <base/attached_rom_dataspace.h>
#include <vfs/dir_file_system.h>
#include <timer_session/connection.h>
#include <os/timer.h>

/* libc includes */
#include <libc/component.h>
#include <libc-plugin/plugin_registry.h>

/* libc-internal includes */
#include <internal/call_func.h>
#include <base/internal/unmanaged_singleton.h>
#include "vfs_plugin.h"
#include "libc_init.h"
#include "task.h"


namespace Libc {
	class Env_implementation;
	class Kernel;
	class Pthreads;
	class Timer;
	class Timer_accessor;
	class Timeout;
	class Timeout_handler;
	class Io_response_handler;

	using Microseconds = Genode::Time_source::Microseconds;
}


class Libc::Env_implementation : public Libc::Env
{
	private:

		Genode::Env &_env;

		Genode::Attached_rom_dataspace _config { _env, "config" };

		Genode::Xml_node _vfs_config()
		{
			try { return _config.xml().sub_node("vfs"); }
			catch (Genode::Xml_node::Nonexistent_sub_node) { }
			try {
				Genode::Xml_node node =
					_config.xml().sub_node("libc").sub_node("vfs");
				Genode::warning("'<config> <libc> <vfs/>' is deprecated, "
				                "please move to '<config> <vfs/>'");
				return node;
			}
			catch (Genode::Xml_node::Nonexistent_sub_node) { }

			return Genode::Xml_node("<vfs/>");
		}

		Vfs::Dir_file_system _vfs;

		Genode::Xml_node _config_xml() const override {
			return _config.xml(); };

	public:

		Env_implementation(Genode::Env &env, Genode::Allocator &alloc,
		                   Vfs::Io_response_handler &io_response_handler)
		:
			_env(env),
			_vfs(_env, alloc, _vfs_config(), io_response_handler,
			     Vfs::global_file_system_factory())
		{ }


		/*************************
		 ** Libc::Env interface **
		 *************************/

		Vfs::File_system &vfs() override {
			return _vfs; }


		/***************************
		 ** Genode::Env interface **
		 ***************************/

		Parent &parent() override {
			return _env.parent(); }

		Ram_session &ram() override {
			return _env.ram(); }

		Cpu_session &cpu() override {
			return _env.cpu(); }

		Region_map &rm() override {
			return _env.rm(); }

		Pd_session &pd() override {
			return _env.pd(); }

		Entrypoint &ep() override {
			return _env.ep(); }

		Ram_session_capability ram_session_cap() override {
			return _env.ram_session_cap(); }
		Cpu_session_capability cpu_session_cap() override {
			return _env.cpu_session_cap(); }

		Pd_session_capability pd_session_cap() override {
			return _env.pd_session_cap(); }

		Id_space<Parent::Client> &id_space() override {
			return _env.id_space(); }

		Session_capability session(Parent::Service_name const &name,
	                                   Parent::Client::Id id,
	                                   Parent::Session_args const &args,
	                                   Affinity             const &aff) override {
			return _env.session(name, id, args, aff); }


		void upgrade(Parent::Client::Id id,
		             Parent::Upgrade_args const &args) override {
			return _env.upgrade(id, args); }

		void close(Parent::Client::Id id) override {
			return _env.close(id); }
};


struct Libc::Timer
{
	::Timer::Connection _timer_connection;
	Genode::Timer       _timer;

	Timer(Genode::Env &env)
	:
		_timer_connection(env),
		_timer(_timer_connection, env.ep())
	{ }

	unsigned long curr_time() const
	{
		return _timer.curr_time().value/1000;
	}

	static Microseconds microseconds(unsigned long timeout_ms)
	{
		return Microseconds(1000*timeout_ms);
	}

	static unsigned long max_timeout()
	{
		return Genode::Timer::Microseconds::max().value/1000;
	}
};


/**
 * Interface for obtaining the libc-global timer instance
 *
 * The 'Timer' is instantiated on demand whenever the 'Timer_accessor::timer'
 * method is first called. This way, libc-using components do not depend of a
 * timer connection unless they actually use time-related functionality.
 */
struct Libc::Timer_accessor
{
	virtual Timer &timer() = 0;
};


struct Libc::Timeout_handler
{
	virtual void handle_timeout() = 0;
};


/*
 * TODO curr_time wrapping
 */
struct Libc::Timeout
{
	Libc::Timer_accessor              &_timer_accessor;
	Timeout_handler                   &_handler;
	Genode::One_shot_timeout<Timeout>  _timeout;

	bool          _expired             = true;
	unsigned long _absolute_timeout_ms = 0;

	void _handle(Microseconds now)
	{
		_expired             = true;
		_absolute_timeout_ms = 0;
		_handler.handle_timeout();
	}

	Timeout(Timer_accessor &timer_accessor, Timeout_handler &handler)
	:
		_timer_accessor(timer_accessor),
		_handler(handler),
		_timeout(_timer_accessor.timer()._timer, *this, &Timeout::_handle)
	{ }

	void start(unsigned long timeout_ms)
	{
		unsigned long const now = _timer_accessor.timer().curr_time();

		_expired             = false;
		_absolute_timeout_ms = now + timeout_ms;

		_timeout.start(_timer_accessor.timer().microseconds(timeout_ms));
	}

	unsigned long duration_left() const
	{
		unsigned long const now = _timer_accessor.timer().curr_time();

		return _expired ? 0 : _absolute_timeout_ms - now;
	}
};


struct Libc::Pthreads
{
	struct Pthread : Timeout_handler
	{
		Genode::Lock  lock { Genode::Lock::LOCKED };
		Pthread      *next { nullptr };

		Timeout _timeout;

		Pthread(Timer_accessor &timer_accessor, unsigned long timeout_ms)
		: _timeout(timer_accessor, *this)
		{
			if (timeout_ms > 0)
				_timeout.start(timeout_ms);
		}

		void handle_timeout()
		{
			lock.unlock();
		}
	};

	Genode::Lock    mutex;
	Pthread        *pthreads = nullptr;
	Timer_accessor &timer_accessor;


	Pthreads(Timer_accessor &timer_accessor)
	: timer_accessor(timer_accessor) { }

	void resume_all()
	{
		Genode::Lock::Guard g(mutex);

		for (Pthread *p = pthreads; p; p = p->next)
			p->lock.unlock();
	}

	unsigned long suspend_myself(unsigned long timeout_ms)
	{
		Pthread myself { timer_accessor, timeout_ms };
		{
			Genode::Lock::Guard g(mutex);

			myself.next = pthreads;
			pthreads    = &myself;
		}
		myself.lock.lock();
		{
			Genode::Lock::Guard g(mutex);

			/* address of pointer to next pthread allows to change the head */
			for (Pthread **next = &pthreads; *next; next = &(*next)->next) {
				if (*next == &myself) {
					*next = myself.next;
					break;
				}
			}
		}

		return timeout_ms > 0 ? myself._timeout.duration_left() : 0;
	}
};


extern void (*libc_select_notify)();

struct Libc::Io_response_handler : Vfs::Io_response_handler
{
	void handle_io_response(Vfs::Vfs_handle::Context *) override
	{
		/* some contexts may have been deblocked from select() */
		if (libc_select_notify)
			libc_select_notify();

		/* resume all as any context may have been deblocked from blocking I/O */
		Libc::resume_all();
	}
};


/* internal utility */
static void resumed_callback();
static void suspended_callback();


/**
 * Libc "kernel"
 *
 * This class represents the "kernel" of the libc-based application
 * Blocking and deblocking happens here on libc functions like read() or
 * select(). This combines blocking of the VFS backend and other signal sources
 * (e.g., timers). The libc task runs on the component thread and allocates a
 * secondary stack for the application task. Context switching uses
 * setjmp/longjmp.
 */
struct Libc::Kernel
{
	private:

		Genode::Env        &_env;
		Genode::Heap        _heap { _env.ram(), _env.rm() };
		Io_response_handler _io_response_handler;
		Env_implementation  _libc_env { _env, _heap, _io_response_handler };
		Vfs_plugin          _vfs { _libc_env, _heap };

		jmp_buf _kernel_context;
		jmp_buf _user_context;

		Genode::Thread &_myself { *Genode::Thread::myself() };

		void *_user_stack = {
			_myself.alloc_secondary_stack(_myself.name().string(),
			                              Component::stack_size()) };

		Genode::Reconstructible<Genode::Signal_handler<Kernel>> _resume_main_handler {
			_env.ep(), *this, &Kernel::_resume_main };

		void (*_original_suspended_callback)() = nullptr;

		enum State { KERNEL, USER };

		State _state = KERNEL;

		struct Timer_accessor : Libc::Timer_accessor
		{
			Genode::Env &_env;

			/*
			 * The '_timer' is constructed by whatever thread (main thread
			 * of pthread) that uses a time-related function first. Hence,
			 * the construction must be protected by a lock.
			 */
			Genode::Lock _lock;

			Genode::Constructible<Timer> _timer;

			Timer_accessor(Genode::Env &env) : _env(env) { }

			Timer &timer() override
			{
				Lock::Guard guard(_lock);

				if (!_timer.constructed())
					_timer.construct(_env);

				return *_timer;
			}
		};

		Timer_accessor _timer_accessor { _env };

		struct Main_timeout : Timeout_handler
		{
			Genode::Signal_context_capability _signal_cap;

			Timer_accessor        &_timer_accessor;
			Constructible<Timeout> _timeout;

			void _construct_timeout_once()
			{
				if (!_timeout.constructed())
					_timeout.construct(_timer_accessor, *this);
			}

			Main_timeout(Timer_accessor &timer_accessor)
			: _timer_accessor(timer_accessor)
			{ }

			void timeout(unsigned long timeout_ms, Signal_context_capability signal_cap)
			{
				_signal_cap = signal_cap;
				_construct_timeout_once();
				_timeout->start(timeout_ms);
			}

			unsigned long duration_left()
			{
				_construct_timeout_once();
				return _timeout->duration_left();
			}

			void handle_timeout()
			{
				/*
				 * XXX I don't dare to call _resume_main() here as this switches
				 * immediately to the user stack, which would result in dead lock
				 * if the calling context holds any lock in the timeout
				 * implementation.
				 */

				Genode::Signal_transmitter(_signal_cap).submit();
			}
		};

		Main_timeout _main_timeout { _timer_accessor };

		Pthreads _pthreads { _timer_accessor };

		/**
		 * Trampoline to application (user) code
		 *
		 * This function is called by the main thread.
		 */
		static void _user_entry(Libc::Kernel *kernel)
		{
			Libc::Component::construct(kernel->_libc_env);

			/* returned from user - switch stack to libc and return to dispatch loop */
			kernel->_switch_to_kernel();
		}

		bool _main_context() const { return &_myself == Genode::Thread::myself(); }

		/**
		 * Utility to switch main context to kernel
		 *
		 * User context must be saved explicitly before this function is called
		 * to enable _switch_to_user() later.
		 */
		void _switch_to_kernel()
		{
			_state = KERNEL;
			_longjmp(_kernel_context, 1);
		}

		/**
		 * Utility to switch main context to user
		 *
		 * Kernel context must be saved explicitly before this function is called
		 * to enable _switch_to_kernel() later.
		 */
		void _switch_to_user()
		{
			_state = USER;
			_longjmp(_user_context, 1);
		}

		/* called from signal handler */
		void _resume_main()
		{
			if (!_main_context() || _state != KERNEL) {
				Genode::error(__PRETTY_FUNCTION__, " called from non-kernel context");
				return;
			}

			if (!_setjmp(_kernel_context))
				_switch_to_user();
		}

		unsigned long _suspend_main(unsigned long timeout_ms)
		{
			if (timeout_ms > 0)
				_main_timeout.timeout(timeout_ms, *_resume_main_handler);

			if (!_setjmp(_user_context))
				_switch_to_kernel();

			return timeout_ms > 0 ? _main_timeout.duration_left() : 0;
		}

	public:

		Kernel(Genode::Env &env) : _env(env)
		{
			Genode::log("libc: kernel stack {",
			            Genode::Hex(Thread::myself()->mystack().base), ",",
			            Genode::Hex(Thread::myself()->mystack().top),
			            "} user stack {",
			            Genode::Hex((Genode::addr_t)_user_stack - Component::stack_size()),
			            ",", _user_stack, "}");
		}

		~Kernel() { Genode::error(__PRETTY_FUNCTION__, " should not be executed!"); }

		/**
		 * Setup kernel context and run libc application main context
		 *
		 * This function is called by the component thread at component
		 * construction time.
		 */
		void run()
		{
			if (!_main_context() || _state != KERNEL) {
				Genode::error(__PRETTY_FUNCTION__, " called from non-kernel context");
				return;
			}

			/* save continuation of libc kernel (incl. current stack) */
			if (!_setjmp(_kernel_context)) {
				/* _setjmp() returned directly -> switch to user stack and launch component */
				_state = USER;
				call_func(_user_stack, (void *)_user_entry, (void *)this);

				/* never reached */
			}

			/* _setjmp() returned after _longjmp() -> we're done */
		}

		/**
		 * Resume all contexts (main and pthreads)
		 */
		void resume_all()
		{
			Genode::Signal_transmitter(*_resume_main_handler).submit();

			_pthreads.resume_all();
		}

		/**
		 * Suspend this context (main or pthread)
		 */
		unsigned long suspend(unsigned long timeout_ms)
		{
			if (timeout_ms > 0
			 && timeout_ms > _timer_accessor.timer().max_timeout()) {
				Genode::warning("libc: limiting exceeding timeout of ",
				                timeout_ms, " ms to maximum of ",
				                _timer_accessor.timer().max_timeout(), " ms");

				timeout_ms = min(timeout_ms, _timer_accessor.timer().max_timeout());
			}

			return _main_context() ? _suspend_main(timeout_ms)
			                       : _pthreads.suspend_myself(timeout_ms);
		}

		unsigned long current_time()
		{
			return _timer_accessor.timer().curr_time();
		}

		/**
		 * Called from the main context (by fork)
		 */
		void schedule_suspend(void(*original_suspended_callback) ())
		{
			if (_state != USER) {
				Genode::error(__PRETTY_FUNCTION__, " called from non-user context");
				return;
			}

			/*
			 * We hook into suspend-resume callback chain to destruct and
			 * reconstruct parts of the kernel from the context of the initial
			 * thread, i.e., without holding any object locks.
			 */
			_original_suspended_callback = original_suspended_callback;
			_env.ep().schedule_suspend(suspended_callback, resumed_callback);

			if (!_setjmp(_user_context))
				_switch_to_kernel();
		}

		/**
		 * Called from the context of the initial thread (on fork)
		 */
		void entrypoint_suspended()
		{
			_resume_main_handler.destruct();

			_original_suspended_callback();
		}

		/**
		 * Called from the context of the initial thread (after fork)
		 */
		void entrypoint_resumed()
		{
			_resume_main_handler.construct(_env.ep(), *this, &Kernel::_resume_main);

			Genode::Signal_transmitter(*_resume_main_handler).submit();
		}
};


/**
 * Libc kernel singleton
 *
 * The singleton is implemented with the unmanaged-singleton utility
 * in Component::construct() to ensure it is never destructed
 * like normal static global objects. Otherwise, the task object may be
 * destructed in a RPC to Rpc_resume, which would result in a deadlock.
 */
static Libc::Kernel *kernel;


/**
 * Main context execution was suspended (on fork)
 *
 * This function is executed in the context of the initial thread.
 */
static void suspended_callback() { kernel->entrypoint_suspended(); }


/**
 * Resume main context execution (after fork)
 *
 * This function is executed in the context of the initial thread.
 */
static void resumed_callback() { kernel->entrypoint_resumed(); }


/*******************
 ** Libc task API **
 *******************/

void Libc::resume_all() { kernel->resume_all(); }


unsigned long Libc::suspend(unsigned long timeout_ms)
{
	return kernel->suspend(timeout_ms);
}


unsigned long Libc::current_time()
{
	return kernel->current_time();
}


void Libc::schedule_suspend(void (*suspended) ())
{
	if (!kernel) {
		error("libc kernel not initialized, needed for suspend");
		return;
	}
	kernel->schedule_suspend(suspended);
}


/***************************
 ** Component entry point **
 ***************************/

Genode::size_t Component::stack_size() { return Libc::Component::stack_size(); }


void Component::construct(Genode::Env &env)
{
	/* pass Genode::Env to libc subsystems that depend on it */
	Libc::init_mem_alloc(env);
	Libc::init_dl(env);

	/* initialize plugins that require Genode::Env */
	auto init_plugin = [&] (Libc::Plugin &plugin) {
		plugin.init(env);
	};
	Libc::plugin_registry()->for_each_plugin(init_plugin);

	kernel = unmanaged_singleton<Libc::Kernel>(env);
	kernel->run();
}


/**
 * Default stack size for libc-using components
 */
Genode::size_t Libc::Component::stack_size() __attribute__((weak));
Genode::size_t Libc::Component::stack_size() {
	return 32UL * 1024 * sizeof(Genode::addr_t); }


