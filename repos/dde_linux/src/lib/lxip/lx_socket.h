#ifdef __cplusplus
extern "C" {
#endif

#include <genode_c_api/socket.h>

struct socket *lx_sock_alloc(void);
void           lx_sock_release(struct socket* sock);

enum Errno lx_socket_create(int domain, int type, int protocol, struct socket **res);
enum Errno lx_socket_bind(struct socket *sock, struct genode_sockaddr const *addr);
enum Errno lx_socket_listen(struct socket *sock, int length);
enum Errno lx_socket_accept(struct socket *sock, struct socket *new_sock,
                            struct genode_sockaddr *addr);
enum Errno lx_socket_connect(struct socket *sock, struct genode_sockaddr const *addr);

unsigned lx_socket_pollin_set(void);
unsigned lx_socket_pollout_set(void);
unsigned lx_socket_pollex_set(void);
unsigned lx_socket_poll(struct socket *sock);

enum Errno lx_socket_getsockopt(struct socket *sock, enum Sock_level level,
                                enum Sock_opt opt, void *optval, unsigned *optlen);

#ifdef __cplusplus
} /* extern "C" */
#endif
