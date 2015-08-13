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
.p2align 8
.global _machine_begin
_machine_begin:

/* 0x100 user mode */
j user_trap
.space 0x3c
/* 0x140 supervisor */
j supervisor_trap
.space 0x3c
/* 0x180 hypervisor */
1: j 1b
.space 0x3c
/* 0x1c0 machine */
j machine_trap
.space 0x38
/* 0x1fc non-maksable interrupt */
1: j 1b

user_trap:

	csrrw sp, mscratch, sp
	sd    t2, -8(sp)
	li    t2, 0
	j     put_char

supervisor_trap:

	sd    t2, -8(sp)
	li    t2, 1
	j     put_char

machine_trap:

	sd    t2, -8(sp)
	li    t2, 3
	j     put_char

put_char:

	sd  t0, -16(sp)
	sd  t1, -24(sp)

	/* check if ecall (8 - 11) */
	csrr t0, mcause
	li   t1, 8
	bltu t0, t1, trap_return
	li   t1, 12
	bgtu t0, t1, trap_return

	/* check for put char ecall number */
	li t1, 1
	bne t1, a0, trap_return

	/* output character */
	csrw mtohost, a1

1:li t0, 0
	csrrw t0, mfromhost, t0
	beqz t0, 1b

	/* advance epc */
	csrr t0, mepc
	addi t0, t0, 4
	csrw mepc, t0

	ld t0, -16(sp)
	ld t1, -24(sp)

	bnez t2, 2f
	ld t2,  -8(sp)

	csrrw sp, mscratch, sp
	eret

2:
	ld t2,  -8(sp)
	eret

trap_return:

	/* trap from user mode */
	bne t2, x0, 1f
	ld t2,  -8(sp)
	ld t0, -16(sp)
	ld t1, -24(sp)
	csrrw sp, mscratch, sp

	/* handle in supervisor */
	mrts

1: csrrw t0, mfromhost, x0
2:j 2b /* TODO: handle trap from supervisor or machine mode */

.global _machine_end
_machine_end:



.p2align 12
.global _mt_begin
_mt_begin:

/* 0x100 user mode */
1: j 1b
.space 0x3c
/* 0x140 supervisor */
j exception
.space 0x3c
/* 0x180 hypervisor */
1: j 1b
.space 0x3c
/* 0x1c0 machine */
j exception
.space 0x38
/* 0x1fc non-maksable interrupt */
1: j 1b

exception:


/* space for a copy of the kernel context */
.p2align 2
.global _mt_master_context_begin
_mt_master_context_begin:

/* space must be at least as large as 'Cpu_state' */
.space 34*8

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
