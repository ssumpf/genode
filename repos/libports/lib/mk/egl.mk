SHARED_LIB = yes
LIBS       = libc

include $(REP_DIR)/lib/mk/mesa-11-common.inc

SRC_C = \
	main/eglsurface.c \
	main/eglconfig.c \
	main/eglglobals.c \
	main/egldisplay.c \
	main/eglfallbacks.c \
	main/eglsync.c \
	main/egllog.c \
	main/eglarray.c \
	main/eglimage.c \
	main/eglcontext.c \
	main/eglcurrent.c \
	main/eglapi.c \
	main/egldriver.c


CC_OPT += -D_EGL_NATIVE_PLATFORM=_EGL_PLATFORM_GENODE

MESA_PORT_DIR := $(call select_from_ports,mesa-11)/src/lib/mesa

vpath %.c $(MESA_PORT_DIR)/src/egl
