/**
 * \brief  Jump slot entry code for ARM platforms
 * \author Sebastian Sumpf
 * \date   2014-10-26
 */

/*
 * Copyright (C) 2014 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

.text
.globl _jmp_slot
.type  _jmp_slot,%function
/*
 *  stack[0] = RA
 *  ip = &GOT[n+3]
 *  lr = &GOT[2]
 */
_jmp_slot:

