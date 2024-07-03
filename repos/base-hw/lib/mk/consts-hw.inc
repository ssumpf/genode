REP_INC_DIR += src/lib/hw/$(ARCH_WIDTH_PATH)

SRC_CC += $(ARCH_WIDTH_PATH)/memory_map.cc

hw/memory_consts.h: $(call select_from_repositories,src/lib/hw/$(ARCH_WIDTH_PATH))/memory_consts.s
	$(MSG_CONVERT) $@
	$(VERBOSE)mkdir -p hw
	$(VERBOSE)sed -e 's/^HW_MM_\([0-9A-Z_]*\)\s*=\s*\(.*\)/		static constexpr Genode::size_t \1 = \2;/' -e 's/^#//' $< > $@

$(ARCH_WIDTH_PATH)/memory_map.cc: hw/memory_consts.h

vpath $(ARCH_WIDTH_PATH)/memory_map.cc $(call select_from_repositories,src/lib/hw)
