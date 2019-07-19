TARGET    = vmm
REQUIRES  = hw arm_v8
LIBS      = base
SRC_CC    = main.cc vmm.cc cpu.cc device.cc pl011.cc
INC_DIR  += $(PRG_DIR)

CC_CXX_WARN_STRICT :=
