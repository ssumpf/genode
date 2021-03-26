SHARED_LIB = yes
LIBS       = libc stdcxx zlib expat glapi-21 softpipe mesa_api

include $(REP_DIR)/lib/mk/mesa-common-21.inc

SRC_CC += mesa.cc

INC_DIR += $(MESA_GEN_DIR)/src/compiler \
           $(MESA_GEN_DIR)/src/compiler/glsl \
           $(MESA_GEN_DIR)/src/compiler/nir \
           $(MESA_GEN_DIR)/src/compiler/spirv \
           $(MESA_GEN_DIR)/src/mapi \
           $(MESA_GEN_DIR)/src/mesa \
           $(MESA_GEN_DIR)/src/mesa/main \
           $(MESA_GEN_DIR)/src/util/format \
           $(MESA_SRC_DIR)/src \
           $(MESA_SRC_DIR)/src/compiler \
           $(MESA_SRC_DIR)/src/compiler/glsl \
           $(MESA_SRC_DIR)/src/compiler/glsl/glcpp \
           $(MESA_SRC_DIR)/src/compiler/nir \
           $(MESA_SRC_DIR)/src/compiler/spirv \
           $(MESA_SRC_DIR)/src/gallium/auxiliary \
           $(MESA_SRC_DIR)/src/gallium/frontends/dri \
           $(MESA_SRC_DIR)/src/gallium/winsys \
           $(MESA_SRC_DIR)/src/mapi \
           $(MESA_SRC_DIR)/src/mesa \
           $(MESA_SRC_DIR)/src/mesa/drivers/dri/common \
           $(MESA_SRC_DIR)/src/mesa/main \
           $(MESA_SRC_DIR)/src/util \
           $(MESA_SRC_DIR)/src/util/format

# C++ generated

SRC_CC += compiler/glsl/glsl_lexer.cpp \
          compiler/glsl/glsl_parser.cpp

