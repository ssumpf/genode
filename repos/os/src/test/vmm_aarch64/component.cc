/*
 * \brief  VM session interface test for aarch64
 * \author Alexander Boettcher
 * \date   2019-06-17
 *
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <base/attached_dataspace.h>
#include <base/attached_rom_dataspace.h>
#include <base/component.h>
#include <base/heap.h>
#include <base/signal.h>
#include <timer_session/connection.h>
#include <util/reconstructible.h>
#include <vm_session/connection.h>
#include <vm_session/vm_session.h>

//#include <cpu/vm_state.h>

class Vm;

class Vcpu {

	private:

		Vm                                 &_vm;
		Genode::Vm_connection              &_vm_con;
		Genode::Vm_handler<Vcpu>            _handler;
		Genode::Vm_session_client::Vcpu_id  _vcpu;
		Genode::Attached_dataspace          _state_ds;
		Genode::Vm_state                   &_state;

		/* test state start - some status information to steer the test */
		unsigned                            _exit_count     { 0 };
		unsigned                            _pause_count    { 0 };
		unsigned                            _timer_count    { 0 };
		unsigned                            _pause_at_timer { 0 };
		enum {
			INITIAL,
			HALTED,
			PAUSED,
			UNKNOWN,
			RUNNING
		}                                   _test_state { INITIAL };
		/* test state end */

		void _handle_vm_exception();

		void _cpu_init()
		{
			Genode::error("cpu init");
		}

	public:

		Vcpu(Genode::Entrypoint &ep, Genode::Vm_connection &vm_con,
		     Genode::Allocator &alloc, Genode::Env &env, Vm &vm)
		:
			_vm(vm), _vm_con(vm_con),
			_handler(ep, *this, &Vcpu::_handle_vm_exception),
			/* construct vcpu */
			_vcpu(_vm_con.with_upgrade([&]() {
				return _vm_con.create_vcpu(alloc, env, _handler); })),
			/* get state of vcpu */
			_state_ds(env.rm(), _vm_con.cpu_state(_vcpu)),
			_state(*_state_ds.local_addr<Genode::Vm_state>())
		{
			Genode::log("vcpu ", _vcpu.id, " : created");
		}

		Genode::Vm_session_client::Vcpu_id id() const { return _vcpu; }

#if 0
		void skip_instruction(unsigned bytes)
		{
			_state = Genode::Vm_state {};
			_state.ip.value(_state.ip.value() + bytes);
		}
#endif

		/*
		 * state information and state requests to steer the test
		 */
		bool halted() const {
			 return _test_state == HALTED; }
		bool paused_1st() const {
			return _test_state == PAUSED && _pause_count == 1; }
		bool paused_2nd() const {
			return _test_state == PAUSED && _pause_count == 2; }
		bool paused_3rd() const {
			return _test_state == PAUSED && _pause_count == 3; }
		bool paused_4th() const {
			return _test_state == PAUSED && _pause_count == 4; }

		void break_endless_loop()
		{
			_pause_at_timer = _timer_count + 3;
		}
		bool pause_endless_loop()
		{
			if (_pause_at_timer == 0)
				return false;

			if (_timer_count < _pause_at_timer)
				return false;

			_pause_at_timer = 0;
			return true;
		}

		void claim_state_unknown() { _test_state = UNKNOWN; }

		void timer_triggered() { _timer_count ++; }
};

class Vm {

	private:

		enum { STACK_SIZE = 2*1024*sizeof(long) };

		Genode::Heap                 _heap;
		Genode::Vm_connection        _vm_con;
		Genode::Entrypoint          &_ep_first;  /* running on first CPU */
//		Genode::Entrypoint           _ep_second; /* running on second CPU */
		Vcpu                         _vcpu0;
//		Vcpu                         _vcpu1;
//		Vcpu                         _vcpu2;
//		Vcpu                         _vcpu3;
		Genode::Dataspace_capability _memory; /* guest memory */

		/* just to trigger some events after some time */
		Timer::Connection            _timer;
		Genode::Signal_handler<Vm>   _timer_handler;

		/* trigger destruction of _vm session to test this case also */
		Genode::Signal_context_capability _signal_destruction;

		void _handle_timer();

	public:

