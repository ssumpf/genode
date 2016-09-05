SHARED_LIB = yes
LIBS       = libc blit i965

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
	main/egldriver.c \
	drivers/dri2/egl_dri2.c \
	platform.c

SRC_CC = genode_interface.cc

CC_OPT  += -D_EGL_NATIVE_PLATFORM=_EGL_PLATFORM_GENODE -D_EGL_BUILT_IN_DRIVER_DRI2 \
           -DHAVE_GENODE_PLATFORM

INC_DIR += $(MESA_PORT_DIR)/src/egl/main \
           $(MESA_PORT_DIR)/src/egl/drivers/dri2

# XXX: Remove
INC_DIR += $(REP_DIR)/../dde_linux/src/lib/framebuffer/intel/include
INC_DIR += $(REP_DIR)/../dde_linux/src/include

vpath %.c  $(MESA_PORT_DIR)/src/egl
vpath %.c  $(LIB_DIR)/egl
vpath %.cc $(LIB_DIR)/egl
