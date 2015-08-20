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
.set USER_MODE,       0
.set SUPERVISOR_MODE, 1
.set MACHINE_MODE,    3

.set CALL_PUT_CHAR,      1
.set CALL_PROGRAM_TIMER, 2


.macro _save_scratch_registers mode

	.if \mode == USER_MODE
		csrrw sp, mscratch, sp
	.endif

	addi sp, sp, -24
	sd t0, 0(sp)
	sd t1, 8(sp)
	sd t2, 16(sp)
.endm

.macro  _restore_scratch_registers mode
	ld t0, 0(sp)
	ld t1, 8(sp)
	ld t2, 16(sp)
	addi sp, sp, 24

	.if \mode == USER_MODE
		csrrw sp, mscratch, sp
	.endif
.endm

.macro _put_char mode

	/* check if ecall (8 - 11) */
	csrr t0, mcause
	li   t1, 8
	bltu t0, t1, 9f
	li   t1, 12
	bgtu t0, t1, 9f

	/* check for put char ecall number */
	li t1, CALL_PUT_CHAR
	bne t1, a0, 9f

	/* output character */
	csrw mtohost, a1

1:
	li t0, 0
	csrrw t0, mfromhost, t0
	beqz t0, 1b

	/* advance epc */
	csrr t0, mepc
	addi t0, t0, 4
	csrw mepc, t0

	_restore_scratch_registers \mode
	eret
9:
.endm

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

	_save_scratch_registers USER_MODE
	_put_char USER_MODE
	_restore_scratch_registers USER_MODE
	mrts

supervisor_trap:

	_save_scratch_registers SUPERVISOR_MODE
	_put_char SUPERVISOR_MODE
	j fault

machine_trap:

	_save_scratch_registers MACHINE_MODE
	_put_char MACHINE_MODE
	j fault


fault:j fault /* TODO: handle trap from supervisor or machine mode */

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
