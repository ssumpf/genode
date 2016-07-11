SHARED_LIB = yes
LIBS       = libc

SRC_C = drivers/dri/swrast/swrast.c

MESA_PORT_DIR := $(call select_from_ports,mesa-11)/src/lib/mesa
MESA_SRC_DIR  := $(MESA_PORT_DIR)/src/mesa

INC_DIR += $(MESA_SRC_DIR) \
           $(MESA_SRC_DIR)/drivers/dri/common \
           $(MESA_PORT_DIR)/src \
           $(MESA_PORT_DIR)/include \
           $(MESA_PORT_DIR)/src/mapi \
           $(MESA_PORT_DIR)/src/gallium/auxiliary \
           $(MESA_PORT_DIR)/src/gallium/include \

CC_OPT = -DHAVE_PTHREAD -D_XOPEN_SOURCE=600

vpath %.c $(MESA_SRC_DIR)
