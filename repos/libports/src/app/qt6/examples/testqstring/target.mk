QMAKE_PROJECT_FILE = $(QT_DIR)/qtbase/examples/qtestlib/tutorial1

QMAKE_TARGET_BINARIES = tutorial1

QT6_PORT_LIBS = libQt6Core libQt6Gui libQt6Test libQt6Widgets

LIBS = libc libm mesa qt6_component stdcxx $(QT6_PORT_LIBS)

include $(call select_from_repositories,lib/import/import-qt6_qmake.mk)
