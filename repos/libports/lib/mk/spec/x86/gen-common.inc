INC_DIR += $(MESA_GEN_DIR)/src/intel \
           $(MESA_SRC_DIR)/src/intel

SRC_C += $(addprefix intel/blorp/, $(notdir $(wildcard $(MESA_SRC_DIR)/src/intel/blorp/*.c)))
SRC_C += $(addprefix intel/perf/, $(notdir $(wildcard $(MESA_SRC_DIR)/src/intel/perf/*.c)))
SRC_C += $(addprefix intel/common/, $(notdir $(wildcard $(MESA_SRC_DIR)/src/intel/common/*.c)))
SRC_C += $(addprefix mesa/swrast/, $(notdir $(wildcard $(MESA_SRC_DIR)/src/mesa/swrast/*.c)))
SRC_C += $(addprefix mesa/tnl/, $(notdir $(wildcard $(MESA_SRC_DIR)/src/mesa/tnl/*.c)))

SRC_C += intel/isl/isl.c \
         intel/isl/isl_aux_info.c \
         intel/isl/isl_gen7.c \
         intel/isl/isl_gen8.c \
         intel/isl/isl_gen9.c \
         intel/isl/isl_gen12.c \
         intel/isl/isl_drm.c \
         intel/isl/isl_format.c \
         intel/isl/isl_format_layout.c \
         intel/isl/isl_storage_image.c \
         intel/isl/isl_tiled_memcpy_normal.c

SRC_C  += intel/compiler/brw_clip_line.c \
          intel/compiler/brw_clip_point.c \
          intel/compiler/brw_clip_tri.c \
          intel/compiler/brw_clip_unfilled.c \
          intel/compiler/brw_clip_util.c \
          intel/compiler/brw_compile_clip.c \
          intel/compiler/brw_compiler.c \
          intel/compiler/brw_compile_sf.c \
          intel/compiler/brw_debug_recompile.c \
          intel/compiler/brw_disasm.c \
          intel/compiler/brw_disasm_info.c \
          intel/compiler/brw_eu_compact.c \
          intel/compiler/brw_eu_emit.c \
          intel/compiler/brw_eu_util.c \
          intel/compiler/brw_eu_validate.c \
          intel/compiler/brw_interpolation_map.c \
          intel/compiler/brw_nir_analyze_boolean_resolves.c \
          intel/compiler/brw_nir_analyze_ubo_ranges.c \
          intel/compiler/brw_nir_attribute_workarounds.c \
          intel/compiler/brw_nir.c \
          intel/compiler/brw_nir_clamp_image_1d_2d_array_sizes.c \
          intel/compiler/brw_nir_lower_alpha_to_coverage.c \
          intel/compiler/brw_nir_lower_conversions.c \
          intel/compiler/brw_nir_lower_cs_intrinsics.c \
          intel/compiler/brw_nir_lower_image_load_store.c \
          intel/compiler/brw_nir_lower_intersection_shader.c \
          intel/compiler/brw_nir_lower_mem_access_bit_sizes.c \
          intel/compiler/brw_nir_lower_rt_intrinsics.c \
          intel/compiler/brw_nir_lower_scoped_barriers.c \
          intel/compiler/brw_nir_lower_shader_calls.c \
          intel/compiler/brw_nir_opt_peephole_ffma.c \
          intel/compiler/brw_nir_rt.c \
          intel/compiler/brw_nir_tcs_workarounds.c \
          intel/compiler/brw_packed_float.c \
          intel/compiler/brw_reg_type.c \
          intel/compiler/brw_vue_map.c

SRC_CC += intel/compiler/brw_cfg.cpp \
          intel/compiler/brw_dead_control_flow.cpp \
          intel/compiler/brw_eu.cpp \
          intel/compiler/brw_fs_bank_conflicts.cpp \
          intel/compiler/brw_fs_cmod_propagation.cpp \
          intel/compiler/brw_fs_combine_constants.cpp \
          intel/compiler/brw_fs_copy_propagation.cpp \
          intel/compiler/brw_fs.cpp \
          intel/compiler/brw_fs_cse.cpp \
          intel/compiler/brw_fs_dead_code_eliminate.cpp \
          intel/compiler/brw_fs_generator.cpp \
          intel/compiler/brw_fs_live_variables.cpp \
          intel/compiler/brw_fs_lower_pack.cpp \
          intel/compiler/brw_fs_lower_regioning.cpp \
          intel/compiler/brw_fs_nir.cpp \
          intel/compiler/brw_fs_reg_allocate.cpp \
          intel/compiler/brw_fs_register_coalesce.cpp \
          intel/compiler/brw_fs_saturate_propagation.cpp \
          intel/compiler/brw_fs_scoreboard.cpp \
          intel/compiler/brw_fs_sel_peephole.cpp \
          intel/compiler/brw_fs_validate.cpp \
          intel/compiler/brw_fs_visitor.cpp \
          intel/compiler/brw_ir_performance.cpp \
          intel/compiler/brw_predicated_break.cpp \
          intel/compiler/brw_schedule_instructions.cpp \
          intel/compiler/brw_shader.cpp \
          intel/compiler/brw_vec4_cmod_propagation.cpp \
          intel/compiler/brw_vec4_copy_propagation.cpp \
          intel/compiler/brw_vec4.cpp \
          intel/compiler/brw_vec4_cse.cpp \
          intel/compiler/brw_vec4_dead_code_eliminate.cpp \
          intel/compiler/brw_vec4_generator.cpp \
          intel/compiler/brw_vec4_gs_nir.cpp \
          intel/compiler/brw_vec4_gs_visitor.cpp \
          intel/compiler/brw_vec4_live_variables.cpp \
          intel/compiler/brw_vec4_nir.cpp \
          intel/compiler/brw_vec4_reg_allocate.cpp \
          intel/compiler/brw_vec4_surface_builder.cpp \
          intel/compiler/brw_vec4_tcs.cpp \
          intel/compiler/brw_vec4_tes.cpp \
          intel/compiler/brw_vec4_visitor.cpp \
          intel/compiler/brw_vec4_vs_visitor.cpp \
          intel/compiler/brw_wm_iz.cpp \
          intel/compiler/gen6_gs_visitor.cpp

SRC_C  += mesa/main/texformat.c

SRC_C += intel/dev/gen_debug.c \
         intel/dev/gen_device_info.c

CC_C_OPT += -Dioctl=genode_ioctl
