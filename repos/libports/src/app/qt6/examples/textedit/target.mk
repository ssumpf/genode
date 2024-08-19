QMAKE_PROJECT_FILE = $(QT_DIR)/qtbase/tests/manual/examples/widgets/richtext/textedit/textedit.pro

QMAKE_TARGET_BINARIES = textedit

QT6_PORT_LIBS = libQt6Core libQt6Gui libQt6PrintSupport libQt6Widgets

LIBS = libc libm mesa qt6_component stdcxx $(QT6_PORT_LIBS)

include $(call select_from_repositories,lib/import/import-qt6_qmake.mk)
