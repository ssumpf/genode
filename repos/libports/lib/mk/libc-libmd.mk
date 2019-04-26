LIBC_LIBMD_DIR = $(LIBC_DIR)/lib/libmd

CC_OPT += -DWEAK_REFS

FILTER_OUT = mdXhl.c shadriver.c skeindriver.c rmddriver.c

SRC_C = $(filter-out $(FILTER_OUT),$(notdir $(wildcard $(LIBC_LIBMD_DIR)/*.c)))

INC_DIR += $(LIBC_DIR)/sys
INC_DIR += $(LIBC_LIBMD_DIR)

include $(REP_DIR)/lib/mk/libc-common.inc

vpath %.c $(LIBC_LIBMD_DIR)

CC_CXX_WARN_STRICT =
