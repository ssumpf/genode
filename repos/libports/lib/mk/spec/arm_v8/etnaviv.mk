LIBS = libc libdrm

include $(REP_DIR)/lib/mk/mesa-common.inc

CC_OPT += -DHAVE_LIBDRM

INC_DIR += $(MESA_SRC_DIR)/src/compiler/nir \
           $(MESA_SRC_DIR)/src/etnaviv \
           $(MESA_SRC_DIR)/src/gallium/auxiliary \
           $(MESA_SRC_DIR)/src/gallium/drivers \
           $(MESA_SRC_DIR)/src/util \
           $(MESA_GEN_DIR)/src/compiler/nir \
           $(MESA_PORT_DIR)/include/drm-uapi

REP_INC_DIR += include/drm-uapi

SRC_C = src/etnaviv/drm/etnaviv_bo.c \
        src/etnaviv/drm/etnaviv_bo_cache.c \
        src/etnaviv/drm/etnaviv_cmd_stream.c \
        src/etnaviv/drm/etnaviv_device.c \
        src/etnaviv/drm/etnaviv_gpu.c \
        src/etnaviv/drm/etnaviv_perfmon.c \
        src/etnaviv/drm/etnaviv_pipe.c \
        src/gallium/drivers/etnaviv/etnaviv_asm.c \
        src/gallium/drivers/etnaviv/etnaviv_blend.c \
        src/gallium/drivers/etnaviv/etnaviv_blt.c \
        src/gallium/drivers/etnaviv/etnaviv_clear_blit.c \
        src/gallium/drivers/etnaviv/etnaviv_compiler.c \
        src/gallium/drivers/etnaviv/etnaviv_compiler_nir.c \
        src/gallium/drivers/etnaviv/etnaviv_compiler_nir_emit.c \
        src/gallium/drivers/etnaviv/etnaviv_compiler_nir_liveness.c \
        src/gallium/drivers/etnaviv/etnaviv_compiler_nir_ra.c \
        src/gallium/drivers/etnaviv/etnaviv_context.c \
        src/gallium/drivers/etnaviv/etnaviv_disasm.c \
        src/gallium/drivers/etnaviv/etnaviv_disk_cache.c \
        src/gallium/drivers/etnaviv/etnaviv_emit.c \
        src/gallium/drivers/etnaviv/etnaviv_etc2.c \
        src/gallium/drivers/etnaviv/etnaviv_fence.c \
        src/gallium/drivers/etnaviv/etnaviv_format.c \
        src/gallium/drivers/etnaviv/etnaviv_nir.c \
        src/gallium/drivers/etnaviv/etnaviv_perfmon.c \
        src/gallium/drivers/etnaviv/etnaviv_query.c \
        src/gallium/drivers/etnaviv/etnaviv_query_acc.c \
        src/gallium/drivers/etnaviv/etnaviv_query_acc_occlusion.c \
        src/gallium/drivers/etnaviv/etnaviv_query_acc_perfmon.c \
        src/gallium/drivers/etnaviv/etnaviv_query_sw.c \
        src/gallium/drivers/etnaviv/etnaviv_rasterizer.c \
        src/gallium/drivers/etnaviv/etnaviv_resource.c \
        src/gallium/drivers/etnaviv/etnaviv_rs.c \
        src/gallium/drivers/etnaviv/etnaviv_screen.c \
        src/gallium/drivers/etnaviv/etnaviv_shader.c \
        src/gallium/drivers/etnaviv/etnaviv_state.c \
        src/gallium/drivers/etnaviv/etnaviv_surface.c \
        src/gallium/drivers/etnaviv/etnaviv_texture.c \
        src/gallium/drivers/etnaviv/etnaviv_texture_desc.c \
        src/gallium/drivers/etnaviv/etnaviv_texture_state.c \
        src/gallium/drivers/etnaviv/etnaviv_tiling.c \
        src/gallium/drivers/etnaviv/etnaviv_transfer.c \
        src/gallium/drivers/etnaviv/etnaviv_uniforms.c \
        src/gallium/drivers/etnaviv/etnaviv_zsa.c \
        src/gallium/winsys/etnaviv/drm/etnaviv_drm_winsys.c \

vpath %.c $(MESA_SRC_DIR)/src
