LIBS = libc libdrm \
       iris_gen80 iris_gen90 iris_gen110 iris_gen120 iris_gen125 \
       isl_gen80  isl_gen90  isl_gen110  isl_gen120  isl_gen125

LIBS += expat zlib

include $(REP_DIR)/lib/mk/mesa-common.inc

CC_CXX_WARN_STRICT =

CC_OPT   += -DGALLIUM_IRIS
# We rename 'ioctl' calls to 'genode_ioctl' calls (drm lib)
CC_C_OPT += -Dioctl=genode_ioctl
CC_C_OPT += -DUSE_SSE41 -msse4

INC_DIR += $(MESA_GEN_DIR)/src/compiler \
           $(MESA_GEN_DIR)/src/compiler/nir \
           $(MESA_GEN_DIR)/src/intel

INC_DIR += $(MESA_SRC_DIR)/src/compiler/nir \
           $(MESA_SRC_DIR)/src/gallium/auxiliary \
           $(MESA_SRC_DIR)/src/intel \
           $(MESA_SRC_DIR)/src/mapi \
           $(MESA_SRC_DIR)/src/mesa/main \
           $(MESA_SRC_DIR)/src/mesa

SRC_C = gallium/drivers/iris/iris_batch.c \
        gallium/drivers/iris/iris_binder.c \
        gallium/drivers/iris/iris_blit.c \
        gallium/drivers/iris/iris_border_color.c \
        gallium/drivers/iris/iris_bufmgr.c \
        gallium/drivers/iris/iris_clear.c \
        gallium/drivers/iris/iris_context.c \
        gallium/drivers/iris/iris_disk_cache.c \
        gallium/drivers/iris/iris_draw.c \
        gallium/drivers/iris/iris_fence.c \
        gallium/drivers/iris/iris_fine_fence.c \
        gallium/drivers/iris/iris_formats.c \
        gallium/drivers/iris/iris_monitor.c \
        gallium/drivers/iris/iris_perf.c \
        gallium/drivers/iris/iris_performance_query.c \
        gallium/drivers/iris/iris_pipe_control.c \
        gallium/drivers/iris/iris_program.c \
        gallium/drivers/iris/iris_program_cache.c \
        gallium/drivers/iris/iris_resolve.c \
        gallium/drivers/iris/iris_resource.c \
        gallium/drivers/iris/iris_screen.c \
        gallium/winsys/iris/drm/iris_drm_winsys.c

# rename get_time because it is also defined in i965
CC_OPT_gallium/drivers/iris/iris_context = -Dget_time=iris_get_time


SRC_C += intel/isl/isl_tiled_memcpy_sse41.c

vpath %.c   $(MESA_GEN_DIR)/src

vpath %.c   $(MESA_SRC_DIR)/src
vpath %.cpp $(MESA_SRC_DIR)/src
