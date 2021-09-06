LIBS += libdrm i965 iris

CC_OPT += -DGALLIUM_i965 \
          -DGALLIUM_IRIS \
          -DHAVE_UINT128

include $(REP_DIR)/lib/mk/mesa.inc
include $(REP_DIR)/lib/mk/spec/x86/gen-common.inc
