TARGET             := tcp_stress_server

LIBS               += stdcxx
LIBS               += libc_pipe
LIBS               += vfs
LIBS               += vfs_lwip

CC_CXX_WARN_STRICT :=

SRC_CC             := main.cc
SRC_CC             += tcp_server.cc

