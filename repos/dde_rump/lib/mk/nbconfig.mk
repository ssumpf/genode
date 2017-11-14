include $(REP_DIR)/lib/mk/rump2.inc

CC   ?= gcc
YACC ?= bison
LEX  ?= flex

SRC_C = files.c \
        hash.c \
        lint.c \
        main.c \
        mkdevsw.c \
        mkheaders.c \
        mkioconf.c \
        mkmakefile.c \
        mkswap.c \
        pack.c \
        sem.c \
        util.c

TARGET = $(RUMP_BASE)/bin/nbconfig

OBJ = $(SRC_C:%.c=$(RUMP_BASE)/%.o)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $<

vpath %.c $(RUMP_PORT_DIR)/src/usr.bin/config
vpath %.c $(RUMP_BASE)
