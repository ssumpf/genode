include $(REP_DIR)/lib/mk/virtualbox7-common.inc

SRC_CC += VMM/VMMR3/CPUMDbg.cpp
SRC_CC += VMM/VMMR3/DBGF.cpp
SRC_CC += VMM/VMMR3/DBGFAddr.cpp
SRC_CC += VMM/VMMR3/DBGFDisas.cpp
SRC_CC += VMM/VMMR3/DBGFMem.cpp
SRC_CC += VMM/VMMR3/DBGFR3Trace.cpp
SRC_CC += VMM/VMMR3/DBGFReg.cpp

SRC_CC += $(addprefix Disassembler/, $(notdir $(wildcard $(VBOX_DIR)/Disassembler/*.cpp)))

FILTERED_OUT_SRC_CC += Disassembler/DisasmFormatArmV8.cpp
FILTERED_OUT_SRC_CC += Disassembler/DisasmCore-armv8.cpp
FILTERED_OUT_SRC_CC += Disassembler/DisasmReg.cpp
FILTERED_OUT_SRC_CC += Disassembler/DisasmTables-armv8-a64.cpp

SRC_CC := $(filter-out $(FILTERED_OUT_SRC_CC), $(SRC_CC))

INC_DIR += $(VBOX_DIR)/VMM/include

CC_OPT += -DVBOX_IN_VMM

CC_CXX_WARN_STRICT =
