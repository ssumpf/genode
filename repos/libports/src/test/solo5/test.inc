TEST_NAME := test_$(subst $(REP_DIR)/src/test/solo5/,,$(PRG_DIR))
TARGET = solo5-$(TEST_NAME)

LIBS += base solo5

CC_OPT += -fstack-protector-strong

# GCC 8 complains about mismatches of dummy function declarations
CC_OPT += -Wno-error=builtin-declaration-mismatch

SRC_C += $(TEST_NAME).c

vpath %.c $(call select_from_ports,solo5)/src/lib/solo5/tests/$(TEST_NAME)
