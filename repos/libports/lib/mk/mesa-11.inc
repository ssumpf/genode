SHARED_LIB = yes
LIBS       = libc stdcxx

MAIN_ES_FILES = \
	main/es1_conversion.c

MAIN_FILES = \
	main/accum.c \
	main/api_arrayelt.c \
	main/api_exec.c \
	main/api_loopback.c \
	main/api_validate.c \
	main/arbprogram.c \
	main/arrayobj.c \
	main/atifragshader.c \
	main/attrib.c \
	main/blend.c \
	main/blit.c \
	main/bufferobj.c \
	main/buffers.c \
	main/clear.c \
	main/clip.c \
	main/colortab.c \
	main/compute.c \
	main/condrender.c \
	main/context.c \
	main/convolve.c \
	main/copyimage.c \
	main/cpuinfo.c \
	main/debug.c \
	main/debug_output.c \
	main/depth.c \
	main/dlist.c \
	main/drawpix.c \
	main/drawtex.c \
	main/enable.c \
	main/enums.c \
	main/errors.c \
	main/eval.c \
	main/execmem.c \
	main/extensions.c \
	main/fbobject.c \
	main/feedback.c \
	main/ffvertex_prog.c \
	main/fog.c \
	main/format_pack.c \
	main/format_unpack.c \
	main/formatquery.c \
	main/formats.c \
	main/format_utils.c \
	main/framebuffer.c \
	main/get.c \
	main/genmipmap.c \
	main/getstring.c \
	main/glformats.c \
	main/hash.c \
	main/hint.c \
	main/histogram.c \
	main/image.c \
	main/imports.c \
	main/light.c \
	main/lines.c \
	main/matrix.c \
	main/mipmap.c \
	main/mm.c \
	main/multisample.c \
	main/objectlabel.c \
	main/objectpurge.c \
	main/pack.c \
	main/pbo.c \
	main/performance_monitor.c \
	main/pipelineobj.c \
	main/pixel.c \
	main/pixelstore.c \
	main/pixeltransfer.c \
	main/points.c \
	main/polygon.c \
	main/program_resource.c \
	main/querymatrix.c \
	main/queryobj.c \
	main/rastpos.c \
	main/readpix.c \
	main/remap.c \
	main/renderbuffer.c \
	main/samplerobj.c \
	main/scissor.c \
	main/shaderapi.c \
	main/shaderimage.c \
	main/shaderobj.c \
	main/shared.c \
	main/state.c \
	main/stencil.c \
	main/syncobj.c \
	main/texcompress.c \
	main/texcompress_bptc.c \
	main/texcompress_cpal.c \
	main/texcompress_etc.c \
	main/texcompress_fxt1.c \
	main/texcompress_rgtc.c \
	main/texcompress_s3tc.c \
	main/texenv.c \
	main/texformat.c \
	main/texgen.c \
	main/texgetimage.c \
	main/teximage.c \
	main/texobj.c \
	main/texparam.c \
	main/texstate.c \
	main/texstorage.c \
	main/texstore.c \
	main/textureview.c \
	main/texturebarrier.c \
	main/transformfeedback.c \
	main/uniforms.c \
	main/varray.c \
	main/vdpau.c \
	main/version.c \
	main/viewport.c \
	main/vtxfmt.c

MAIN_FILES_CC = \
	main/ff_fragment_shader.cpp \
	main/shader_query.cpp \
	main/uniform_query.cpp \

MATH_FILES = \
	math/m_debug_clip.c \
	math/m_debug_norm.c \
	math/m_debug_xform.c \
	math/m_eval.c \
	math/m_matrix.c \
	math/m_translate.c \
	math/m_vector.c \

MATH_XFORM_FILES = \
	math/m_xform.c \

VBO_FILES = \
	vbo/vbo_context.c \
	vbo/vbo_exec_api.c \
	vbo/vbo_exec_array.c \
	vbo/vbo_exec.c \
	vbo/vbo_exec_draw.c \
	vbo/vbo_exec_eval.c \
	vbo/vbo_minmax_index.c \
	vbo/vbo_noop.c \
	vbo/vbo_primitive_restart.c \
	vbo/vbo_rebase.c \
	vbo/vbo_save_api.c \
	vbo/vbo_save.c \
	vbo/vbo_save_draw.c \
	vbo/vbo_save_loopback.c \
	vbo/vbo_split.c \
	vbo/vbo_split_copy.c \
	vbo/vbo_split_inplace.c

