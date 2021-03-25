/*
 * \brief  Lx::Task represents a cooperatively scheduled thread of control
 * \author Sebastian Sumpf
 * \author Josef Soentgen
 * \author Norman Feske
 * \date   2014-10-10
 */

/*
 * Copyright (C) 2014-2017 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#ifndef _LX_KIT__INTERNAL__TASK_H_
#define _LX_KIT__INTERNAL__TASK_H_

/* Genode includes */
#include <base/log.h>
#include <base/thread.h>
#include <base/sleep.h>

/* Linux emulation environment includes */
#include <lx_kit/internal/list.h>
#include <lx_kit/internal/arch_execute.h>


namespace Lx {

	class Task;
}

/**
 * Allows pseudo-parallel execution of functions
 */
class Lx::Task : public Lx_kit::List<Lx::Task>::Element
{
	public:

		/**
		 * TODO generalize - higher is more important
		 */
		enum Priority { PRIORITY_0, PRIORITY_1, PRIORITY_2, PRIORITY_3 };

		/**
		 * Runtime state
		 *
		 *                        INIT
		 *                         |
		 *                       [run]
		 *                         v
		 * BLOCKED <--[block]--- RUNNING
		 *         --[unblock]->
		 */
		enum State { STATE_INIT, STATE_RUNNING, STATE_BLOCKED };

	private:

		bool verbose = false;

		State _state = STATE_INIT;

		bool _parked = false;
		bool _park   = false;

		/* sub-classes may overwrite the runnable condition */
		virtual bool _runnable() const
		{
			switch (_state) {
			case STATE_INIT:          return true;
			case STATE_RUNNING:       return true;
			case STATE_BLOCKED:       return false;
			}

			Genode::error("state ", (int)_state, " not handled by switch");
			Genode::sleep_forever();
		}

		void        *_stack     = nullptr;       /* stack pointer */
		jmp_buf      _env;                       /* execution state */
		jmp_buf      _saved_env;                 /* saved state of thread calling run() */

		Priority     _priority;
		Scheduler   &_scheduler;         /* scheduler this task is attached to */

		void       (*_func)(void *);     /* function to call*/
		void        *_arg;               /* argument for function */
		char const  *_name;              /* name of task */

	public:

		Task(void (*func)(void*), void *arg, char const *name,
		     Priority priority, Scheduler &scheduler);

		virtual ~Task();

		State    state()    const { return _state;    }
		Priority priority() const { return _priority; }

		/*******************************
		 ** Runtime state transitions **
		 *******************************/

		void block()
		{
			if (_state == STATE_RUNNING) {
				_state = STATE_BLOCKED;
			}
		}

		void unblock()
		{
			if (_parked) {
				Genode::error(__func__, ": cannot unblock parked task: '", name(), "' (", this, ")");
				return;
			}
			if (_state == STATE_BLOCKED) {
				_state = STATE_RUNNING;
			}
		}

		void park()
		{
			_park = true;
		}

		void parked()
		{
			_park   = false;
			_parked = true;
		}

		bool should_park() const { return _park; }

		void unpark()
		{
			_parked = false;
		}

		/**
		 * Run task until next preemption point
		 *
		 * \return true if run, false if not runnable
		 */
		bool run()
		{
			if (!_runnable())
				return false;

			/*
			 * Save the execution environment. The scheduled task returns to this point
			 * after execution, i.e., at the next preemption point.
			 */
			if (_setjmp(_saved_env))
				return true;

			if (_state == STATE_INIT) {
				/* setup execution environment and call task's function */
				_state = STATE_RUNNING;
				Genode::Thread *th = Genode::Thread::myself();

				enum { STACK_SIZE = 32 * 1024 }; /* FIXME make stack size configurable */
				_stack = th->alloc_secondary_stack(_name, STACK_SIZE);

				/* switch stack and call '_func(_arg)' */
				arch_execute(_stack, (void *)_func, _arg);
			} else {
				/* restore execution environment */
				_longjmp(_env, 1);
			}

			/* never reached */
			Genode::error("unexpected return of task");
			Genode::sleep_forever();
		}

		/**
		 * Request scheduling (of other tasks)
		 *
		 * Note, this task may not be blocked when calling schedule() depending
		 * on the use case.
		 */
		void schedule()
		{
			/*
			 * Save the execution environment. The task will resume from here on next
			 * schedule.
			 */
			if (_setjmp(_env))
				return;

			/* return to thread calling run() */
			_longjmp(_saved_env, 1);
		}

		/**
		 * Shortcut to enter blocking state and request scheduling
		 */
		void block_and_schedule()
		{
			block();
			schedule();
		}

		/**
		 * Return the name of the task (mainly for debugging purposes)
		 */
		char const *name() { return _name; }
};


#endif /* _LX_KIT__INTERNAL__TASK_H_ */
