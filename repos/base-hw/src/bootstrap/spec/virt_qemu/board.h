/*
 * \brief  Board driver for bootstrap
 * \author Stefan Kalkowski
 * \date   2019-05-10
 */

/*
 * Copyright (C) 2019 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#ifndef _BOOTSTRAP__SPEC__VIRT_QEMU__BOARD_H_
#define _BOOTSTRAP__SPEC__VIRT_QEMU__BOARD_H_

#include <hw/spec/arm_64/virt_qemu_board.h>
#include <hw/spec/arm_64/cpu.h>
#include <hw/spec/arm/lpae.h>
#include <spec/gicv3/pic.h>

namespace Bootstrap {
	using Cpu = Hw::Arm_64_cpu;
};

namespace Board {
	using namespace Hw::Virt_qemu_board;
};


namespace Bootstrap { struct Pic; }
struct Bootstrap::Pic : Hw::Pic
{
	void init_cpu_local();
};


#endif /* _BOOTSTRAP__SPEC__VIRT_QEMU__BOARD_H_ */
