INC_DIR += $(REP_DIR)/src/core/spec/riscv

CC_OPT += -fno-delete-null-pointer-checks

# add C++ sources
SRC_CC += platform_services.cc
SRC_CC += kernel/vm_thread_off.cc kernel/kernel.cc
SRC_CC += spec/riscv/kernel/cpu_context.cc
SRC_CC += spec/riscv/kernel/thread.cc
SRC_CC += spec/riscv/kernel/pd.cc
SRC_CC += spec/riscv/kernel/cpu.cc
SRC_CC += spec/riscv/platform_support.cc

#add assembly sources
SRC_S += $(REP_DIR)/src/bootstrap/spec/riscv/exception_vector.s
SRC_S += spec/riscv/crt0.s

# include less specific configuration
include $(REP_DIR)/lib/mk/core-hw.inc
