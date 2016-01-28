/*
 * \brief  Interface between kernel and userland
 * \author Sebastian Sumpf
 * \date   2015-06-01
 */

/*
 * Copyright (C) 2015 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

#ifndef _KERNEL__INTERFACE_SUPPORT_H_
#define _KERNEL__INTERFACE_SUPPORT_H_

#include <base/stdint.h>

namespace Kernel {

	typedef Genode::uint64_t Call_arg;
	typedef Genode::uint64_t Call_ret;
}

#endif /* _KERNEL__INTERFACE_SUPPORT_H_ */

