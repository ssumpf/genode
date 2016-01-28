#
# \brief  Build config for Genodes core process
# \author Sebastian Sumpf
# \date   2012-10-04
#

INC_DIR += $(REP_DIR)/src/core/include/spec/riscv

CC_OPT += -fno-delete-null-pointer-checks

# add C++ sources
SRC_CC += platform_services.cc
SRC_CC += kernel/vm_thread.cc
SRC_CC += spec/riscv/kernel/cpu_context.cc
SRC_CC += spec/riscv/kernel/thread_base.cc
SRC_CC += spec/riscv/kernel/thread.cc
SRC_CC += spec/riscv/kernel/pd.cc
SRC_CC += spec/riscv/kernel/cpu.cc
SRC_CC += spec/riscv/platform_support.cc

#add assembly sources
SRC_S += spec/riscv/mode_transition.s
SRC_S += spec/riscv/kernel/crt0.s
SRC_S += spec/riscv/crt0.s

# include less specific configuration
include $(REP_DIR)/lib/mk/core.inc
