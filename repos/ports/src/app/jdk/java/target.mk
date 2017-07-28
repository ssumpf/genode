TARGET   = java
SRC_C    = main.c
LIBS     = jli java jvm posix

CC_C_OPT = -DVERSION_STRING='"9-genode.openjdk"'

JDK_PATH = $(call select_from_ports,jdk)/src/app/jdk
vpath main.c $(JDK_PATH)/jdk/src/java.base/share/native/launcher
