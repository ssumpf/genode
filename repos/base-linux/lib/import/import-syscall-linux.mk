HOST_INC_DIR += $(dir $(call select_from_repositories,src/lib/syscall/linux_syscalls.h))

ifeq ($(filter-out $(SPECS),x86),)
	include $(REP_DIR)/lib/import/spec/x86/import-syscall-linux.mk
endif

ifeq ($(filter-out $(SPECS),arm_v7a),)
	include $(REP_DIR)/lib/import/spec/arm_v7a/import-syscall-linux.mk
endif