		Vm(Genode::Env &env, Genode::Signal_context_capability destruct_cap)
		:
			_heap(env.ram(), env.rm()),
			_vm_con(env),
			_ep_first(env.ep()),
//			_ep_second(env, STACK_SIZE, "second ep",
//			           env.cpu().affinity_space().location_of_index(1)),
			_vcpu0(_ep_first, _vm_con, _heap, env, *this),
//			_vcpu1(_ep_first, _vm_con, _heap, env, *this),
//			_vcpu2(_ep_second, _vm_con, _heap, env, *this),
//			_vcpu3(_ep_second, _vm_con, _heap, env, *this),
			_memory(env.ram().alloc(4096)),
			_timer(env),
			_timer_handler(_ep_first, *this, &Vm::_handle_timer),
			_signal_destruction(destruct_cap)
		{
			/* prepare guest memory with some instructions for testing */
			Genode::uint8_t * guest = env.rm().attach(_memory);
			Genode::error("instruction for guest missing");
#if 0
			*(guest + 0xff0) = 0x0f; /* CPUID instruction */
			*(guest + 0xff1) = 0xa2;
#endif
			*(guest + 0xff0) = 0xf4; /* HLT instruction */
			*(guest + 0xff1) = 0xf4; /* HLT instruction */
			*(guest + 0xff2) = 0xeb; /* JMP - endless loop to RIP */
			*(guest + 0xff3) = 0xfe; /* JMP   of -2 byte (size of JMP inst) */
			*(guest + 0xff4) = 0xf4; /* HLT instruction */
			env.rm().detach(guest);

			Genode::log ("let vCPUs run - first EP");
			_vm_con.run(_vcpu0.id());
//			_vm_con.run(_vcpu1.id());

//			Genode::log ("let vCPUs run - second EP");
//			_vm_con.run(_vcpu2.id());
//			_vm_con.run(_vcpu3.id());

//			_timer.sigh(_timer_handler);
//			_timer.trigger_periodic(1000 * 1000 /* in us */);
		}

		Genode::Dataspace_capability handle_guest_memory_exit()
		{
			/*
			 * A real VMM would now have to lookup the right dataspace for
			 * the given guest physical region. This simple test has just one
			 * supported region ...
			 */
			return _memory;
		}
};


/**
 * Handle timer events - used to trigger some pause/resume on vCPU for testing
 */
void Vm::_handle_timer()
{
	_vcpu0.timer_triggered();
//	_vcpu1.timer_triggered();
//	_vcpu2.timer_triggered();
//	_vcpu3.timer_triggered();
	Genode::warning("timer triggered");
#if 0
	/*
	 * We're running in context of _ep_first. Try to trigger remotely
	 * for vCPU2 (handled by _ep_second actually) pause/run. Remotely means
	 * that vCPU2 is not on the same physical CPU as _ep_first.
	 */
	if (_vcpu2.halted()) {
		/* test to trigger a Genode signal even if we're already blocked */
		_vm_con.pause(_vcpu2.id());
	}

	if (_vcpu2.paused_1st()) {
		Genode::log(Genode::Thread::myself()->name(), "     : request resume of vcpu ", _vcpu2.id().id);

		/* continue after first paused state */
		_vm_con.run(_vcpu2.id());
	} else if (_vcpu2.paused_2nd()) {
		Genode::log(Genode::Thread::myself()->name(), "     : request resume of vcpu ", _vcpu2.id().id);

		/* skip over next hlt instructions after second paused state */
		_vcpu2.skip_instruction(1*1 /* 1x hlt instruction size */);

		/* reset state to unknown, otherwise we may enter this a second time */
		_vcpu2.claim_state_unknown();

		/* the next instruction is again a hlt */
		_vm_con.run(_vcpu2.id());
	}

	/*
	 * pause/run for vCPU0 in context of right _ep_first - meaning both
	 * are on same physical CPU.
	 */
	if (_vcpu1.pause_endless_loop()) {
		Genode::log("pause endless loop");
		/* guest in endless jmp loop - request to stop it asap */
		_vm_con.pause(_vcpu1.id());
		return;
	}

	if (_vcpu1.halted()) {
		Genode::log(Genode::Thread::myself()->name(), "     : request pause of vcpu ", _vcpu1.id().id);
		/* test to trigger a Genode signal even if we're already blocked */
		_vm_con.pause(_vcpu1.id());
	}

	if (_vcpu1.paused_1st()) {
		Genode::log(Genode::Thread::myself()->name(), "     : request resume (A) of vcpu ", _vcpu1.id().id);

		/* continue after first paused state */
		_vm_con.run(_vcpu1.id());
	} else if (_vcpu1.paused_2nd()) {
		Genode::log(Genode::Thread::myself()->name(), "     : request resume (B) of vcpu ", _vcpu1.id().id);

		/* skip over next 2 hlt instructions after second paused state */
		_vcpu1.skip_instruction(2*1 /* 2x hlt instruction size */);

		/* reset state to unknown, otherwise we may enter this a second time */
		_vcpu1.claim_state_unknown();

		/* the next instruction is actually a jmp endless loop */
		_vm_con.run(_vcpu1.id());

		/* request on the next timeout to stop the jmp endless loop */
		_vcpu1.break_endless_loop();
	} else if (_vcpu1.paused_3rd()) {
		Genode::log(Genode::Thread::myself()->name(), "     : request resume (C) of vcpu ", _vcpu1.id().id);

		_vcpu1.skip_instruction(1*2 /* 1x jmp endless loop size */);
		_vm_con.run(_vcpu1.id());
	} else if (_vcpu1.paused_4th()) {
		Genode::log("vcpu test finished - de-arm timer");
		_timer.trigger_periodic(0);

		/* trigger destruction of VM session */
		Genode::Signal_transmitter(_signal_destruction).submit();
	}
#endif
}

