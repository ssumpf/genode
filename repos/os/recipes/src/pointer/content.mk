SRC_DIR := src/app/pointer
include $(GENODE_DIR)/repos/base/recipes/src/content.inc

content: include/pointer

include/pointer:
	$(mirror_from_rep_dir)
