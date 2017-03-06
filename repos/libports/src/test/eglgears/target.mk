TARGET = gears
LIBS   = libm libc libc-setjmp egl mesa-11

SRC_C  = eglgears.c eglut.c
SRC_CC = eglut_genode.cc
CC_OLEVEL = -O0
EGLUT_DIR = $(REP_DIR)/src/lib/mesa/eglut

INC_DIR += $(EGLUT_DIR) $(REP_DIR)/src/lib/mesa/include

# XXX: Remove
INC_DIR += $(REP_DIR)/../dde_linux/src/lib/framebuffer/intel/include
INC_DIR += $(REP_DIR)/../dde_linux/src/include
INC_DIR += $(REP_DIR)/../dde_linux/src/include/spec/x86_64
LIBS += intel_fb

vpath %.c  $(EGLUT_DIR)
vpath %.cc $(EGLUT_DIR)