# C++
SRC_CC += compiler/glsl/ast_array_index.cpp \
          compiler/glsl/ast_expr.cpp \
          compiler/glsl/ast_function.cpp \
          compiler/glsl/ast_to_hir.cpp \
          compiler/glsl/ast_type.cpp \
          compiler/glsl/builtin_functions.cpp \
          compiler/glsl/builtin_types.cpp \
          compiler/glsl/builtin_variables.cpp \
          compiler/glsl/generate_ir.cpp \
          compiler/glsl/glsl_parser_extras.cpp \
          compiler/glsl/glsl_symbol_table.cpp \
          compiler/glsl/glsl_to_nir.cpp \
          compiler/glsl/hir_field_selection.cpp \
          compiler/glsl/ir_array_refcount.cpp \
          compiler/glsl/ir_basic_block.cpp \
          compiler/glsl/ir_builder.cpp \
          compiler/glsl/ir_clone.cpp \
          compiler/glsl/ir_constant_expression.cpp \
          compiler/glsl/ir.cpp \
          compiler/glsl/ir_equals.cpp \
          compiler/glsl/ir_expression_flattening.cpp \
          compiler/glsl/ir_function_can_inline.cpp \
          compiler/glsl/ir_function.cpp \
          compiler/glsl/ir_function_detect_recursion.cpp \
          compiler/glsl/ir_hierarchical_visitor.cpp \
          compiler/glsl/ir_hv_accept.cpp \
          compiler/glsl/ir_print_visitor.cpp \
          compiler/glsl/ir_rvalue_visitor.cpp \
          compiler/glsl/ir_set_program_inouts.cpp \
          compiler/glsl/ir_validate.cpp \
          compiler/glsl/ir_variable_refcount.cpp \
          compiler/glsl/link_atomics.cpp \
          compiler/glsl/linker.cpp \
          compiler/glsl/linker_util.cpp \
          compiler/glsl/link_functions.cpp \
          compiler/glsl/link_interface_blocks.cpp \
          compiler/glsl/link_uniform_block_active_visitor.cpp \
          compiler/glsl/link_uniform_blocks.cpp \
          compiler/glsl/link_uniform_initializers.cpp \
          compiler/glsl/link_uniforms.cpp \
          compiler/glsl/link_varyings.cpp \
          compiler/glsl/loop_analysis.cpp \
          compiler/glsl/loop_unroll.cpp \
          compiler/glsl/lower_blend_equation_advanced.cpp \
          compiler/glsl/lower_buffer_access.cpp \
          compiler/glsl/lower_builtins.cpp \
          compiler/glsl/lower_const_arrays_to_uniforms.cpp \
          compiler/glsl/lower_cs_derived.cpp \
          compiler/glsl/lower_discard.cpp \
          compiler/glsl/lower_discard_flow.cpp \
          compiler/glsl/lower_distance.cpp \
          compiler/glsl/lower_if_to_cond_assign.cpp \
          compiler/glsl/lower_instructions.cpp \
          compiler/glsl/lower_int64.cpp \
          compiler/glsl/lower_jumps.cpp \
          compiler/glsl/lower_mat_op_to_vec.cpp \
          compiler/glsl/lower_named_interface_blocks.cpp \
          compiler/glsl/lower_offset_array.cpp \
          compiler/glsl/lower_output_reads.cpp \
          compiler/glsl/lower_packed_varyings.cpp \
          compiler/glsl/lower_packing_builtins.cpp \
          compiler/glsl/lower_precision.cpp \
          compiler/glsl/lower_shared_reference.cpp \
          compiler/glsl/lower_subroutine.cpp \
          compiler/glsl/lower_tess_level.cpp \
          compiler/glsl/lower_ubo_reference.cpp \
          compiler/glsl/lower_variable_index_to_cond_assign.cpp \
          compiler/glsl/lower_vec_index_to_cond_assign.cpp \
          compiler/glsl/lower_vec_index_to_swizzle.cpp \
          compiler/glsl/lower_vector.cpp \
          compiler/glsl/lower_vector_derefs.cpp \
          compiler/glsl/lower_vector_insert.cpp \
          compiler/glsl/lower_vertex_id.cpp \
          compiler/glsl/lower_xfb_varying.cpp \
          compiler/glsl/opt_algebraic.cpp \
          compiler/glsl/opt_array_splitting.cpp \
          compiler/glsl/opt_conditional_discard.cpp \
          compiler/glsl/opt_constant_folding.cpp \
          compiler/glsl/opt_constant_propagation.cpp \
          compiler/glsl/opt_constant_variable.cpp \
          compiler/glsl/opt_copy_propagation_elements.cpp \
          compiler/glsl/opt_dead_builtin_variables.cpp \
          compiler/glsl/opt_dead_builtin_varyings.cpp \
          compiler/glsl/opt_dead_code.cpp \
          compiler/glsl/opt_dead_code_local.cpp \
          compiler/glsl/opt_dead_functions.cpp \
          compiler/glsl/opt_flatten_nested_if_blocks.cpp \
          compiler/glsl/opt_flip_matrices.cpp \
          compiler/glsl/opt_function_inlining.cpp \
          compiler/glsl/opt_if_simplification.cpp \
          compiler/glsl/opt_minmax.cpp \
          compiler/glsl/opt_rebalance_tree.cpp \
          compiler/glsl/opt_redundant_jumps.cpp \
          compiler/glsl/opt_structure_splitting.cpp \
          compiler/glsl/opt_swizzle.cpp \
          compiler/glsl/opt_tree_grafting.cpp \
          compiler/glsl/opt_vectorize.cpp \
          compiler/glsl/propagate_invariance.cpp \
          compiler/glsl/serialize.cpp \
          compiler/glsl/shader_cache.cpp \
          compiler/glsl/string_to_uint_map.cpp \
          compiler/glsl_types.cpp \
          compiler/nir_types.cpp \
          gallium/auxiliary/tessellator/p_tessellator.cpp \
          gallium/auxiliary/tessellator/tessellator.cpp \
          mesa/main/ff_fragment_shader.cpp \
          mesa/main/shader_query.cpp \
          mesa/main/texcompress_astc.cpp \
          mesa/main/uniform_query.cpp \
          mesa/program/ir_to_mesa.cpp \
          mesa/state_tracker/st_glsl_to_ir.cpp \
          mesa/state_tracker/st_glsl_to_nir.cpp \
          mesa/state_tracker/st_glsl_to_tgsi_array_merge.cpp \
          mesa/state_tracker/st_glsl_to_tgsi.cpp \
          mesa/state_tracker/st_glsl_to_tgsi_private.cpp \
          mesa/state_tracker/st_glsl_to_tgsi_temprename.cpp \
          util/u_printf.cpp

# C generated
SRC_C += \
         compiler/glsl/glcpp/glcpp-parse.c \
         compiler/glsl/glcpp/glcpp-lex.c \
         compiler/nir/nir_constant_expressions.c \
         compiler/nir/nir_intrinsics.c \
         compiler/nir/nir_opt_algebraic.c \
         compiler/nir/nir_opcodes.c \
         compiler/spirv/spirv_info.c \
         compiler/spirv/vtn_gather_types.c \
         mapi/glapi/gen/api_exec.c \
         mapi/glapi/gen/enums.c \
         mapi/glapi/gen/marshal_generated0.c \
         mapi/glapi/gen/marshal_generated1.c \
         mapi/glapi/gen/marshal_generated2.c \
         mapi/glapi/gen/marshal_generated3.c \
         mapi/glapi/gen/marshal_generated4.c \
         mapi/glapi/gen/marshal_generated5.c \
         mapi/glapi/gen/marshal_generated6.c \
         mapi/glapi/gen/marshal_generated7.c \
         mesa/format_fallback.c \
         mesa/format_pack.c \
         mesa/format_unpack.c \
         mesa/program/lex.yy.c \
         mesa/program/program_parse.tab.c \
         util/format_srgb.c \
         util/format/u_format_table.c

