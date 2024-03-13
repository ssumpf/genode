MIRROR_FROM_REP_DIR := src/drivers/i2c_hid/pc \
                       src/lib/pc/lx_emul \
                       src/include

content: $(MIRROR_FROM_REP_DIR)
$(MIRROR_FROM_REP_DIR):
	$(mirror_from_rep_dir)

PORT_DIR := $(call port_dir,$(GENODE_DIR)/repos/dde_linux/ports/linux)

content: LICENSE
LICENSE:
	cp $(PORT_DIR)/src/linux/COPYING $@
