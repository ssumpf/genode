PORT_DIR := $(call port_dir,$(REP_DIR)/ports/qt5)

MIRROR_SYMBOLS := src/lib/qt5/genode/api/lib/symbols/libQt5Qml \
                  src/lib/qt5/genode/api/lib/symbols/libQt5QmlModels \
                  src/lib/qt5/genode/api/lib/symbols/libQt5Quick \
                  src/lib/qt5/genode/api/lib/symbols/libQt5QuickControls2 \
                  src/lib/qt5/genode/api/lib/symbols/libQt5QuickTemplates2 \
                  src/lib/qt5/genode/api/lib/symbols/libQt5QuickWidgets \
                  src/lib/qt5/genode/api/lib/symbols/libQt5VirtualKeyboard \
                  src/lib/qt5/genode/api/lib/symbols/qt5_quickcontrols

content: $(MIRROR_SYMBOLS)

$(MIRROR_SYMBOLS):
	mkdir -p lib/symbols
	cp $(PORT_DIR)/$@ lib/symbols

content: LICENSE

LICENSE:
	cp $(PORT_DIR)/src/lib/qt5/LICENSE.LGPLv3 $@