TNL_FILES = \
	tnl/t_context.c \
	tnl/t_draw.c \
	tnl/t_pipeline.c \
	tnl/t_vb_fog.c \
	tnl/t_vb_light.c \
	tnl/t_vb_normals.c \
	tnl/t_vb_points.c \
	tnl/t_vb_program.c \
	tnl/t_vb_render.c \
	tnl/t_vb_texgen.c \
	tnl/t_vb_texmat.c \
	tnl/t_vb_vertex.c \
	tnl/t_vertex.c \
	tnl/t_vertex_generic.c \
	tnl/t_vertex_sse.c \
	tnl/t_vp_build.c \

SWRAST_FILES = \
	swrast/s_aaline.c \
	swrast/s_aatriangle.c \
	swrast/s_alpha.c \
	swrast/s_atifragshader.c \
	swrast/s_bitmap.c \
	swrast/s_blend.c \
	swrast/s_blit.c \
	swrast/s_clear.c \
	swrast/s_context.c \
	swrast/s_copypix.c \
	swrast/s_depth.c \
	swrast/s_drawpix.c \
	swrast/s_feedback.c \
	swrast/s_fog.c \
	swrast/s_fragprog.c \
	swrast/s_lines.c \
	swrast/s_logic.c \
	swrast/s_masking.c \
	swrast/s_points.c \
	swrast/s_renderbuffer.c \
	swrast/s_span.c \
	swrast/s_stencil.c \
	swrast/s_texcombine.c \
	swrast/s_texfetch.c \
	swrast/s_texfilter.c \
	swrast/s_texrender.c \
	swrast/s_texture.c \
	swrast/s_triangle.c \
	swrast/s_zoom.c \

SWRAST_SETUP_FILES = \
	swrast_setup/ss_context.c \
	swrast_setup/ss_triangle.c \

COMMON_DRIVER_FILES = \
	drivers/common/driverfuncs.c \
	drivers/common/meta_blit.c \
	drivers/common/meta_copy_image.c \
	drivers/common/meta_generate_mipmap.c \
	drivers/common/meta_tex_subimage.c \
	drivers/common/meta.c \

ASM_C_FILES += \
	x86/common_x86.c \
	x86/x86_xform.c \
	x86/sse.c \
	x86/rtasm/x86sse.c \
	sparc/sparc.c \

SRC_C = \
	$(MAIN_ES_FILES) \
	$(MAIN_FILES) \
	$(MATH_FILES) \
	$(MATH_XFORM_FILES) \
	$(VBO_FILES) \
	$(TNL_FILES) \
	$(SWRAST_FILES) \
	$(SWRAST_SETUP_FILES) \
	$(COMMON_DRIVER_FILES) \
	$(ASM_C_FILES)

SRC_CC = $(MAIN_FILES_CC)

MESA_PORT_DIR := $(call select_from_ports,mesa-11)/src/lib/mesa
MESA_SRC_DIR  := $(MESA_PORT_DIR)/src/mesa
LIB_DIR        = $(REP_DIR)/src/lib/mesa

INC_DIR += $(MESA_SRC_DIR) \
           $(MESA_SRC_DIR)/main \
           $(MESA_SRC_DIR)/x86 \
           $(MESA_PORT_DIR) \
           $(MESA_PORT_DIR)/include \
           $(MESA_PORT_DIR)/src \
           $(MESA_PORT_DIR)/src/mapi \
           $(MESA_PORT_DIR)/src/gallium/auxiliary \
           $(MESA_PORT_DIR)/src/gallium/include \
           $(LIB_DIR)/include

CC_OPT = -DHAVE_PTHREAD -D_XOPEN_SOURCE=600 -DPACKAGE_VERSION=\"11.2.2\" \
         -DPACKAGE_BUGREPORT=\"https://bugs.freedesktop.org/enter_bug.cgi\?product=Mesa\"

CC_C_OPT += -std=c99

CC_CXX_OPT += -DINT64_MAX=0x7fffffffffffffffLL

vpath %.c    $(MESA_SRC_DIR)
vpath %.cpp  $(MESA_SRC_DIR)

# vi: set ft=make :
