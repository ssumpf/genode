LIBS       = libc
SHARED_LIB = yes
JDK_BASE   = $(call select_from_ports,jdk)/src/app/jdk/jdk/src/java.base

SRC_C = bsd_close.c \
        net_util.c \
        net_util_md.c \
        InetAddress.c \
        Inet4Address.c \
        Inet6Address.c \

INC_DIR += $(BUILD_BASE_DIR)/tool/jdk/support/headers/java.base \
           $(JDK_BASE)/share/native/include \
           $(JDK_BASE)/share/native/libjava \
           $(JDK_BASE)/share/native/libnet \
           $(JDK_BASE)/share/native/libnio \
           $(JDK_BASE)/share/native/libnio/ch \
           $(JDK_BASE)/unix/native/include \
           $(JDK_BASE)/unix/native/libjava \
           $(JDK_BASE)/unix/native/libnet \
           $(JDK_BASE)/unix/native/libnio

CC_C_OPT = -D_ALLBSD_SOURCE -include netinet/in.h
CC_OPT_net_util_md += -include sys/socket.h

vpath %.c $(JDK_BASE)/unix/native/libnet
vpath %.c $(JDK_BASE)/share/native/libnet
vpath %.c $(JDK_BASE)/macosx/native/libnet
