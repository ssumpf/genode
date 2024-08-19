QMAKE_PROJECT_FILE = $(PRG_DIR)/qt_core.pro

QMAKE_TARGET_BINARIES = test-qt_core

QT6_PORT_LIBS = libQt6Core

LIBS = libc libm qt6_component stdcxx $(QT6_PORT_LIBS)

include $(call select_from_repositories,lib/import/import-qt6_qmake.mk)
