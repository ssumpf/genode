include ioq3.inc

CC_OPT += -DDEDICATED
SRC_C   = code/server/sv_bot.c \
          code/server/sv_client.c \
          code/server/sv_ccmds.c \
          code/server/sv_game.c \
          code/server/sv_init.c \
          code/server/sv_main.c \
          code/server/sv_net_chan.c \
          code/server/sv_snapshot.c \
          code/server/sv_world.c \
          code/qcommon/cm_load.c \
          code/qcommon/cm_patch.c \
          code/qcommon/cm_polylib.c \
          code/qcommon/cm_test.c \
          code/qcommon/cm_trace.c \
          code/qcommon/cmd.c \
          code/qcommon/common.c \
          code/qcommon/cvar.c \
          code/qcommon/files.c \
          code/qcommon/md4.c \
          code/qcommon/msg.c \
          code/qcommon/net_chan.c \
          code/qcommon/net_ip.c \
          code/qcommon/huffman.c \
          code/qcommon/q_math.c \
          code/qcommon/q_shared.c \
          code/qcommon/unzip.c \
          code/qcommon/ioapi.c \
          code/qcommon/vm.c \
          code/qcommon/vm_interpreted.c \
          code/zlib/adler32.c \
          code/zlib/crc32.c \
          code/zlib/inffast.c \
          code/zlib/inflate.c \
          code/zlib/inftrees.c \
          code/zlib/zutil.c \
          code/qcommon/vm_x86_64.c \
          code/qcommon/vm_x86_64_assembler.c \
          code/sys/sys_unix.c \
          code/sys/con_tty.c
