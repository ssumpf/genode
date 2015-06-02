.section ".text.crt0"

.global _start
_start:

 /* clear the bss segment */
la   a0, _bss_start
la   a1, _bss_end
1:
sd   x0, (a0)
addi a0, a0, 8
bne  a0, a1, 1b


la   sp, kernel_stack
la   a0, kernel_stack_size
ld   a0, (a0)
add  sp, sp, a0
j    init_kernel_up

/*********************************
 ** .bss (non-initialized data) **
 *********************************/

.bss

	/* stack of the temporary initial environment */
	.p2align 8
	.space 32 * 1024
	_stack_high:
