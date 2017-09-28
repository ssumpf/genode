LIBS       = libc
SHARED_LIB = yes
JDK_BASE   = $(call select_from_ports,jdk)/src/app/jdk/jdk/src/java.base

SRC_CC = endian.cpp \
         imageDecompressor.cpp \
         imageFile.cpp \
         jimage.cpp \
         NativeImageBuffer.cpp \
         osSupport_unix.cpp

INC_DIR += $(JDK_BASE)/share/native/include \
           $(JDK_BASE)/share/native/libjava \
           $(JDK_BASE)/share/native/libjimage \
           $(JDK_BASE)/unix/native/include \
           $(JDK_BASE)/unix/native/libjava \
           $(BUILD_BASE_DIR)/tool/jdk/support/headers/java.base

vpath %.cpp $(JDK_BASE)/share/native/libjimage
vpath %.cpp $(JDK_BASE)/unix/native/libjimage
