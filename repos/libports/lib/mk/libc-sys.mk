LIBC_SYS_DIR = $(LIBC_DIR)/lib/libc/sys

SRC_C += \
	interposing_table.c \
	sigaction.c \
	sigprocmask.c \
	sigwait.c \

include $(REP_DIR)/lib/mk/libc-common.inc

vpath %.c $(LIBC_SYS_DIR)

CC_CXX_WARN_STRICT =
