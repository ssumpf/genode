#
# The following externally defined variables are evaluated:
#
# CMAKE_LISTS_DIR:      path to the CMakeLists.txt file
# CMAKE_TARGET_BINARIES binaries to be stripped and linked into 'bin' and 'debug' directories
# QT6_PORT_LIBS:        Qt6 libraries used from port (for example libQt6Core)
#

QT_TOOLS_DIR = /usr/local/genode/tool/23.05/qt6

ifeq ($(filter-out $(SPECS),arm),)
QT_PLATFORM = genode-arm-g++
else ifeq ($(filter-out $(SPECS),arm_64),)
QT_PLATFORM = genode-aarch64-g++
else ifeq ($(filter-out $(SPECS),x86_32),)
QT_PLATFORM = genode-x86_32-g++
else ifeq ($(filter-out $(SPECS),x86_64),)
QT_PLATFORM = genode-x86_64-g++
else
$(error Error: unsupported platform)
endif

ifeq ($(CONTRIB_DIR),)
QT_DIR     = $(call select_from_repositories,src/lib/qt6)
QT_API_DIR = $(call select_from_repositories,mkspecs)/..
else
QT_PORT_DIR := $(call select_from_ports,qt6)
QT_DIR       = $(QT_PORT_DIR)/src/lib/qt6
QT_API_DIR   = $(QT_DIR)/genode/api
endif

ifeq ($(VERBOSE),)
MAKE_VERBOSE="1"
else
QT6_OUTPUT_FILTER = > /dev/null
endif

#
# Genode libraries to be linked to Qt applications and libraries
#

QT6_GENODE_LIBS_APP   = libc.lib.so libm.lib.so stdcxx.lib.so qt6_component.lib.so
QT6_GENODE_LIBS_SHLIB = libc.lib.so libm.lib.so stdcxx.lib.so ldso_so_support.lib.a

#
# flags to be passed to CMake
#

GENODE_CMAKE_CFLAGS = \
	-D__FreeBSD__=12 \
	-D__GENODE__ \
	-ffunction-sections \
	-fno-strict-aliasing \
	$(CC_OPT_NOSTDINC) \
	$(CC_MARCH) \
	$(CC_OPT_PIC) \
	$(filter-out -I.,$(INCLUDES)) \
	-I$(CURDIR)/cmake_root/mkspecs/$(QT_PLATFORM)

GENODE_CMAKE_LFLAGS_APP = \
	$(addprefix $(LD_OPT_PREFIX),$(LD_MARCH)) \
	$(addprefix $(LD_OPT_PREFIX),$(LD_OPT_GC_SECTIONS)) \
	$(addprefix $(LD_OPT_PREFIX),$(LD_OPT_ALIGN_SANE)) \
	$(addprefix $(LD_OPT_PREFIX),--dynamic-list=$(BASE_DIR)/src/ld/genode_dyn.dl) \
	$(LD_OPT_NOSTDLIB) \
	-Wl,-Ttext=0x01000000 \
	$(CC_MARCH) \
	-Wl,--dynamic-linker=$(DYNAMIC_LINKER).lib.so \
	-Wl,--eh-frame-hdr \
	-Wl,-rpath-link=. \
	-Wl,-T -Wl,$(LD_SCRIPT_DYN) \
	-L$(CURDIR)/cmake_root/lib \
	-Wl,--whole-archive \
	-Wl,--start-group \
	$(addprefix -l:,$(QT6_GENODE_LIBS_APP)) \
	$(shell $(CC) $(CC_MARCH) -print-libgcc-file-name) \
	-Wl,--end-group \
	-Wl,--no-whole-archive

GENODE_CMAKE_LFLAGS_SHLIB = \
	$(LD_OPT_NOSTDLIB) \
	-Wl,-shared \
	-Wl,--eh-frame-hdr \
	$(addprefix $(LD_OPT_PREFIX),$(LD_MARCH)) \
	$(addprefix $(LD_OPT_PREFIX),$(LD_OPT_GC_SECTIONS)) \
	$(addprefix $(LD_OPT_PREFIX),$(LD_OPT_ALIGN_SANE)) \
	-Wl,-T -Wl,$(LD_SCRIPT_SO) \
	$(addprefix $(LD_OPT_PREFIX),--entry=0x0) \
	-L$(CURDIR)/cmake_root/lib \
	-Wl,--whole-archive \
	-Wl,--start-group \
	$(addprefix -l:,$(QT6_GENODE_LIBS_SHLIB)) \
	$(shell $(CC) $(CC_MARCH) -print-libgcc-file-name) \
	-Wl,--end-group \
	-Wl,--no-whole-archive

##
## prepare a directory named 'cmake_root' where CMake can find needed files
##

cmake_root:
	$(VERBOSE)mkdir -p $@

