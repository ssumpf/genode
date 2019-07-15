/*
 * \brief  VM session component for 'base-hw'
 * \author Stefan Kalkowski
 * \date   2012-10-08
 */

/*
 * Copyright (C) 2012-2017 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <vm_session_component.h>
#include <platform.h>
#include <core_env.h>

using namespace Genode;


addr_t Vm_session_component::_alloc_ds()
{
	addr_t addr;
	if (platform().ram_alloc().alloc_aligned(_ds_size(), (void**)&addr,
		                                     get_page_size_log2()).error())
		throw Insufficient_ram_quota();
	return addr;
}


void Vm_session_component::_run(Vcpu_id)
{
	if (Kernel_object<Kernel::Vm>::_cap.valid())
		Kernel::run_vm(kernel_object());
}


void Vm_session_component::_pause(Vcpu_id)
{
	if (Kernel_object<Kernel::Vm>::_cap.valid())
		Kernel::pause_vm(kernel_object());
}
