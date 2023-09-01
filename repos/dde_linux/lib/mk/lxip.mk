LXIP_DIR       := $(REP_DIR)/src/lib/lxip
LIBS           := jitterentropy virt_lx_emul virt_linux_generated
SHARED_LIB     := yes

ifeq ($(filter-out $(SPECS),x86_64),)
	SPEC_ARCH := x86_64
endif

TARGET_LIB_DIR := $(LXIP_DIR)
INC_DIR        += $(LXIP_DIR)/include $(LXIP_DIR)

SRC_CC += lx_emul/random.cc

SRC_CC += init.cc

SRC_C += dummies.c \
         generated_dummies.c \
         lx_emul.c \
         lx_user.c \

vpath %.cc $(REP_DIR)/src/lib
vpath %.c  $(LXIP_DIR)/spec/$(SPEC_ARCH)
vpath %    $(LXIP_DIR)
