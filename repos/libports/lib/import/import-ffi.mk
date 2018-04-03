ifeq ($(filter-out $(SPECS),x86_64),)
INC_DIR += $(call select_from_ports,ffi)/include/ffi/x86_64
endif
