include $(REP_DIR)/lib/mk/ioq3.inc

CC_OPT += -DBOTLIB
SRC_C   = code/botlib/be_aas_bspq3.c \
          code/botlib/be_aas_cluster.c \
          code/botlib/be_aas_debug.c \
          code/botlib/be_aas_entity.c \
          code/botlib/be_aas_file.c \
          code/botlib/be_aas_main.c \
          code/botlib/be_aas_move.c \
          code/botlib/be_aas_optimize.c \
          code/botlib/be_aas_reach.c \
          code/botlib/be_aas_route.c \
          code/botlib/be_aas_routealt.c \
          code/botlib/be_aas_sample.c \
          code/botlib/be_ai_char.c \
          code/botlib/be_ai_chat.c \
          code/botlib/be_ai_gen.c \
          code/botlib/be_ai_goal.c \
          code/botlib/be_ai_move.c \
          code/botlib/be_ai_weap.c \
          code/botlib/be_ai_weight.c \
          code/botlib/be_ea.c \
          code/botlib/be_interface.c \
          code/botlib/l_crc.c \
          code/botlib/l_libvar.c \
          code/botlib/l_log.c \
          code/botlib/l_memory.c \
          code/botlib/l_precomp.c \
          code/botlib/l_script.c \
          code/botlib/l_struct.c
