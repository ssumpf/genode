TARGET  = usb_hid_drv
LIBS    = base jitterentropy virt_lx_emul

INC_DIR = $(PRG_DIR) $(REP_DIR)/src/lib/usb_client

SRC_C = dummies.c \
        generated_dummies.c \
        lx_emul.c \
        lx_user.c \
        lx_emul/urb.c \


SRC_CC = main.cc \
         lx_emul/random.cc \
         usb_client/usb_client.cc \

CC_OPT += -fno-tree-vectorize
CC_C_OPT += -fno-tree-vectorize


vpath %.c  $(PRG_DIR)
vpath %.cc $(PRG_DIR)
vpath %.c  $(REP_DIR)/src/lib
vpath %.cc $(REP_DIR)/src/lib
