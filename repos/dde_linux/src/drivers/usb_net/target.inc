TARGET  = usb_net_drv
LIBS    = base jitterentropy virt_lx_emul

INC_DIR = $(PRG_DIR)/../..

SRC_C += dummies.c \
         generated_dummies.c \
         lx_emul.c \
         lx_user.c

#
SRC_C +=  lx_emul/virt/shadow/drivers/usb/core/urb.c
#
SRC_CC = main.cc
#
SRC_CC += lx_emul/random.cc
#
#SRC_CC += genode_c_api/event.cc \

SRC_CC  += genode_c_api/usb_client.cc

vpath %.c  $(PRG_DIR)
vpath %.c  $(PRG_DIR)/../..
vpath %.cc $(PRG_DIR)/../..
vpath %.c  $(REP_DIR)/src/lib
#vpath %.cc $(REP_DIR)/src/lib

C_API = $(dir $(call select_from_repositories,src/lib/genode_c_api))

#vpath genode_c_api/event.cc      $(C_API)
vpath genode_c_api/usb_client.cc $(C_API)

# vim: set ft=make :
