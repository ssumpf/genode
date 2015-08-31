.section ".text"

.global _core_start
_core_start:

	/* create environment for main thread */
	jal init_main_thread

	/* load stack pointer from init_main_thread_result */
	la sp, init_main_thread_result
	ld sp, (sp)

	/* jump into init C-code */
	j _main
