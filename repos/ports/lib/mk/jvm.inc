LIBS         = stdcxx
SHARED_LIB   = yes
HOTSPOT_BASE = $(call select_from_ports,jdk)/src/app/jdk/hotspot/src

SRC_CC = $(shell cd $(HOTSPOT_BASE)/share/vm; find . -name "*.cpp")

CC_OPT += -fpermissive -Wno-comment

##XXX: may have to use our own
CC_OPT += -DINCLUDE_SUFFIX_OS=_bsd

INC_DIR += $(HOTSPOT_BASE)/os/bsd/vm \
           $(HOTSPOT_BASE)/os/posix/vm \
           $(HOTSPOT_BASE)/os_cpu/bsd_x86/vm

INC_DIR += $(REP_DIR)/src/app/jdk/lib/include \
           $(HOTSPOT_BASE)/share/vm \
           $(HOTSPOT_BASE)/share/vm/precompiled \
           $(HOTSPOT_BASE)/share/vm/prims

vpath %.cpp $(HOTSPOT_BASE)/share/vm

# vi: set ft=make :
