
LIBS = libc libdrm \
       i965_gen80 i965_gen90 i965_gen110 \
       isl_gen80  isl_gen90  isl_gen110  isl_gen120  isl_gen125

LIBS += expat zlib

include $(REP_DIR)/lib/mk/mesa-common.inc

CC_CXX_WARN_STRICT =

CC_OPT   += -DGALLIUM_I965
# We rename 'ioctl' calls to 'genode_ioctl' calls (drm lib)
CC_C_OPT += -Dioctl=genode_ioctl

INC_DIR += $(MESA_GEN_DIR)/src/compiler \
           $(MESA_GEN_DIR)/src/compiler/nir \
           $(MESA_GEN_DIR)/src/intel

INC_DIR += $(MESA_SRC_DIR)/src/compiler/nir \
           $(MESA_SRC_DIR)/src/intel \
           $(MESA_SRC_DIR)/src/mapi \
           $(MESA_SRC_DIR)/src/mesa \
           $(MESA_SRC_DIR)/src/mesa/main \
           $(MESA_SRC_DIR)/src/mesa/drivers/dri/i965 \
           $(MESA_SRC_DIR)/src/mesa/drivers/dri/common

FILTER_OUT_GENX = genX_pipe_control.c genX_blorp_exec.c genX_state_upload.c
SRC_C += $(addprefix mesa/drivers/dri/i965/, $(filter-out $(FILTER_OUT_GENX), $(notdir $(wildcard $(MESA_SRC_DIR)/src/mesa/drivers/dri/i965/*.c))))

# rename get_time because it is also defined in iris
CC_OPT_mesa/drivers/dri/i965/intel_screen = -Dget_time=i965_get_time

SRC_C += intel/perf/gen_perf_metrics.c

SRC_CC += mesa/drivers/dri/i965/brw_link.cpp \
          mesa/drivers/dri/i965/brw_nir_uniforms.cpp

SRC_C  += mesa/swrast_setup/ss_context.c \
          mesa/swrast_setup/ss_triangle.c

SRC_CC += i965/unsupported.cc

vpath %.c   $(MESA_SRC_DIR)/src
vpath %.c   $(MESA_GEN_DIR)/src
vpath %.c   $(REP_DIR)/src/lib/mesa
vpath %.cpp $(MESA_SRC_DIR)/src
vpath %.cc  $(REP_DIR)/src/lib/mesa
