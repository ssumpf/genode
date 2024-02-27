MIRROR_FROM_REP_DIR := lib/mk/vfs_oss_next.mk src/lib/vfs/oss_next

content: $(MIRROR_FROM_REP_DIR) LICENSE

$(MIRROR_FROM_REP_DIR):
	$(mirror_from_rep_dir)

LICENSE:
	cp $(GENODE_DIR)/LICENSE $@
