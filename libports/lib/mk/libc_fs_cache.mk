SRC_CC   = plugin.cc
LIBS    += libc
INC_DIR += $(REP_DIR)/src/lib/libc

vpath plugin.cc $(REP_DIR)/src/lib/libc_fs_cache

SHARED_LIB = yes
