JDK_TOOL_BASE   = $(BUILD_BASE_DIR)/tool/jdk
JDK_CONTRIB_DIR = $(call select_from_ports,jdk)/src/app/jdk

#XXX: add different configure options for ARM
$(JDK_TOOL_BASE)/.prepared:
	@echo "Building jdk ..."
	@mkdir -p $(JDK_TOOL_BASE)
	unset VERBOSE && cd $(JDK_TOOL_BASE) && /bin/bash $(JDK_CONTRIB_DIR)/configure && make
	@touch $(JDK_TOOL_BASE)/.prepared

all: $(JDK_TOOL_BASE)/.prepared
