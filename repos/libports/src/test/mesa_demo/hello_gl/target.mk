TARGET = hello_gl
LIBS   = libm libc egl mesa

SRC_C  = hello-gl.c eglut.c util.c
SRC_CC = eglut_genode.cc
LD_OPT = --export-dynamic

EGLUT_DIR = $(PRG_DIR)/../eglut

INC_DIR += $(REP_DIR)/src/lib/mesa/include \
           $(EGLUT_DIR)

vpath %.c  $(EGLUT_DIR)
vpath %.cc $(EGLUT_DIR)

