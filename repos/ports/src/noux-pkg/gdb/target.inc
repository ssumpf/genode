PKG_DIR = $(call select_from_ports,gdb)/src/noux-pkg/gdb

CONFIGURE_ARGS += --program-prefix=$(PROGRAM_PREFIX) \
                  --target=$(GDB_TARGET)

# the configure script calls the linker with "-lexpat", which fails
CONFIGURE_ARGS += --without-expat
CPPFLAGS += -DHAVE_LIBEXPAT=1
CFLAGS += -Wno-error=sizeof-pointer-memaccess -Wno-error=unused-value

# prevent errors when compiling GDB 7.3 with GCC 8
CFLAGS += -Wno-error=cast-function-type
CFLAGS += -Wno-error=format-overflow
CFLAGS += -Wno-error=implicit-fallthrough
CFLAGS += -Wno-error=stringop-truncation
CFLAGS += -Wno-error=int-in-bool-context

LIBS += ncurses expat

# workaround for problems with makeinfo version 5
MAKE_ENV += "MAKEINFO=true"

INSTALL_TARGET = install

include $(call select_from_repositories,mk/noux.mk)
