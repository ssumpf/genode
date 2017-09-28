LIBS       = libc zlib
SHARED_LIB = yes
JDK_BASE   = $(call select_from_ports,jdk)/src/app/jdk/jdk/src/java.base

SRC_C = Adler32.c CRC32.c Deflater.c Inflater.c zip_util.c

INC_DIR += $(JDK_BASE)/share/native/include \
           $(JDK_BASE)/share/native/libjava \
           $(JDK_BASE)/unix/native/include \
           $(JDK_BASE)/unix/native/libjava \
           $(BUILD_BASE_DIR)/tool/jdk/support/headers/java.base

CC_C_OPT = -D_ALLBSD_SOURCE

vpath %.c $(JDK_BASE)/share/native/libzip
