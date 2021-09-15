TARGET = intel_gpu_drv
SRC_CC = main.cc mmio_dump.cc
SRC_C  = gen9_renderstate.c
LIBS   = base

REQUIRES = x86_64

INC_DIR += $(PRG_DIR)
