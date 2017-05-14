TARGET      = ioq3
LIBS        = libc sdl \
              mesa-11 ioq3_bot ioq3_common ioq3_renderer libc_resolv

SRC_C       = con_log.c con_passive.c sys_main.c sys_unix.c
SRC_CC      = main.cc

CC_OPT_sys_main = -Dmain=ioq3_main
CC_OPT      = -Wimplicit -pipe -DUSE_ICON -DNO_GZIP \
              -DUSE_INTERNAL_JPEG  -DUSE_LOCAL_HEADERS -DSTANDALONE \
              -DPRODUCT_VERSION=\"1.36-GIT\" -Wformat=2 -Wno-format-zero-length \
              -Wformat-security -Wno-format-nonliteral -Wstrict-aliasing=2 \
              -Wmissing-format-attribute -Wdisabled-optimization \
              -Werror-implicit-function-declaration -DNDEBUG -funroll-loops \
              -falign-loops=2 -falign-jumps=2 -falign-functions=2 -fstrength-reduce \
              -ffast-math

INC_DIR   +=$(call select_from_repositories,src/lib/mesa/include)

REQUIRES = narf

vpath %.c $(call select_from_ports,ioq3)/src/app/ioq3/code/sys
