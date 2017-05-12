IOQ3_DIR    = $(call select_from_ports,ioq3)/src/app/ioq3
INC_DIR    += $(IOQ3_DIR)/code/jpeg-8c \
              $(IOQ3_DIR)/code/zlib
CC_OPT      = -Wimplicit -pipe -DUSE_ICON -DNO_GZIP \
              -DUSE_INTERNAL_JPEG  -DUSE_LOCAL_HEADERS -DSTANDALONE \
              -DPRODUCT_VERSION=\"1.36-GIT\" -Wformat=2 -Wno-format-zero-length -Wformat-security \
              -Wno-format-nonliteral -Wstrict-aliasing=2 -Wmissing-format-attribute -Wdisabled-optimization \
              -Werror-implicit-function-declaration -DNDEBUG -funroll-loops -falign-loops=2 \
              -falign-jumps=2 -falign-functions=2 -fstrength-reduce -ffast-math
CC_MARCH    = -march=core2 -m32
LIBS        = sdl libc libm

vpath %.c $(IOQ3_DIR)
