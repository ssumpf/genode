TARGET   = imx8q_gpu_drv
REQUIRES = arm_v8a
LIBS     = base
SRC_CC   = main.cc lx_emul.cc
SRC_C    = dummies.c lx_emul_c.c
SRC_C   += $(notdir $(wildcard $(PRG_DIR)/generated_dummies.c))

INC_DIR += $(PRG_DIR)
INC_DIR += $(PRG_DIR)/include

CC_OLEVEL := -O0


#
# Lx_emul + Lx_kit definitions
#

SRC_C   += lx_emul/init.c
SRC_CC  += lx_kit/debug.cc
SRC_CC  += lx_kit/env.cc
SRC_CC  += lx_kit/init.cc
SRC_CC  += lx_kit/printf.cc
SRC_CC  += lx_kit/malloc.cc
SRC_CC  += lx_kit/irq.cc
SRC_CC  += lx_kit/scheduler.cc
SRC_CC  += lx_kit/timer.cc
SRC_CC  += lx_kit/work.cc
SRC_CC  += lx_kit/spec/arm_64/platform.cc
SRC_S   += lx_kit/spec/arm_64/setjmp.S
INC_DIR += $(REP_DIR)/src/include
INC_DIR += $(REP_DIR)/src/include/spec/arm_64
INC_DIR += $(REP_DIR)/src/include/lx_emul/shadow

vpath % $(REP_DIR)/src/lib


#
# Linux kernel definitions
#

CONTRIB_DIR := $(call select_from_ports,imx8mq_gpu)/src/drivers/gpu/etnaviv

# include the generated header files
INC_DIR  += $(REP_DIR)/src/drivers/gpu/etnaviv/include/generated
INC_DIR  += $(REP_DIR)/src/drivers/gpu/etnaviv/include/generated/uapi

INC_DIR  += $(CONTRIB_DIR)/arch/arm64/include
INC_DIR  += $(CONTRIB_DIR)/arch/arm64/include/generated
INC_DIR  += $(CONTRIB_DIR)/include
INC_DIR  += $(CONTRIB_DIR)/
INC_DIR  += $(CONTRIB_DIR)/arch/arm64/include/uapi
INC_DIR  += $(CONTRIB_DIR)/arch/arm64/include/generated/uapi
INC_DIR  += $(CONTRIB_DIR)/include/uapi
INC_DIR  += $(CONTRIB_DIR)/include/generated/uapi
INC_DIR  += $(CONTRIB_DIR)/scripts/dtc/libfdt

CC_C_OPT += -std=gnu89 -include $(CONTRIB_DIR)/include/linux/kconfig.h
CC_C_OPT += -D__KERNEL__ -DCONFIG_CC_HAS_K_CONSTRAINT=1
CC_C_OPT += -DKASAN_SHADOW_SCALE_SHIFT=3
CC_C_OPT += -Wall -Wundef -Werror=strict-prototypes -Wno-trigraphs
#CC_C_OPT += -Werror=implicit-function-declaration -Werror=implicit-int
CC_C_OPT += -Wno-format-security -Wno-psabi
CC_C_OPT += -Wno-frame-address -Wno-format-truncation -Wno-format-overflow
CC_C_OPT += -Wframe-larger-than=2048 -Wno-unused-but-set-variable -Wimplicit-fallthrough
CC_C_OPT += -Wno-unused-const-variable -Wdeclaration-after-statement -Wvla
CC_C_OPT += -Wno-pointer-sign -Wno-stringop-truncation -Wno-array-bounds -Wno-stringop-overflow
CC_C_OPT += -Wno-restrict -Wno-maybe-uninitialized -Werror=date-time
CC_C_OPT += -Werror=incompatible-pointer-types -Werror=designated-init
CC_C_OPT += -Wno-packed-not-aligned

CC_CXX_OPT += -include $(CONTRIB_DIR)/include/linux/kconfig.h \
              -D__KERNEL__ -DCONFIG_CC_HAS_K_CONSTRAINT=1 -DKASAN_SHADOW_SCALE_SHIFT=3

CC_CXX_WARN_STRICT :=

LX_OBJECTS_dma := \
                  $(CONTRIB_DIR)/drivers/dma-buf/dma-buf.o \
                  $(CONTRIB_DIR)/drivers/dma-buf/dma-fence.o \
                  $(CONTRIB_DIR)/drivers/dma-buf/dma-resv.o
LX_OBJECTS += $(LX_OBJECTS_dma)

LX_OBJECTS_drm := \
                  $(CONTRIB_DIR)/drivers/gpu/drm/drm_gem.o \
                  $(CONTRIB_DIR)/drivers/gpu/drm/drm_mm.o \
                  $(CONTRIB_DIR)/drivers/gpu/drm/drm_of.o \
                  $(CONTRIB_DIR)/drivers/gpu/drm/drm_vma_manager.o \
                  $(CONTRIB_DIR)/drivers/gpu/drm/drm_prime.o \
                  $(CONTRIB_DIR)/drivers/gpu/drm/drm_ioctl.o
LX_OBJECTS += $(LX_OBJECTS_drm)

LX_OBJECTS += $(CONTRIB_DIR)/drivers/base/component.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/base/devres.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/scheduler/sched_entity.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/scheduler/sched_fence.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/scheduler/sched_main.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_buffer.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_cmd_parser.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_cmdbuf.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_drv.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_dump.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_gem.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_gem_prime.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_gem_submit.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_gpu.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_hwdb.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_iommu.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_iommu_v2.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_mmu.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_perfmon.o
LX_OBJECTS += $(CONTRIB_DIR)/drivers/gpu/drm/etnaviv/etnaviv_sched.o
LX_OBJECTS += $(CONTRIB_DIR)/lib/idr.o
LX_OBJECTS += $(CONTRIB_DIR)/lib/rbtree.o
LX_OBJECTS += $(CONTRIB_DIR)/lib/radix-tree.o
LX_OBJECTS += $(CONTRIB_DIR)/lib/string.o
LX_OBJECTS += $(CONTRIB_DIR)/lib/sort.o
LX_OBJECTS += $(CONTRIB_DIR)/lib/bitmap.o
LX_OBJECTS += $(CONTRIB_DIR)/lib/refcount.o
LX_OBJECTS += $(CONTRIB_DIR)/lib/scatterlist.o
LX_OBJECTS += $(CONTRIB_DIR)/lib/hexdump.o
LX_OBJECTS += $(CONTRIB_DIR)/lib/ctype.o
LX_OBJECTS += $(CONTRIB_DIR)/lib/find_bit.o
LX_OBJECTS += $(CONTRIB_DIR)/kernel/time/time.o
LX_ASM      = $(wildcard $(CONTRIB_DIR)/arch/arm64/lib/mem*.S)
LX_ASM     += $(wildcard $(CONTRIB_DIR)/arch/arm64/lib/str*.S)

LX_REL_OBJ = $(LX_OBJECTS:$(CONTRIB_DIR)/%=%)
SRC_C     += $(LX_REL_OBJ:%.o=%.c)
SRC_S     += $(LX_ASM:$(CONTRIB_DIR)/%=%)

define CC_OPT_LX_RULES =
CC_OPT_$(1) = -DKBUILD_MODFILE='"$(1)"' -DKBUILD_BASENAME='"$(notdir $(1))"' -DKBUILD_MODNAME='"$(notdir $(1))"'
endef

$(foreach file,$(LX_REL_OBJ),$(eval $(call CC_OPT_LX_RULES,$(file:%.o=%))))

vpath %.c $(CONTRIB_DIR)
vpath %.S $(CONTRIB_DIR)
