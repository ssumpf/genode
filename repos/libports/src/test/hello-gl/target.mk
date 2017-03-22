TARGET = hello_gl
LIBS   = libm libc egl mesa-11

SRC_C  = hello-gl.c eglut.c util.c
SRC_CC = eglut_genode.cc
CC_OLEVEL = -O0
EGLUT_DIR = $(REP_DIR)/src/lib/mesa/eglut

INC_DIR += $(EGLUT_DIR) $(REP_DIR)/src/lib/mesa/include

vpath %.c  $(EGLUT_DIR)
vpath %.cc $(EGLUT_DIR)

