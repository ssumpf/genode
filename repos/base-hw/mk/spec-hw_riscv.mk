SPECS += riscv 64bit

REP_INC_DIR += include/riscv

include $(call select_from_repositories,mk/spec-64bit.mk)
