.section ".text.crt0"

.global _start
_start:
j _start_next_page

/* leave first page empty for mode-transition page located at 0x100 */
.space 4096

_start_next_page:

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

/* save kernel stack pointer in mscratch */
csrw mscratch, sp

jal  setup_riscv_exception_vector
jal  init_kernel_up


/*********************************************
 ** Startup code that is common to all CPUs **
 *********************************************/

.global _start_secondary_cpus
_start_secondary_cpus:

jal init_kernel_mp

/*********************************
 ** .bss (non-initialized data) **
 *********************************/

.bss

	/* stack of the temporary initial environment */
	.p2align 8
	.space 32 * 1024
	_stack_high:
