CMAKE_LISTS_DIR = $(PRG_DIR)

CMAKE_TARGET_BINARIES = test-qt_core_cmake

QT6_PORT_LIBS = libQt6Core

LIBS = libc libm qt6_component stdcxx

include $(call select_from_repositories,lib/import/import-qt6_cmake.mk)
