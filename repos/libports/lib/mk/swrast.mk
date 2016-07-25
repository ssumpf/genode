SHARED_LIB = yes
LIBS       = libc mesa-11

include $(REP_DIR)/lib/mk/mesa-11-common.inc

SRC_C    = drivers/dri/swrast/swrast.c
INC_DIR += $(MESA_SRC_DIR)/drivers/dri/common

vpath %.c $(MESA_SRC_DIR)
