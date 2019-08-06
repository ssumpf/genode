HOST_INC_DIR += /usr/arm-linux-gnueabi/include

# needed for Ubuntu >= 11.04
HOST_INC_DIR += /usr/arm-linux-gnueabi/include/$(shell /usr/local/genode/tool/current/bin/genode-arm-gcc -dumpmachine)

#
# Some header files installed on GNU/Linux test for the GNU compiler. For
# example, 'stdio.h' might complain with the following error otherwise:
#
#  /usr/include/stdio.h:432:27: error: expected initializer before ‘throw’
#  /usr/include/stdio.h:488:6: error: expected initializer before ‘throw’
#
# By manually defining '_GNU_SOURCE', the header files are processed as
# expected.
#
CC_OPT += -D_GNU_SOURCE

