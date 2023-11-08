SHARED_LIB = yes

VFS_DIR  = $(REP_DIR)/src/lib/vfs/lxip
LIBS     = lxip
SRC_CC   = vfs.cc
LD_OPT  += --version-script=$(VFS_DIR)/symbol.map

vpath %.cc $(VFS_DIR)
