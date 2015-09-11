REQUIRES = riscv

include $(REP_DIR)/lib/mk/ldso.inc

INC_DIR += $(DIR)/riscv
vpath %.s $(DIR)/riscv
