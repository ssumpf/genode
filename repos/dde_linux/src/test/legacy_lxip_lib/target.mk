TARGET = test-legacy_lxip_lib

SRC_CC = main.cc

INC_DIR += $(REP_DIR)/src/lib/legacy_lxip

LIBS = base legacy_lxip lxip_include

CC_CXX_WARN_STRICT =

