include $(REP_DIR)/lib/mk/rump2_common.inc

INC_DIR += $(LIBGCC_INC_DIR) \
           $(RUMP_PORT_DIR)//nblibs/lib/libpthread \
           $(RUMP_PORT_DIR)/src/sys \
           $(RUMP_PORT_DIR)/src/sys/rump/include  \
           $(RUMP_PORT_DIR)/src/sys/sys \
           $(RUMP_BASE)
