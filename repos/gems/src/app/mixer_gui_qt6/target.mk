QMAKE_PROJECT_FILE = $(PRG_DIR)/mixer_gui_qt.pro

QMAKE_TARGET_BINARIES = mixer_gui_qt

QT6_PORT_LIBS = libQt6Core libQt6Gui libQt6Widgets

LIBS = base libc libm mesa stdcxx qoost $(QT6_PORT_LIBS)

include $(call select_from_repositories,lib/import/import-qt6_qmake.mk)

QT6_GENODE_LIBS_APP += ld.lib.so
QT6_GENODE_LIBS_APP := $(filter-out qt6_component.lib.so,$(QT6_GENODE_LIBS_APP))

qmake_prepared.tag: qmake_root/lib/ld.lib.so
