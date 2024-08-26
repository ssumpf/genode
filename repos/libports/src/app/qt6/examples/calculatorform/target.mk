QMAKE_PROJECT_FILE = $(QT_DIR)/qttools/examples/designer/calculatorform/calculatorform.pro

QMAKE_TARGET_BINARIES = calculatorform

QT6_PORT_LIBS = libQt6Core libQt6Gui libQt6Widgets

LIBS = libc libm mesa qt6_component stdcxx

include $(call select_from_repositories,lib/import/import-qt6_qmake.mk)
