/*
 * \brief  Transition between kernel/userland
 * \date   2011-11-15
 */

/*
 * Copyright (C) 2011-2015 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU General Public License version 2.
 */

.section .text

/*
 * Page aligned base of mode transition code.
 *
 * This position independent code switches between a kernel context and a
 * user context and thereby between their address spaces. Due to the latter
 * it must be mapped executable to the same region in every address space.
 * To enable such switching, the kernel context must be stored within this
 * region, thus one should map it solely accessable for privileged modes.
 */
.p2align 12
.global _mt_begin
_mt_begin:

/* 0x100 user mode */
1: j 1b
.space 0x3c
/* 0x140 supervisor */
j machine_exception
.space 0x3c
/* 0x180 hypervisor */
1: j 1b
.space 0x3c
/* 0x1c0 machine */
j machine_exception
.space 0x38
/* 0x1fc non-maksable interrupt */
1: j 1b

machine_exception:
csrw mscratch, t0
csrw sscratch, t1
csrr t0, mcause
li   t1, 8
bltu t0, t1, machine_leave
li   t1, 1
bne t1, a0, machine_leave
csrw mtohost, a1

1:
csrrw t0, mfromhost, x0
bne t0, x0, 1b

machine_leave:
csrr  t0, mepc
addi t0, t0, 4
csrw mepc, t0
csrr t0, mscratch
csrr t1, sscratch
eret

/* space for a copy of the kernel context */
.p2align 2
.global _mt_master_context_begin
_mt_master_context_begin:

/* space must be at least as large as 'Cpu_state' */
.space 33*8

.global _mt_master_context_end
_mt_master_context_end:

/* space for a client context-pointer per CPU */
.p2align 2
.global _mt_client_context_ptr
_mt_client_context_ptr:
.space 8

.global _mt_kernel_entry_pic
_mt_kernel_entry_pic:

.global _mt_user_entry_pic
_mt_user_entry_pic:


/* end of the mode transition code */
.global _mt_end
_mt_end:
