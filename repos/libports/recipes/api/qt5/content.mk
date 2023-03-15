MIRROR_FROM_REP_DIR := lib/import/import-qt5_cmake.mk \
                       lib/import/import-qt5_qmake.mk

content: $(MIRROR_FROM_REP_DIR)

$(MIRROR_FROM_REP_DIR):
	$(mirror_from_rep_dir)

PORT_DIR := $(call port_dir,$(REP_DIR)/ports/qt5)

MIRROR_FROM_PORT_DIR := src/lib/qt5/genode/api/include \
                        src/lib/qt5/genode/api/mkspecs \
                        src/lib/qt5/genode/api/lib/cmake \

MIRROR_SYMBOLS := src/lib/qt5/genode/api/lib/symbols/libQt5Core \
                  src/lib/qt5/genode/api/lib/symbols/libQt5Gui \
                  src/lib/qt5/genode/api/lib/symbols/libQt5Network \
                  src/lib/qt5/genode/api/lib/symbols/libQt5PrintSupport \
                  src/lib/qt5/genode/api/lib/symbols/libQt5Sql \
                  src/lib/qt5/genode/api/lib/symbols/libQt5Svg \
                  src/lib/qt5/genode/api/lib/symbols/libQt5Test \
                  src/lib/qt5/genode/api/lib/symbols/libQt5Widgets \
                  src/lib/qt5/genode/api/lib/symbols/libQt5Xml \
                  src/lib/qt5/genode/api/lib/symbols/libqgenode


content: $(MIRROR_FROM_PORT_DIR)

$(MIRROR_FROM_PORT_DIR):
	cp -r $(PORT_DIR)/$@ .

content: $(MIRROR_SYMBOLS)

$(MIRROR_SYMBOLS):
	mkdir -p lib/symbols
	cp $(PORT_DIR)/$@ lib/symbols


content: LICENSE

LICENSE:
	cp $(PORT_DIR)/src/lib/qt5/LICENSE.LGPLv3 $@
