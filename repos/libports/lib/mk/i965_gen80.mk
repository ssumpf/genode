LIBS = libc

include $(REP_DIR)/lib/mk/mesa-common.inc

CC_OPT  += -DGEN_VERSIONx10=80
include $(REP_DIR)/lib/mk/i965_gen.inc

