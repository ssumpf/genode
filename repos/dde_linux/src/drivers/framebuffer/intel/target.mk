REQUIRES = x86

TARGET   = intel_fb_drv
LIBS     = base intel_fb_drv
SRC_CC   = main.cc

vpath %.cc $(PRG_DIR)
vpath %.cc $(REP_DIR)/src/lx_kit
