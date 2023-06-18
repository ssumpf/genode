TARGET  = usb_hid_drv
LIBS    = base jitterentropy virt_lx_emul

INC_DIR = $(PRG_DIR) $(REP_DIR)/src/lib/usb_client

SRC_C = dummies.c \
        generated_dummies.c \
        lx_emul.c


SRC_CC = main.cc \
         lx_emul/random.cc \
         lx_emul/urb.c \
         usb_client/usb_client.cc

vpath %.c  $(PRG_DIR)
vpath %.cc $(PRG_DIR)
vpath %.c  $(REP_DIR)/src/lib
vpath %.cc $(REP_DIR)/src/lib
