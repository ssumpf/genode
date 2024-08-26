QMAKE_PROJECT_FILE = $(QT_DIR)/qtbase/tests/manual/examples/widgets/widgets/tetrix/tetrix.pro

QMAKE_TARGET_BINARIES = tetrix

QT6_PORT_LIBS = libQt6Core libQt6Gui libQt6Widgets

LIBS = libc libm mesa qt6_component stdcxx

include $(call select_from_repositories,lib/import/import-qt6_qmake.mk)