#SRC_C +=
#         mapi/glapi/gen/marshal_generated0.c \
#         mapi/glapi/gen/marshal_generated1.c \
#         mapi/glapi/gen/marshal_generated2.c \
#         mapi/glapi/gen/marshal_generated3.c \
#         mapi/glapi/gen/marshal_generated4.c \
#         mapi/glapi/gen/marshal_generated5.c \
#         mapi/glapi/gen/marshal_generated6.c \
#         mapi/glapi/gen/marshal_generated7.c \

# C
SRC_C += compiler/glsl/glcpp/pp.c \
         compiler/glsl/gl_nir_link_atomics.c \
         compiler/glsl/gl_nir_linker.c \
         compiler/glsl/gl_nir_link_uniform_blocks.c \
         compiler/glsl/gl_nir_link_uniform_initializers.c \
         compiler/glsl/gl_nir_link_uniforms.c \
         compiler/glsl/gl_nir_link_xfb.c \
         compiler/glsl/gl_nir_lower_atomics.c \
         compiler/glsl/gl_nir_lower_buffers.c \
         compiler/glsl/gl_nir_lower_images.c \
         compiler/glsl/gl_nir_lower_samplers_as_deref.c \
         compiler/glsl/gl_nir_lower_samplers.c \
         compiler/nir/nir_builtin_builder.c \
         compiler/nir/nir.c \
         compiler/nir/nir_clone.c \
         compiler/nir/nir_control_flow.c \
         compiler/nir/nir_deref.c \
         compiler/nir/nir_divergence_analysis.c \
         compiler/nir/nir_dominance.c \
         compiler/nir/nir_from_ssa.c \
         compiler/nir/nir_gather_info.c \
         compiler/nir/nir_gather_ssa_types.c \
         compiler/nir/nir_gather_xfb_info.c \
         compiler/nir/nir_inline_functions.c \
         compiler/nir/nir_instr_set.c \
         compiler/nir/nir_linking_helpers.c \
         compiler/nir/nir_liveness.c \
         compiler/nir/nir_loop_analyze.c \
         compiler/nir/nir_lower_alpha_test.c \
         compiler/nir/nir_lower_alu.c \
         compiler/nir/nir_lower_alu_to_scalar.c \
         compiler/nir/nir_lower_atomics_to_ssbo.c \
         compiler/nir/nir_lower_bitmap.c \
         compiler/nir/nir_lower_bool_to_float.c \
         compiler/nir/nir_lower_bool_to_int32.c \
         compiler/nir/nir_lower_clamp_color_outputs.c \
         compiler/nir/nir_lower_clip.c \
         compiler/nir/nir_lower_clip_cull_distance_arrays.c \
         compiler/nir/nir_lower_clip_disable.c \
         compiler/nir/nir_lower_double_ops.c \
         compiler/nir/nir_lower_drawpixels.c \
         compiler/nir/nir_lower_flatshade.c \
         compiler/nir/nir_lower_flrp.c \
         compiler/nir/nir_lower_frexp.c \
         compiler/nir/nir_lower_global_vars_to_local.c \
         compiler/nir/nir_lower_goto_ifs.c \
         compiler/nir/nir_lower_indirect_derefs.c \
         compiler/nir/nir_lower_int64.c \
         compiler/nir/nir_lower_int_to_float.c \
         compiler/nir/nir_lower_io_arrays_to_elements.c \
         compiler/nir/nir_lower_io.c \
         compiler/nir/nir_lower_io_to_scalar.c \
         compiler/nir/nir_lower_io_to_temporaries.c \
         compiler/nir/nir_lower_io_to_vector.c \
         compiler/nir/nir_lower_load_const_to_scalar.c \
         compiler/nir/nir_lower_locals_to_regs.c \
         compiler/nir/nir_lower_packing.c \
         compiler/nir/nir_lower_passthrough_edgeflags.c \
         compiler/nir/nir_lower_patch_vertices.c \
         compiler/nir/nir_lower_phis_to_scalar.c \
         compiler/nir/nir_lower_pntc_ytransform.c \
         compiler/nir/nir_lower_point_size_mov.c \
         compiler/nir/nir_lower_regs_to_ssa.c \
         compiler/nir/nir_lower_returns.c \
         compiler/nir/nir_lower_samplers.c \
         compiler/nir/nir_lower_system_values.c \
         compiler/nir/nir_lower_tex.c \
         compiler/nir/nir_lower_to_source_mods.c \
         compiler/nir/nir_lower_two_sided_color.c \
         compiler/nir/nir_lower_ubo_vec4.c \
         compiler/nir/nir_lower_uniforms_to_ubo.c \
         compiler/nir/nir_lower_var_copies.c \
         compiler/nir/nir_lower_variable_initializers.c \
         compiler/nir/nir_lower_vars_to_ssa.c \
         compiler/nir/nir_lower_vec_to_movs.c \
         compiler/nir/nir_lower_wpos_ytransform.c \
         compiler/nir/nir_metadata.c \
         compiler/nir/nir_opt_access.c \
         compiler/nir/nir_opt_combine_stores.c \
         compiler/nir/nir_opt_conditional_discard.c \
         compiler/nir/nir_opt_constant_folding.c \
         compiler/nir/nir_opt_copy_propagate.c \
         compiler/nir/nir_opt_copy_prop_vars.c \
         compiler/nir/nir_opt_cse.c \
         compiler/nir/nir_opt_dce.c \
         compiler/nir/nir_opt_dead_cf.c \
         compiler/nir/nir_opt_dead_write_vars.c \
         compiler/nir/nir_opt_find_array_copies.c \
         compiler/nir/nir_opt_gcm.c \
         compiler/nir/nir_opt_if.c \
         compiler/nir/nir_opt_intrinsics.c \
         compiler/nir/nir_opt_load_store_vectorize.c \
         compiler/nir/nir_opt_loop_unroll.c \
         compiler/nir/nir_opt_peephole_select.c \
         compiler/nir/nir_opt_remove_phis.c \
         compiler/nir/nir_opt_shrink_vectors.c \
         compiler/nir/nir_opt_trivial_continues.c \
         compiler/nir/nir_opt_undef.c \
         compiler/nir/nir_opt_vectorize.c \
         compiler/nir/nir_phi_builder.c \
         compiler/nir/nir_print.c \
         compiler/nir/nir_range_analysis.c \
         compiler/nir/nir_remove_dead_variables.c \
         compiler/nir/nir_repair_ssa.c \
         compiler/nir/nir_search.c \
         compiler/nir/nir_serialize.c \
         compiler/nir/nir_split_per_member_structs.c \
         compiler/nir/nir_split_var_copies.c \
         compiler/nir/nir_sweep.c \
         compiler/nir/nir_to_lcssa.c \
         compiler/nir/nir_validate.c \
         compiler/nir/nir_worklist.c \
         compiler/shader_enums.c \
         compiler/spirv/gl_spirv.c \
         compiler/spirv/spirv_to_nir.c \
         compiler/spirv/vtn_alu.c \
         compiler/spirv/vtn_amd.c \
         compiler/spirv/vtn_cfg.c \
         compiler/spirv/vtn_glsl450.c \
         compiler/spirv/vtn_opencl.c \
         compiler/spirv/vtn_subgroup.c \
         compiler/spirv/vtn_variables.c \
         gallium/auxiliary/cso_cache/cso_cache.c \
         gallium/auxiliary/cso_cache/cso_context.c \
         gallium/auxiliary/cso_cache/cso_hash.c \
         gallium/auxiliary/draw/draw_context.c \
         gallium/auxiliary/draw/draw_fs.c \
         gallium/auxiliary/draw/draw_gs.c \
         gallium/auxiliary/draw/draw_pipe_aaline.c \
         gallium/auxiliary/draw/draw_pipe_aapoint.c \
         gallium/auxiliary/draw/draw_pipe.c \
         gallium/auxiliary/draw/draw_pipe_clip.c \
         gallium/auxiliary/draw/draw_pipe_cull.c \
         gallium/auxiliary/draw/draw_pipe_flatshade.c \
         gallium/auxiliary/draw/draw_pipe_offset.c \
         gallium/auxiliary/draw/draw_pipe_pstipple.c \
         gallium/auxiliary/draw/draw_pipe_stipple.c \
         gallium/auxiliary/draw/draw_pipe_twoside.c \
         gallium/auxiliary/draw/draw_pipe_unfilled.c \
         gallium/auxiliary/draw/draw_pipe_user_cull.c \
         gallium/auxiliary/draw/draw_pipe_util.c \
         gallium/auxiliary/draw/draw_pipe_validate.c \
         gallium/auxiliary/draw/draw_pipe_vbuf.c \
         gallium/auxiliary/draw/draw_pipe_wide_line.c \
         gallium/auxiliary/draw/draw_pipe_wide_point.c \
         gallium/auxiliary/draw/draw_prim_assembler.c \
         gallium/auxiliary/draw/draw_pt.c \
         gallium/auxiliary/draw/draw_pt_emit.c \
         gallium/auxiliary/draw/draw_pt_fetch.c \
         gallium/auxiliary/draw/draw_pt_fetch_emit.c \
         gallium/auxiliary/draw/draw_pt_fetch_shade_emit.c \
         gallium/auxiliary/draw/draw_pt_fetch_shade_pipeline.c \
         gallium/auxiliary/draw/draw_pt_post_vs.c \
         gallium/auxiliary/draw/draw_pt_so_emit.c \
         gallium/auxiliary/draw/draw_pt_util.c \
         gallium/auxiliary/draw/draw_pt_vsplit.c \
         gallium/auxiliary/draw/draw_tess.c \
         gallium/auxiliary/draw/draw_vertex.c \
         gallium/auxiliary/draw/draw_vs.c \
         gallium/auxiliary/draw/draw_vs_exec.c \
         gallium/auxiliary/draw/draw_vs_variant.c \
         gallium/auxiliary/driver_ddebug/dd_context.c \
         gallium/auxiliary/driver_ddebug/dd_draw.c \
         gallium/auxiliary/driver_ddebug/dd_screen.c \
         gallium/auxiliary/driver_noop/noop_pipe.c \
         gallium/auxiliary/driver_noop/noop_state.c \
         gallium/auxiliary/driver_rbug/rbug_context.c \
         gallium/auxiliary/driver_rbug/rbug_core.c \
         gallium/auxiliary/driver_rbug/rbug_objects.c \
         gallium/auxiliary/driver_rbug/rbug_screen.c \
         gallium/auxiliary/driver_trace/tr_context.c \
         gallium/auxiliary/driver_trace/tr_dump.c \
         gallium/auxiliary/driver_trace/tr_dump_state.c \
         gallium/auxiliary/driver_trace/tr_screen.c \
         gallium/auxiliary/driver_trace/tr_texture.c \
         gallium/auxiliary/hud/font.c \
         gallium/auxiliary/hud/hud_context.c \
         gallium/auxiliary/hud/hud_cpu.c \
         gallium/auxiliary/hud/hud_driver_query.c \
         gallium/auxiliary/hud/hud_fps.c \
         gallium/auxiliary/nir/nir_draw_helpers.c \
         gallium/auxiliary/nir/nir_to_tgsi.c \
         gallium/auxiliary/os/os_process.c \
         gallium/auxiliary/pipe-loader/pipe_loader.c \
         gallium/auxiliary/pipe-loader/pipe_loader_sw.c \
         gallium/auxiliary/postprocess/pp_celshade.c \
         gallium/auxiliary/postprocess/pp_colors.c \
         gallium/auxiliary/postprocess/pp_init.c \
         gallium/auxiliary/postprocess/pp_mlaa.c \
         gallium/auxiliary/postprocess/pp_program.c \
         gallium/auxiliary/postprocess/pp_run.c \
         gallium/auxiliary/rbug/rbug_connection.c \
         gallium/auxiliary/rbug/rbug_context.c \
         gallium/auxiliary/rbug/rbug_core.c \
         gallium/auxiliary/rbug/rbug_demarshal.c \
         gallium/auxiliary/rbug/rbug_shader.c \
         gallium/auxiliary/rbug/rbug_texture.c \
         gallium/auxiliary/rtasm/rtasm_cpu.c \
         gallium/auxiliary/rtasm/rtasm_execmem.c \
         gallium/auxiliary/rtasm/rtasm_x86sse.c \
         gallium/auxiliary/tgsi/tgsi_build.c \
         gallium/auxiliary/tgsi/tgsi_dump.c \
         gallium/auxiliary/tgsi/tgsi_emulate.c \
         gallium/auxiliary/tgsi/tgsi_exec.c \
         gallium/auxiliary/tgsi/tgsi_from_mesa.c \
         gallium/auxiliary/tgsi/tgsi_info.c \
         gallium/auxiliary/tgsi/tgsi_iterate.c \
         gallium/auxiliary/tgsi/tgsi_parse.c \
         gallium/auxiliary/tgsi/tgsi_sanity.c \
         gallium/auxiliary/tgsi/tgsi_scan.c \
         gallium/auxiliary/tgsi/tgsi_strings.c \
         gallium/auxiliary/tgsi/tgsi_text.c \
         gallium/auxiliary/tgsi/tgsi_transform.c \
         gallium/auxiliary/tgsi/tgsi_ureg.c \
         gallium/auxiliary/tgsi/tgsi_util.c \
         gallium/auxiliary/translate/translate.c \
         gallium/auxiliary/translate/translate_cache.c \
         gallium/auxiliary/translate/translate_generic.c \
         gallium/auxiliary/translate/translate_sse.c \
         gallium/auxiliary/util/u_bitmask.c \
         gallium/auxiliary/util/u_blitter.c \
         gallium/auxiliary/util/u_dl.c \
         gallium/auxiliary/util/u_draw.c \
         gallium/auxiliary/util/u_draw_quad.c \
         gallium/auxiliary/util/u_dump_defines.c \
         gallium/auxiliary/util/u_dump_state.c \
         gallium/auxiliary/util/u_framebuffer.c \
         gallium/auxiliary/util/u_gen_mipmap.c \
         gallium/auxiliary/util/u_helpers.c \
         gallium/auxiliary/util/u_log.c \
         gallium/auxiliary/util/u_network.c \
         gallium/auxiliary/util/u_pstipple.c \
         gallium/auxiliary/util/u_sampler.c \
         gallium/auxiliary/util/u_screen.c \
         gallium/auxiliary/util/u_simple_shaders.c \
         gallium/auxiliary/util/u_surface.c \
         gallium/auxiliary/util/u_tests.c \
         gallium/auxiliary/util/u_texture.c \
         gallium/auxiliary/util/u_tile.c \
         gallium/auxiliary/util/u_transfer.c \
         gallium/auxiliary/util/u_upload_mgr.c \
         gallium/auxiliary/util/u_vbuf.c \
         gallium/frontends/dri/dri_context.c \
         gallium/frontends/dri/dri_drawable.c \
         gallium/frontends/dri/dri_helpers.c \
         gallium/frontends/dri/dri_query_renderer.c \
         gallium/frontends/dri/dri_screen.c \
         gallium/targets/dri/target.c \
         gallium/winsys/sw/dri/dri_sw_winsys.c \
         loader/loader.c \
         loader/pci_id_driver_map.c \
         mesa/drivers/dri/common/dri_util.c \
         mapi/entry.c \
         mesa/drivers/dri/common/megadriver_stub.c \
         mesa/drivers/dri/common/utils.c \
         mesa/main/accum.c \
         mesa/main/api_arrayelt.c \
         mesa/main/arbprogram.c \
         mesa/main/arrayobj.c \
         mesa/main/atifragshader.c \
         mesa/main/attrib.c \
         mesa/main/barrier.c \
         mesa/main/bbox.c \
         mesa/main/blend.c \
         mesa/main/blit.c \
         mesa/main/bufferobj.c \
         mesa/main/buffers.c \
         mesa/main/clear.c \
         mesa/main/clip.c \
         mesa/main/colortab.c \
         mesa/main/compute.c \
         mesa/main/condrender.c \
         mesa/main/conservativeraster.c \
         mesa/main/context.c \
         mesa/main/convolve.c \
         mesa/main/copyimage.c \
         mesa/main/cpuinfo.c \
         mesa/main/debug.c \
         mesa/main/debug_output.c \
         mesa/main/depth.c \
         mesa/main/dlist.c \
         mesa/main/draw.c \
         mesa/main/drawpix.c \
         mesa/main/drawtex.c \
         mesa/main/draw_validate.c \
         mesa/main/enable.c \
         mesa/main/errors.c \
         mesa/main/es1_conversion.c \
         mesa/main/eval.c \
         mesa/main/extensions.c \
         mesa/main/extensions_table.c \
         mesa/main/externalobjects.c \
         mesa/main/fbobject.c \
         mesa/main/feedback.c \
         mesa/main/ffvertex_prog.c \
         mesa/main/fog.c \
         mesa/main/formatquery.c \
         mesa/main/formats.c \
         mesa/main/format_utils.c \
         mesa/main/framebuffer.c \
         mesa/main/genmipmap.c \
         mesa/main/get.c \
         mesa/main/getstring.c \
         mesa/main/glformats.c \
         mesa/main/glspirv.c \
         mesa/main/glthread_bufferobj.c \
         mesa/main/glthread.c \
         mesa/main/glthread_draw.c \
         mesa/main/glthread_shaderobj.c \
         mesa/main/glthread_varray.c \
         mesa/main/hash.c \
         mesa/main/hint.c \
         mesa/main/histogram.c \
         mesa/main/image.c \
         mesa/main/light.c \
         mesa/main/lines.c \
         mesa/main/matrix.c \
         mesa/main/mipmap.c \
         mesa/main/multisample.c \
         mesa/main/objectlabel.c \
         mesa/main/objectpurge.c \
         mesa/main/pack.c \
         mesa/main/pbo.c \
         mesa/main/performance_monitor.c \
         mesa/main/performance_query.c \
         mesa/main/pipelineobj.c \
         mesa/main/pixel.c \
         mesa/main/pixelstore.c \
         mesa/main/pixeltransfer.c \
         mesa/main/points.c \
         mesa/main/polygon.c \
         mesa/main/program_binary.c \
         mesa/main/program_resource.c \
         mesa/main/querymatrix.c \
         mesa/main/queryobj.c \
         mesa/main/rastpos.c \
         mesa/main/readpix.c \
         mesa/main/remap.c \
         mesa/main/renderbuffer.c \
         mesa/main/robustness.c \
         mesa/main/samplerobj.c \
         mesa/main/scissor.c \
         mesa/main/shaderapi.c \
         mesa/main/shaderimage.c \
         mesa/main/shaderobj.c \
         mesa/main/shared.c \
         mesa/main/spirv_extensions.c \
         mesa/main/state.c \
         mesa/main/stencil.c \
         mesa/main/syncobj.c \
         mesa/main/texcompress_bptc.c \
         mesa/main/texcompress.c \
         mesa/main/texcompress_cpal.c \
         mesa/main/texcompress_etc.c \
         mesa/main/texcompress_fxt1.c \
         mesa/main/texcompress_rgtc.c \
         mesa/main/texcompress_s3tc.c \
         mesa/main/texenv.c \
         mesa/main/texgen.c \
         mesa/main/texgetimage.c \
         mesa/main/teximage.c \
         mesa/main/texobj.c \
         mesa/main/texparam.c \
         mesa/main/texstate.c \
         mesa/main/texstorage.c \
         mesa/main/texstore.c \
         mesa/main/texturebindless.c \
         mesa/main/textureview.c \
         mesa/main/transformfeedback.c \
         mesa/main/uniforms.c \
         mesa/main/varray.c \
         mesa/main/vdpau.c \
         mesa/main/version.c \
         mesa/main/viewport.c \
         mesa/main/vtxfmt.c \
         mesa/math/m_eval.c \
         mesa/math/m_matrix.c \
         mesa/program/arbprogparse.c \
         mesa/program/prog_cache.c \
         mesa/program/prog_instruction.c \
         mesa/program/prog_opt_constant_fold.c \
         mesa/program/prog_optimize.c \
         mesa/program/prog_parameter.c \
         mesa/program/prog_parameter_layout.c \
         mesa/program/prog_print.c \
         mesa/program/program.c \
         mesa/program/programopt.c \
         mesa/program/program_parse_extra.c \
         mesa/program/prog_statevars.c \
         mesa/program/prog_to_nir.c \
         mesa/program/symbol_table.c \
         mesa/state_tracker/st_atifs_to_nir.c \
         mesa/state_tracker/st_atom_array.c \
         mesa/state_tracker/st_atom_atomicbuf.c \
         mesa/state_tracker/st_atom_blend.c \
         mesa/state_tracker/st_atom.c \
         mesa/state_tracker/st_atom_clip.c \
         mesa/state_tracker/st_atom_constbuf.c \
         mesa/state_tracker/st_atom_depth.c \
         mesa/state_tracker/st_atom_framebuffer.c \
         mesa/state_tracker/st_atom_image.c \
         mesa/state_tracker/st_atom_msaa.c \
         mesa/state_tracker/st_atom_pixeltransfer.c \
         mesa/state_tracker/st_atom_rasterizer.c \
         mesa/state_tracker/st_atom_sampler.c \
         mesa/state_tracker/st_atom_scissor.c \
         mesa/state_tracker/st_atom_shader.c \
         mesa/state_tracker/st_atom_stipple.c \
         mesa/state_tracker/st_atom_storagebuf.c \
         mesa/state_tracker/st_atom_tess.c \
         mesa/state_tracker/st_atom_texture.c \
         mesa/state_tracker/st_atom_viewport.c \
         mesa/state_tracker/st_cb_bitmap.c \
         mesa/state_tracker/st_cb_bitmap_shader.c \
         mesa/state_tracker/st_cb_blit.c \
         mesa/state_tracker/st_cb_bufferobjects.c \
         mesa/state_tracker/st_cb_clear.c \
         mesa/state_tracker/st_cb_compute.c \
         mesa/state_tracker/st_cb_condrender.c \
         mesa/state_tracker/st_cb_copyimage.c \
         mesa/state_tracker/st_cb_drawpixels.c \
         mesa/state_tracker/st_cb_drawpixels_shader.c \
         mesa/state_tracker/st_cb_drawtex.c \
         mesa/state_tracker/st_cb_eglimage.c \
         mesa/state_tracker/st_cb_fbo.c \
         mesa/state_tracker/st_cb_feedback.c \
         mesa/state_tracker/st_cb_flush.c \
         mesa/state_tracker/st_cb_memoryobjects.c \
         mesa/state_tracker/st_cb_msaa.c \
         mesa/state_tracker/st_cb_perfmon.c \
         mesa/state_tracker/st_cb_perfquery.c \
         mesa/state_tracker/st_cb_program.c \
         mesa/state_tracker/st_cb_queryobj.c \
         mesa/state_tracker/st_cb_rasterpos.c \
         mesa/state_tracker/st_cb_readpixels.c \
         mesa/state_tracker/st_cb_semaphoreobjects.c \
         mesa/state_tracker/st_cb_strings.c \
         mesa/state_tracker/st_cb_syncobj.c \
         mesa/state_tracker/st_cb_texturebarrier.c \
         mesa/state_tracker/st_cb_texture.c \
         mesa/state_tracker/st_cb_viewport.c \
         mesa/state_tracker/st_cb_xformfb.c \
         mesa/state_tracker/st_context.c \
         mesa/state_tracker/st_debug.c \
         mesa/state_tracker/st_draw.c \
         mesa/state_tracker/st_draw_feedback.c \
         mesa/state_tracker/st_extensions.c \
         mesa/state_tracker/st_format.c \
         mesa/state_tracker/st_gen_mipmap.c \
         mesa/state_tracker/st_manager.c \
         mesa/state_tracker/st_nir_builtins.c \
         mesa/state_tracker/st_nir_lower_builtin.c \
         mesa/state_tracker/st_nir_lower_tex_src_plane.c \
         mesa/state_tracker/st_pbo.c \
         mesa/state_tracker/st_program.c \
         mesa/state_tracker/st_sampler_view.c \
         mesa/state_tracker/st_scissor.c \
         mesa/state_tracker/st_shader_cache.c \
         mesa/state_tracker/st_texture.c \
         mesa/state_tracker/st_tgsi_lower_depth_clamp.c \
         mesa/state_tracker/st_tgsi_lower_yuv.c \
         mesa/vbo/vbo_context.c \
         mesa/vbo/vbo_exec_api.c \
         mesa/vbo/vbo_exec.c \
         mesa/vbo/vbo_exec_draw.c \
         mesa/vbo/vbo_exec_eval.c \
         mesa/vbo/vbo_minmax_index.c \
         mesa/vbo/vbo_noop.c \
         mesa/vbo/vbo_save_api.c \
         mesa/vbo/vbo_save.c \
         mesa/vbo/vbo_save_draw.c \
         mesa/vbo/vbo_save_loopback.c \
         mesa/x86/common_x86.c \
         util/blob.c \
         util/build_id.c \
         util/crc32.c \
         util/debug.c \
         util/disk_cache.c \
         util/disk_cache_os.c \
         util/double.c \
         util/format/u_format_bptc.c \
         util/format/u_format.c \
         util/format/u_format_etc.c \
         util/format/u_format_latc.c \
         util/format/u_format_other.c \
         util/format/u_format_rgtc.c \
         util/format/u_format_s3tc.c \
         util/format/u_format_yuv.c \
         util/format/u_format_zs.c \
         util/half_float.c \
         util/hash_table.c \
         util/mesa-sha1.c \
         util/os_file.c \
         util/os_misc.c \
         util/os_time.c \
         util/ralloc.c \
         util/rand_xor.c \
         util/rgtc.c \
         util/set.c \
         util/sha1/sha1.c \
         util/softfloat.c \
         util/string_buffer.c \
         util/strtod.c \
         util/u_cpu_detect.c \
         util/u_debug.c \
         util/u_idalloc.c \
         util/u_math.c \
         util/u_mm.c \
         util/u_process.c \
         util/u_queue.c \
         util/u_vector.c \
         util/xmlconfig.c

CC_OPT += -DMAPI_ABI_HEADER=\"glapi/gen/glapi_mapi_tmp.h\" \
          -DMAPI_MODE_BRIDGE


CC_OPT_loader/loader = -DDEFAULT_DRIVER_DIR='"/drivers"'
CC_OPT_compiler/glsl/glsl_lexer = -include "stdint.h"
CC_OPT_gallium/auxiliary/pipe-loader/pipe_loader_sw = -DPIPE_SEARCH_DIR='"/pipe"'

vpath %.c   $(MESA_SRC_DIR)/src
vpath %.c   $(MESA_GEN_DIR)/src
vpath %.cpp $(MESA_SRC_DIR)/src
vpath %.cpp $(MESA_GEN_DIR)/src
vpath %.cc  $(LIB_DIR)
