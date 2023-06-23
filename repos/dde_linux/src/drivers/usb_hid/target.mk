TARGET  = usb_hid_drv
LIBS    = base jitterentropy virt_lx_emul

INC_DIR = $(PRG_DIR) $(REP_DIR)/src/lib/usb_client

SRC_C = dummies.c \
        generated_dummies.c \
        led.c \
        lx_emul.c \
        lx_user.c \
        lx_emul/urb.c

SRC_C += lx_emul/shadow/drivers/input/evdev.c

SRC_CC = main.cc \
         usb_client/usb_client.cc \

SRC_CC += lx_emul/event.cc \
          lx_emul/random.cc

SRC_CC += genode_c_api/event.cc

vpath %.c  $(PRG_DIR)
vpath %.cc $(PRG_DIR)
vpath %.c  $(REP_DIR)/src/lib
vpath %.cc $(REP_DIR)/src/lib

C_API = $(dir $(call select_from_repositories,src/lib/genode_c_api))

vpath genode_c_api/event.cc $(C_API)
