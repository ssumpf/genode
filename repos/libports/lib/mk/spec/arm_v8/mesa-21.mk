SHARED_LIB := yes
LIBS       += libdrm

LIBS += etnaviv

CC_OPT += -DGALLIUM_ETNAVIV

include $(REP_DIR)/lib/mk/mesa-21.inc

# use etnaviv_drmif.h from mesa DRM backend
INC_DIR += $(MESA_SRC_DIR)/src/etnaviv
