LIBS       = libc
SHARED_LIB = yes
JDK_BASE   = $(call select_from_ports,jdk)/src/app/jdk/jdk/src/java.base
JAVA_BASE  = $(JDK_BASE)/share/native/libjava

SRC_C = $(notdir $(wildcard $(JAVA_BASE)/*.c))

include $(REP_DIR)/lib/mk/jdk_version.inc

CC_C_OPT = $(JDK_VERSION)

CC_C_OPT += -Dlseek64=lseek -DO_DSYNC=O_SYNC

INC_DIR += $(REP_DIR)/src/app/jdk/lib/include \
           $(REP_DIR)/src/app/jdk/lib/include/java.base \
           $(JDK_BASE)/share/native/include \
           $(JDK_BASE)/share/native/libfdlibm \
           $(JDK_BASE)/share/native/libjava \
           $(JDK_BASE)/unix/native/include \
           $(JDK_BASE)/unix/native/libjava

vpath %.c $(JAVA_BASE)
