CC_OPT = -DINCLUDE_SUFFIX_CPU=_x86

INC_DIR = $(call select_from_ports,jdk)/src/app/jdk/hotspot/src/cpu/x86/vm

include $(REP_DIR)/lib/mk/jvm.inc
