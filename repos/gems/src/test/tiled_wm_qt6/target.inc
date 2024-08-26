QT6_PORT_LIBS = libQt6Core libQt6Gui libQt6Widgets

LIBS = base libc libm mesa stdcxx qoost

include $(call select_from_repositories,lib/import/import-qt6_qmake.mk)

QT6_GENODE_LIBS_APP += ld.lib.so
QT6_GENODE_LIBS_APP := $(filter-out qt6_component.lib.so,$(QT6_GENODE_LIBS_APP))

qmake_prepared.tag: build_dependencies/lib/ld.lib.so

INC_DIR += $(PRG_DIR)/..

#
# We need Qt headers in a local directory for MOC to work correctly
#

# icon.h from the qoost API package
ICON_H = $(call select_from_repositories,include/qoost/icon.h)

# fall-back to the qoost port directory if that fails
ifeq ($(ICON_H),)
ICON_H := $(call select_from_ports,qoost)/include/qoost/icon.h
endif

icon.h: $(ICON_H)
	$(VERBOSE)cp $(ICON_H) .
