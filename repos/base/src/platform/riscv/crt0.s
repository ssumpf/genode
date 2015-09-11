.section ".text"

.global _start
_start:

	/* current ip */
	auipc sp, 0

	/* lower 12 bits of STACK (negative) */
	mv  t0, x0
	addi t0, t0, %lo(STACK)

	/* lower 12 bits of _start */
	mv  t1, x0
	addi t1, t1, %lo(_start)

	/* offset form _start to STACK (negative) */
	sub  t0,  t1, t0

	/* address of STACK */
	sub t0, sp, t0

	/* read offset of stack_high from STACK */
	ld t0, (t0)

	/* add to _start */
	add sp, sp, t0

	/* relocate linker */
	jal init_rtld

	/* create environment for main thread */
	jal init_main_thread

	/* load stack pointer from init_main_thread_result */
	la sp, init_main_thread_result
	ld sp, (sp)

	mv s0, x0

	/* jump into init C-code */
	j _main

.p2align 3
	STACK:
	.quad _stack_high - _start

.bss
	.p2align 8
	.space 32*1024
	_stack_high:
