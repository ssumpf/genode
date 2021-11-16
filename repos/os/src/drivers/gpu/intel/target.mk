TARGET = intel_gpu_drv
SRC_CC = main.cc mmio_dump.cc
LIBS   = base

REQUIRES = x86
CC_CXX_WARN_STRICT =

INC_DIR += $(PRG_DIR)
