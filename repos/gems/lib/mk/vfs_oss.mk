SRC_CC := vfs_oss.cc

vpath %.cc $(REP_DIR)/src/lib/vfs/oss


SRC_C   := resample.c
INC_DIR += $(REP_DIR)/src/lib/vfs/oss/contrib
LIBS    += libc libm
CC_OPT  += -DOUTSIDE_SPEEX -DRANDOM_PREFIX=genode
vpath %.c  $(REP_DIR)/src/lib/vfs/oss/contrib


SHARED_LIB := yes
