TARGET  = usb_hid_drv
LIBS    = base jitterentropy virt_lx_emul
INC_DIR = $(PRG_DIR)

SRC_C = dummies.c \
        generated_dummies.c \
        lx_emul.c \
        lx_user.c

SRC_CC = main.cc \
         lx_emul/random.cc

vpath %.c  $(PRG_DIR)
vpath %.c  $(PRG_DIR)
vpath %.cc $(REP_DIR)/src/lib
