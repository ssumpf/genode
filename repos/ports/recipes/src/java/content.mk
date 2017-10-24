content: src/app/jdk LICENSE lib/mk/spec/x86_64

PORT_DIR := $(call port_dir,$(REP_DIR)/ports/jdk)

src/app/jdk:
	mkdir -p $@
	cp -a $(PORT_DIR)/src/app/jdk/* $@
	cp -a  $(REP_DIR)/src/app/jdk/* $@

lib/mk/spec/x86_64:
	mkdir -p $@
	cp $(REP_DIR)/lib/mk/spec/x86_64/java.mk $@/
	cp $(REP_DIR)/lib/mk/spec/x86_64/jvm.mk $@/
	cp $(REP_DIR)/lib/mk/java.inc lib/mk/
	cp $(REP_DIR)/lib/mk/jdk_version.inc lib/mk/
	cp $(REP_DIR)/lib/mk/jimage.mk lib/mk/
	cp $(REP_DIR)/lib/mk/jli.mk lib/mk/
	cp $(REP_DIR)/lib/mk/jnet.mk lib/mk/
	cp $(REP_DIR)/lib/mk/jtool.mk lib/mk/
	cp $(REP_DIR)/lib/mk/jvm.inc lib/mk/
	cp $(REP_DIR)/lib/mk/jzip.mk lib/mk/
	cp $(REP_DIR)/lib/mk/nio.mk lib/mk/

LICENSE:
	cp $(PORT_DIR)/src/app/jdk/LICENSE $@

