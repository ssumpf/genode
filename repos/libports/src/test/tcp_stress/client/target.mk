TARGET             := tcp_stress_client

LIBS               := posix
LIBS               += stdcxx
LIBS               += libc_pipe

CC_CXX_WARN_STRICT :=

SRC_CC             := tcp_client.cc