/**
 * Handle VM exits ...
 */
void Vcpu::_handle_vm_exception()
{
	using namespace Genode;

	Genode::error("vm exit");
#if 0
	enum { VMEXIT_STARTUP = 0xfe, VMEXIT_PAUSED = 0xff };

	unsigned const exit = _state.exit_reason;

	_state = Vm_state {};

	_exit_count++;

	log("vcpu ", _vcpu.id, " : ", _exit_count, ". vm exit - ",
	    "reason ", Hex(exit), " handled by '",
	    Genode::Thread::myself()->name(), "'");

	if (exit == VMEXIT_STARTUP) {
		_cpu_init();
	}

	if (exit == Intel_exit::INVALID_STATE) {
		error("vcpu ", _vcpu.id, " : ", _exit_count, ". vm exit - "
		      " halting vCPU - invalid guest state");
		_test_state = UNKNOWN;
		return;
	}

	if (exit == Amd_exit::TRIPLE_FAULT) {
		error("vcpu ", _vcpu.id, " : ", _exit_count, ". vm exit - "
		      " halting vCPU - triple fault");
		_test_state = UNKNOWN;
		return;
	}

	if (exit == VMEXIT_PAUSED) {
		log("vcpu ", _vcpu.id, " : ", _exit_count, ". vm exit - "
		    " due to pause() request - ip=", Hex(_state.ip.value()));
		_pause_count ++;
		_test_state = PAUSED;
		return;
	}

	if (exit == Intel_exit::HLT || exit == Amd_exit::HLT) {
		log("vcpu ", _vcpu.id, " : ", _exit_count, ". vm exit - "
		    " halting vCPU - guest called HLT - ip=", Hex(_state.ip.value()));
		_test_state = HALTED;
		return;
	}

	if (exit == Intel_exit::EPT ||
	    exit == Amd_exit::NPT || exit == Amd_exit::PF)
	{
		addr_t const guest_fault_addr = _state.qual_secondary.value();
		addr_t const guest_map_addr   = _state.qual_secondary.value() & ~0xFFFUL;

		log("vcpu ", _vcpu.id, " : ", _exit_count, ". vm exit - "
		    " guest fault address: ", Hex(guest_fault_addr));

		Dataspace_capability cap = _vm.handle_guest_memory_exit();
		if (!cap.valid()) {
			error("vcpu ", _vcpu.id, " : ", _exit_count, ". vm exit - "
			      " halting vCPU - guest memory lookup failed");
			_test_state = UNKNOWN;
			/* no memory - we halt the vcpu */
			return;
		}
		if (guest_fault_addr != 0xfffffff0UL) {
			error("vcpu ", _vcpu.id, " : ", _exit_count, ". vm exit - "
			      " unknown guest fault address");
			return;
		}

		_vm_con.attach(cap, guest_map_addr);
	}

	if (_exit_count >= 5) {
		error("vcpu ", _vcpu.id, " : ", _exit_count, ". vm exit - "
		      " halting vCPU - unknown state");
		_test_state = UNKNOWN;
		return;
	}

	log("vcpu ", _vcpu.id, " : ", _exit_count, ". vm exit - resume vcpu");

	_test_state = RUNNING;
	_vm_con.run(_vcpu);
#endif
}

class Vmm {

	private:

		Genode::Signal_handler<Vmm> _destruct_handler;
		Genode::Reconstructible<Vm> _vm;

		void _destruct()
		{
			Genode::log("destruct vm session");

			_vm.destruct();

			Genode::log("vmm test finished");
		}

	public:

		Vmm(Genode::Env &env)
		:
			_destruct_handler(env.ep(), *this, &Vmm::_destruct),
			_vm(env, _destruct_handler)
		{
		}
};

void Component::construct(Genode::Env & env) { static Vmm vmm(env); }
