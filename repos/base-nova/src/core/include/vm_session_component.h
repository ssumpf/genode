/*
 * \brief  Core-specific instance of the VM session interface
 * \author Alexander Boettcher
 * \date   2018-08-26
 */

/*
 * Copyright (C) 2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _CORE__VM_SESSION_COMPONENT_H_
#define _CORE__VM_SESSION_COMPONENT_H_

/* Genode includes */
#include <base/allocator_guard.h>
#include <base/rpc_server.h>
#include <vm_session/vm_session.h>

namespace Genode { class Vm_session_component; }

class Genode::Vm_session_component
:
	private Ram_quota_guard,
	private Cap_quota_guard,
	public Rpc_object<Vm_session, Vm_session_component>
{
	private:

		class Vcpu : public List<Vcpu>::Element {

			public:

				enum State { INIT, ALIVE };

			private:

				Constrained_ram_allocator    &_ram_alloc;
				Cap_quota_guard              &_cap_alloc;
				Ram_dataspace_capability      _ds_cap { };
				addr_t                        _sel_sm_ec_sc;
				addr_t                        _vm_pt_cnt { 0 };
				Vcpu_id const                 _id;
				State                         _state { INIT };

			public:

				Vcpu(Constrained_ram_allocator &ram_alloc,
				     Cap_quota_guard &cap_alloc,
				     Vcpu_id const id);

				~Vcpu();

				addr_t sm_sel() const { return _sel_sm_ec_sc + 0; }
				addr_t ec_sel() const { return _sel_sm_ec_sc + 1; }
				addr_t sc_sel() const { return _sel_sm_ec_sc + 2; }

				addr_t new_pt_id();

				bool match(Vcpu_id const id) const { return id.id == _id.id; }
				Ram_dataspace_capability ds_cap() const { return _ds_cap; }

				bool init() const { return _state == State::INIT; }
				void alive() { _state = ALIVE; };

				static addr_t invalid() { return ~0UL; }
		};

		Rpc_entrypoint            &_ep;
		Constrained_ram_allocator  _constrained_md_ram_alloc;
		Sliced_heap                _sliced_heap;
		addr_t                     _pd_sel   { 0 };
		unsigned                   _id_alloc { 0 };
		unsigned                   _priority;

		List<Vcpu>         _vcpus { };

		Vcpu * _lookup(Vcpu_id const vcpu_id)
		{
			for (Vcpu * vcpu = _vcpus.first(); vcpu; vcpu = vcpu->next())
				if (vcpu->match(vcpu_id)) return vcpu;

			return nullptr;
		}

	protected:

		Ram_quota_guard &_ram_quota_guard() { return *this; }
		Cap_quota_guard &_cap_quota_guard() { return *this; }

	public:

		using Ram_quota_guard::upgrade;
		using Cap_quota_guard::upgrade;

		Vm_session_component(Rpc_entrypoint &, Resources, Label const &,
		                     Diag, Ram_allocator &ram, Region_map &);
		~Vm_session_component();

		/**************************
		 ** Vm session interface **
		 **************************/

		Dataspace_capability _cpu_state(Vcpu_id);

		void _exception_handler(Signal_context_capability, Vcpu_id);
		void _run(Vcpu_id);
		void _pause(Vcpu_id) { }
		void attach(Dataspace_capability, addr_t) override;
		void attach_pic(addr_t) override {}
		void detach(addr_t, size_t) override { }
		void _create_vcpu(Thread_capability);
};

#endif /* _CORE__VM_SESSION_COMPONENT_H_ */
