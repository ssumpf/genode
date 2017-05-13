include $(REP_DIR)/lib/mk/ioq3.inc

CC_OPT    += -D_GNU_SOURCE=1 -D_REENTRANT -DVCMODS_MISC -DVCMODS_OPENGLES -DVCMODS_DEPTH
CC_OPT_PIC =

SRC_O   = snd_mixa.o
SRC_C   = code/asm/ftola.c \
          code/asm/snapvector.c \
          code/client/cl_avi.c \
          code/client/cl_cgame.c \
          code/client/cl_cin.c \
          code/client/cl_console.c \
          code/client/cl_curl.c \
          code/client/cl_input.c \
          code/client/cl_keys.c \
          code/client/cl_main.c \
          code/client/cl_net_chan.c \
          code/client/cl_parse.c \
          code/client/cl_scrn.c \
          code/client/cl_ui.c \
          code/client/qal.c \
          code/client/snd_adpcm.c \
          code/client/snd_codec.c \
          code/client/snd_codec_ogg.c \
          code/client/snd_codec_wav.c \
          code/client/snd_dma.c \
          code/client/snd_main.c \
          code/client/snd_mem.c \
          code/client/snd_mix.c \
          code/client/snd_openal.c \
          code/client/snd_wavelet.c \
          code/jpeg-8c/jaricom.c \
          code/jpeg-8c/jcapimin.c \
          code/jpeg-8c/jcapistd.c \
          code/jpeg-8c/jcarith.c \
          code/jpeg-8c/jccoefct.c \
          code/jpeg-8c/jccolor.c \
          code/jpeg-8c/jcdctmgr.c \
          code/jpeg-8c/jchuff.c \
          code/jpeg-8c/jcinit.c \
          code/jpeg-8c/jcmainct.c \
          code/jpeg-8c/jcmarker.c \
          code/jpeg-8c/jcmaster.c \
          code/jpeg-8c/jcomapi.c \
          code/jpeg-8c/jcparam.c \
          code/jpeg-8c/jcprepct.c \
          code/jpeg-8c/jcsample.c \
          code/jpeg-8c/jctrans.c \
          code/jpeg-8c/jdapimin.c \
          code/jpeg-8c/jdapistd.c \
          code/jpeg-8c/jdarith.c \
          code/jpeg-8c/jdatadst.c \
          code/jpeg-8c/jdatasrc.c \
          code/jpeg-8c/jdcoefct.c \
          code/jpeg-8c/jdcolor.c \
          code/jpeg-8c/jddctmgr.c \
          code/jpeg-8c/jdhuff.c \
          code/jpeg-8c/jdinput.c \
          code/jpeg-8c/jdmainct.c \
          code/jpeg-8c/jdmarker.c \
          code/jpeg-8c/jdmaster.c \
          code/jpeg-8c/jdmerge.c \
          code/jpeg-8c/jdpostct.c \
          code/jpeg-8c/jdsample.c \
          code/jpeg-8c/jdtrans.c \
          code/jpeg-8c/jerror.c \
          code/jpeg-8c/jfdctflt.c \
          code/jpeg-8c/jfdctfst.c \
          code/jpeg-8c/jfdctint.c \
          code/jpeg-8c/jidctflt.c \
          code/jpeg-8c/jidctfst.c \
          code/jpeg-8c/jidctint.c \
          code/jpeg-8c/jmemmgr.c \
          code/jpeg-8c/jmemnobs.c \
          code/jpeg-8c/jquant1.c \
          code/jpeg-8c/jquant2.c \
          code/jpeg-8c/jutils.c \
          code/qcommon/cm_load.c \
          code/qcommon/cm_patch.c \
          code/qcommon/cm_polylib.c \
          code/qcommon/cm_test.c \
          code/qcommon/cm_trace.c \
          code/qcommon/cmd.c \
          code/qcommon/common.c \
          code/qcommon/cvar.c \
          code/qcommon/files.c \
          code/qcommon/huffman.c \
          code/qcommon/ioapi.c \
          code/qcommon/md4.c \
          code/qcommon/md5.c \
          code/qcommon/msg.c \
          code/qcommon/net_chan.c \
          code/qcommon/net_ip.c \
          code/qcommon/puff.c \
          code/qcommon/q_math.c \
          code/qcommon/q_shared.c \
          code/qcommon/unzip.c \
          code/qcommon/vm.c \
          code/qcommon/vm_interpreted.c \
          code/qcommon/vm_x86_64.c \
          code/qcommon/vm_x86_64_assembler.c \
          code/renderer/tr_font.c \
          code/renderer/tr_font.c \
          code/renderer/tr_image_bmp.c \
          code/renderer/tr_image_jpg.c \
          code/renderer/tr_image_pcx.c \
          code/renderer/tr_image_png.c \
          code/renderer/tr_image_tga.c \
          code/renderer/tr_noise.c \
          code/renderer/tr_animation.c \
          code/renderer/tr_backend.c \
          code/renderer/tr_bsp.c \
          code/renderer/tr_cmds.c \
          code/renderer/tr_curve.c \
          code/renderer/tr_flares.c \
          code/renderer/tr_image.c \
          code/renderer/tr_init.c \
          code/renderer/tr_light.c \
          code/renderer/tr_main.c \
          code/renderer/tr_marks.c \
          code/renderer/tr_mesh.c \
          code/renderer/tr_model.c \
          code/renderer/tr_model_iqm.c \
          code/renderer/tr_scene.c \
          code/renderer/tr_shade.c \
          code/renderer/tr_shade_calc.c \
          code/renderer/tr_shader.c \
          code/renderer/tr_shadows.c \
          code/renderer/tr_sky.c \
          code/renderer/tr_surface.c \
          code/renderer/tr_world.c \
          code/sdl/sdl_gamma.c \
          code/sdl/sdl_glimp.c \
          code/sdl/sdl_input.c \
          code/sdl/sdl_snd.c \
          code/server/sv_bot.c \
          code/server/sv_ccmds.c \
          code/server/sv_client.c \
          code/server/sv_game.c \
          code/server/sv_init.c \
          code/server/sv_main.c \
          code/server/sv_net_chan.c \
          code/server/sv_snapshot.c \
          code/server/sv_world.c \
          code/zlib/adler32.c \
          code/zlib/crc32.c \
          code/zlib/inffast.c \
          code/zlib/inflate.c \
          code/zlib/inftrees.c \
          code/zlib/zutil.c

          #code/renderer/tr_postprocess.c \
          #code/renderer/tr_glsl.c \
          #code/renderer/tr_vbo.c \
          #code/renderer/tr_fbo.c \
          ##code/renderer/tr_extramath.c \
          ##code/renderer/tr_extensions.c \