cmake_root/include: cmake_root
	$(VERBOSE)mkdir -p $@
	$(VERBOSE)ln -snf $(QT_API_DIR)/include/* $@/

cmake_root/lib: cmake_root
	$(VERBOSE)mkdir -p $@

cmake_root/lib/cmake: cmake_root/lib
	$(VERBOSE)ln -snf $(QT_API_DIR)/lib/cmake $@

cmake_root/lib/%.lib.so: cmake_root/lib
	$(VERBOSE)ln -sf $(BUILD_BASE_DIR)/var/libcache/$*/$*.abi.so $@

cmake_root/lib/%.lib.a: cmake_root/lib
	$(VERBOSE)ln -sf $(BUILD_BASE_DIR)/var/libcache/$*/$*.lib.a $@

cmake_root/metatypes: cmake_root
	$(VERBOSE)ln -snf $(QT_API_DIR)/metatypes $@

cmake_root/mkspecs: cmake_root
	$(VERBOSE)ln -snf $(QT_API_DIR)/mkspecs $@

cmake_prepared.tag: \
                    cmake_root/include \
                    cmake_root/lib/cmake \
                    cmake_root/lib/libc.lib.so \
                    cmake_root/lib/libm.lib.so \
                    cmake_root/lib/egl.lib.so \
                    cmake_root/lib/mesa.lib.so \
                    cmake_root/lib/qt6_component.lib.so \
                    cmake_root/lib/stdcxx.lib.so \
                    cmake_root/lib/ldso_so_support.lib.a \
                    cmake_root/metatypes \
                    cmake_root/mkspecs

# add symlinks for Qt6 libraries listed in the 'QT6_PORT_LIBS' variable
ifeq ($(CONTRIB_DIR),)
	$(VERBOSE)for qt6_lib in $(QT6_PORT_LIBS); do \
		ln -sf $(BUILD_BASE_DIR)/var/libcache/$${qt6_lib}/$${qt6_lib}.abi.so cmake_root/lib/$${qt6_lib}.lib.so; \
	done
else
	$(VERBOSE)for qt6_lib in $(QT6_PORT_LIBS); do \
		ln -sf $(BUILD_BASE_DIR)/bin/$${qt6_lib}.lib.so cmake_root/lib/; \
	done
endif
	$(VERBOSE)touch $@

.PHONY: build_with_cmake

# 'make' called by CMake uses '/bin/sh', which does not understand '-o pipefail'
unexport .SHELLFLAGS

build_with_cmake: cmake_prepared.tag
	$(VERBOSE)cmake \
	-G "Unix Makefiles" \
	-DCMAKE_PREFIX_PATH="$(CURDIR)/cmake_root" \
	-DCMAKE_MODULE_PATH="$(CURDIR)/cmake_root/lib/cmake/Modules" \
	-DCMAKE_SYSTEM_NAME="Genode" \
	-DCMAKE_AR="$(AR)" \
	-DCMAKE_C_COMPILER="$(CC)" \
	-DCMAKE_C_FLAGS="$(GENODE_CMAKE_CFLAGS)" \
	-DCMAKE_CXX_COMPILER="$(CXX)" \
	-DCMAKE_CXX_FLAGS="$(GENODE_CMAKE_CFLAGS)" \
	-DCMAKE_EXE_LINKER_FLAGS="$(GENODE_CMAKE_LFLAGS_APP)" \
	-DCMAKE_SHARED_LINKER_FLAGS="$(GENODE_CMAKE_LFLAGS_SHLIB)" \
	-DCMAKE_MODULE_LINKER_FLAGS="$(GENODE_CMAKE_LFLAGS_SHLIB)" \
	--no-warn-unused-cli \
	$(CMAKE_LISTS_DIR) \
	$(QT6_OUTPUT_FILTER)

	$(VERBOSE)$(MAKE) VERBOSE=$(MAKE_VERBOSE)

#
# Not every CMake project has an 'install' target, so execute
# this target only if a binary to be installed has "install/" in
# its path.
#
ifneq ($(findstring install/,$(CMAKE_TARGET_BINARIES)),)
	$(VERBOSE)$(MAKE) VERBOSE=$(MAKE_VERBOSE) DESTDIR=install install
endif

	$(VERBOSE)for cmake_target_binary in $(CMAKE_TARGET_BINARIES); do \
		$(OBJCOPY) --only-keep-debug  $${cmake_target_binary} $${cmake_target_binary}.debug; \
		$(STRIP) $${cmake_target_binary} -o $${cmake_target_binary}.stripped; \
		$(OBJCOPY) --add-gnu-debuglink=$${cmake_target_binary}.debug $${cmake_target_binary}.stripped; \
		ln -sf $(CURDIR)/$${cmake_target_binary}.stripped $(PWD)/bin/`basename $${cmake_target_binary}`; \
		ln -sf $(CURDIR)/$${cmake_target_binary}.stripped $(PWD)/debug/`basename $${cmake_target_binary}`; \
		ln -sf $(CURDIR)/$${cmake_target_binary}.debug $(PWD)/debug/; \
	done

BUILD_ARTIFACTS ?= $(notdir $(CMAKE_TARGET_BINARIES))

#
# build applications with CMake
#
TARGET ?= $(CMAKE_LISTS_DIR).cmake_target
.PHONY: $(TARGET)
$(TARGET): build_with_cmake
