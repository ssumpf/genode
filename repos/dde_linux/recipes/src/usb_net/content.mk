MIRROR_FROM_REP_DIR := src/driver/usb_net

content: $(MIRROR_FROM_REP_DIR)
$(MIRROR_FROM_REP_DIR):
	$(mirror_from_rep_dir)

PORT_DIR := $(call port_dir,$(GENODE_DIR)/repos/dde_linux/ports/legacy_linux)

content: LICENSE
LICENSE:
	cp $(PORT_DIR)/src/linux/COPYING $@
