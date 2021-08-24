MIRROR_FROM_REP_DIR := \
                       lib/mk/egl.mk \
                       lib/mk/egl_etnaviv.mk \
                       lib/mk/egl_iris.mk \
                       lib/mk/egl_swrast.mk \
                       lib/mk/etnaviv.mk \
                       lib/mk/iris.mk \
                       lib/mk/iris_gen110.mk \
                       lib/mk/iris_gen120.mk \
                       lib/mk/iris_gen125.mk \
                       lib/mk/iris_gen80.mk \
                       lib/mk/iris_gen90.mk \
                       lib/mk/iris_gen.inc \
                       lib/mk/isl_gen110.mk \
                       lib/mk/isl_gen120.mk \
                       lib/mk/isl_gen125.mk \
                       lib/mk/isl_gen80.mk \
                       lib/mk/isl_gen90.mk \
                       lib/mk/isl_gen.inc \
                       lib/mk/glapi.mk \
                       lib/mk/mesa.inc \
                       lib/mk/mesa_api.mk \
                       lib/mk/mesa-common.inc \
                       lib/mk/softpipe.mk \
                       lib/mk/spec/arm_v8/mesa.mk \
                       lib/mk/spec/x86_64/mesa.mk \
                       src/lib/mesa

content: $(MIRROR_FROM_REP_DIR) src/lib/mesa/target.mk

$(MIRROR_FROM_REP_DIR):
	$(mirror_from_rep_dir)

src/lib/mesa/target.mk:
	mkdir -p $(dir $@)
	echo "LIBS = mesa" > $@

PORT_DIR := $(call port_dir,$(REP_DIR)/ports/mesa)

MIRROR_FROM_PORT_DIR := src/lib/mesa/src generated \

content: $(MIRROR_FROM_PORT_DIR)

$(MIRROR_FROM_PORT_DIR):
	mkdir -p $(dir $@)
	cp -r $(PORT_DIR)/$@ $(dir $@)

content: LICENSE

LICENSE:
	cp $(PORT_DIR)/src/lib/mesa/docs/license.rst $@
