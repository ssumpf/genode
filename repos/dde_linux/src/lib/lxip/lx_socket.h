#ifdef __cplusplus
extern "C" {
#endif

#include <genode_c_api/socket.h>

enum Errno lx_socket_create(int domain, int type, int protocol, struct socket **res);
enum Errno lx_socket_bind(struct socket *sock, struct genode_sockaddr const *addr);
enum Errno lx_socket_listen(struct socket *sock, int length);

#ifdef __cplusplus
} /* extern "C" */
#endif
