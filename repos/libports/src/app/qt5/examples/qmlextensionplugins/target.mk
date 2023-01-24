QMAKE_PROJECT_FILE = $(QT_DIR)/qtdeclarative/examples/qml/qmlextensionplugins/qmlextensionplugins.pro

QT5_PORT_LIBS = libQt5Core libQt5Gui libQt5Network libQt5Qml

LIBS = libc libm mesa qt5_component stdcxx $(QT5_PORT_LIBS)

include $(call select_from_repositories,lib/import/import-qt5_qmake.mk)

#
# create symlinks and tar archive for QML plugin
#

PLUGIN_TAR = $(BUILD_BASE_DIR)/bin/timeexample_qml.tar

$(TARGET): $(PLUGIN_TAR)

$(PLUGIN_TAR): build_with_qmake
	$(VERBOSE)mkdir -p qt/qml
	$(VERBOSE)ln -sf ../../imports/TimeExample qt/qml/
	$(VERBOSE)cd qt/qml/TimeExample && \
		$(STRIP) libqmlqtimeexampleplugin.lib.so -o libqmlqtimeexampleplugin.lib.so.stripped
	$(VERBOSE)ln -sf $(CURDIR)/qt/qml/TimeExample/libqmlqtimeexampleplugin.lib.so.stripped $(PWD)/bin/libqmlqtimeexampleplugin.lib.so
	$(VERBOSE)ln -sf $(CURDIR)/qt/qml/TimeExample/libqmlqtimeexampleplugin.lib.so $(PWD)/debug/
	$(VERBOSE)tar chf $@ --exclude='*.lib.so' --transform='s/\.stripped//' qt