#          code/renderergl2/tr_animation.c \
#          code/renderergl2/tr_backend.c \
#          code/renderergl2/tr_bsp.c \
#          code/renderergl2/tr_cmds.c \
#          code/renderergl2/tr_curve.c \
#          code/renderergl2/tr_extensions.c \
#          code/renderergl2/tr_extramath.c \
#          code/renderergl2/tr_fbo.c \
#          code/renderergl2/tr_flares.c \
#          code/renderergl2/tr_glsl.c \
#          code/renderergl2/tr_image.c \
#          code/renderergl2/tr_init.c \
#          code/renderergl2/tr_light.c \
#          code/renderergl2/tr_main.c \
#          code/renderergl2/tr_marks.c \
#          code/renderergl2/tr_mesh.c \
#          code/renderergl2/tr_model.c \
#          code/renderergl2/tr_model_iqm.c \
#          code/renderergl2/tr_postprocess.c \
#          code/renderergl2/tr_scene.c \
#          code/renderergl2/tr_shade.c \
#          code/renderergl2/tr_shade_calc.c \
#          code/renderergl2/tr_shader.c \
#          code/renderergl2/tr_shadows.c \
#          code/renderergl2/tr_sky.c \
#          code/renderergl2/tr_surface.c \
#          code/renderergl2/tr_vbo.c \
#          code/renderergl2/tr_world.c \


snd_mixa.o: snd_mixa.s
	$(MSG_ASSEM)$@
	$(VERBOSE)$(CC) $(CC_DEF) $(CC_C_OPT) $(INCLUDES) -x assembler-with-cpp -o $@ -c $<

vpath snd_mixa.s $(IOQ3_DIR)/code/asm
