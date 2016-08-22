SHARED_LIB   = yes
LIBS         = libc
DRM_SRC_DIR := $(call select_from_ports,drm)/src/lib/drm
LIB_DIR      = $(REP_DIR)/src/lib/drm

INC_DIR += $(DRM_SRC_DIR)/include/drm $(LIB_DIR)/include \
           $(DRM_SRC_DIR)

SRC_C = intel/intel_bufmgr.c \
        intel/intel_bufmgr_gem.c \
        intel/intel_decode.c \
        xf86drm.c xf86drmHash.c \
        xf86drmRandom.c

SRC_CC = dummies.cc

CC_OPT = -DHAVE_LIBDRM_ATOMIC_PRIMITIVES=1 -DO_CLOEXEC=0

vpath %.c  $(DRM_SRC_DIR)
vpath %.cc $(LIB_DIR)
