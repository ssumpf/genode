LIBC_SOFTFLOAT_DIR = $(LIBC_DIR)/lib/libc/softfloat

SRC_C   = softfloat.c
INC_DIR = $(LIBC_SOFTFLOAT_DIR)
CC_OPT  = -DSOFTFLOAT_FOR_GCC

include $(REP_DIR)/lib/mk/libc-common.inc

vpath softfloat.c $(LIBC_SOFTFLOAT_DIR)/bits64

