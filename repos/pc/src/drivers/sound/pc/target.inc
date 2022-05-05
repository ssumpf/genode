REQUIRES := x86

REL_PRG_DIR := $(PRG_DIR)/../..

TARGET := pc_sound
LIBS   := base pc_lx_emul

INC_DIR += $(REL_PRG_DIR)

SRC_CC += main.cc
SRC_CC += misc.cc
SRC_C  += $(notdir $(wildcard $(REL_PRG_DIR)/generated_dummies.c))
SRC_C  += common_dummies.c
SRC_C  += dummies.c
SRC_C  += lx_emul.c
SRC_C  += lx_emul/spec/x86/pci.c

vpath %.c  $(REL_PRG_DIR)
vpath %.cc $(REL_PRG_DIR)
vpath common_dummies.c $(REP_DIR)/src/lib/pc/lx_emul
