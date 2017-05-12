TARGET      = ioquake
LIBS        = libc sdl \
              ioq3_bot ioq3_common ioq3_renderer mesa-11
SRC_C       = con_log.c con_tty.c sys_main.c sys_unix.c
CC_OPT      = -Wimplicit -pipe -DUSE_ICON -DNO_GZIP \
              -DUSE_INTERNAL_JPEG  -DUSE_LOCAL_HEADERS -DSTANDALONE \
              -DPRODUCT_VERSION=\"1.36-GIT\" -Wformat=2 -Wno-format-zero-length \
              -Wformat-security -Wno-format-nonliteral -Wstrict-aliasing=2 \
              -Wmissing-format-attribute -Wdisabled-optimization \
              -Werror-implicit-function-declaration -DNDEBUG -funroll-loops \
              -falign-loops=2 -falign-jumps=2 -falign-functions=2 -fstrength-reduce \
              -ffast-math

REQUIRES = narf

vpath %.c $(call select_from_ports,ioq3)/src/app/ioq3/code/sys
