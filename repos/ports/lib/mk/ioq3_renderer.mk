include $(REP_DIR)/lib/mk/ioq3.inc

SHADERS = bokeh_fp.glsl \
          bokeh_vp.glsl \
          calclevels4x_fp.glsl \
          calclevels4x_vp.glsl \
          depthblur_fp.glsl \
          depthblur_vp.glsl \
          dlight_fp.glsl \
          dlight_vp.glsl \
          down4x_fp.glsl \
          down4x_vp.glsl \
          fogpass_fp.glsl \
          fogpass_vp.glsl \
          generic_fp.glsl \
          generic_vp.glsl \
          lightall_fp.glsl \
          lightall_vp.glsl \
          pshadow_fp.glsl \
          pshadow_vp.glsl \
          shadowfill_fp.glsl \
          shadowfill_vp.glsl \
          shadowmask_fp.glsl \
          shadowmask_vp.glsl \
          ssao_fp.glsl \
          ssao_vp.glsl \
          texturecolor_fp.glsl \
          texturecolor_vp.glsl \
          tonemap_fp.glsl \
          tonemap_vp.glsl

SRC_C   = $(SHADERS:.glsl=.c)

$(SRC_C): $(SHADERS)
	$(VERBOSE)$(ECHO) "REF_STR $(@: .c=.glsl)"
	$(VERBOSE)echo "const char *fallbackShader_$(notdir $(basename $@)) =" > $@
	$(VERBOAE)cat $(IOQ3_DIR)/code/rend2/glsl/$(@:.c=.glsl) | sed 's/^/\"/;s/$$/\\n\"/' >> $@
	$(VERBOSE)echo ";" >> $@


# $(VERBOSE)cat $(@: .c=.glsl) | sed 's/^/\"/;s/$$/\\n\"/' >> $@
vpath %.glsl $(IOQ3_DIR)/code/rend2/glsl
