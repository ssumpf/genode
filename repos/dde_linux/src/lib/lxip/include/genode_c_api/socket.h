#include <base/fixed_stdint.h>
#include <genode_c_api/base.h>

#ifdef __cplusplus
extern "C" {
#endif

enum Errno {
	GENODE_ENONE = 0,
	GENODE_E2BIG = 1,
	GENODE_EACCES = 2,
	GENODE_EADDRINUSE = 3,
	GENODE_EADDRNOTAVAIL = 4,
	GENODE_EAFNOSUPPORT = 5,
	GENODE_EAGAIN = 6,
	GENODE_EALREADY = 7,
	GENODE_EBADF = 8,
	GENODE_EBADFD = 9,
	GENODE_EBADMSG = 10,
	GENODE_EBADRQC = 11,
	GENODE_EBUSY = 12,
	GENODE_ECONNABORTED = 13,
	GENODE_ECONNREFUSED = 14,
	GENODE_EDESTADDRREQ = 15,
	GENODE_EDOM = 16,
	GENODE_EEXIST = 17,
	GENODE_EFAULT = 18,
	GENODE_EFBIG = 19,
	GENODE_EHOSTUNREACH = 20,
	GENODE_EINPROGRESS = 21,
	GENODE_EINTR = 22,
	GENODE_EINVAL = 23,
	GENODE_EIO = 24,
	GENODE_EISCONN = 25,
	GENODE_ELOOP = 26,
	GENODE_EMLINK = 27,
	GENODE_EMSGSIZE = 28,
	GENODE_ENAMETOOLONG = 29,
	GENODE_ENETDOWN = 30,
	GENODE_ENETUNREACH = 31,
	GENODE_ENFILE = 32,
	GENODE_ENOBUFS = 33,
	GENODE_ENODATA = 34,
	GENODE_ENODEV = 35,
	GENODE_ENOENT = 36,
	GENODE_ENOIOCTLCMD = 37,
	GENODE_ENOLINK = 38,
	GENODE_ENOMEM = 39,
	GENODE_ENOMSG = 40,
	GENODE_ENOPROTOOPT = 41,
	GENODE_ENOSPC = 42,
	GENODE_ENOSYS = 43,
	GENODE_ENOTCONN = 44,
	GENODE_ENOTSUPP = 45,
	GENODE_ENOTTY = 46,
	GENODE_ENXIO = 47,
	GENODE_EOPNOTSUPP = 48,
	GENODE_EOVERFLOW = 49,
	GENODE_EPERM = 50,
	GENODE_EPFNOSUPPORT = 51,
	GENODE_EPIPE = 52,
	GENODE_EPROTO = 53,
	GENODE_EPROTONOSUPPORT = 54,
	GENODE_EPROTOTYPE = 55,
	GENODE_ERANGE = 56,
	GENODE_EREMCHG = 57,
	GENODE_ESOCKTNOSUPPORT = 58,
	GENODE_ESPIPE = 59,
	GENODE_ESRCH = 60,
	GENODE_ESTALE = 61,
	GENODE_ETIMEDOUT = 62,
	GENODE_ETOOMANYREFS = 63,
	GENODE_EUSERS = 64,
	GENODE_EXDEV = 65,
	GENODE_MAX_ERRNO = 66,
};

enum Sock_opt {
	GENODE_SO_DEBUG = 1,
	GENODE_SO_ACCEPTCONN = 2,
	GENODE_SO_DONTROUTE = 3,
	GENODE_SO_LINGER = 4,
	GENODE_SO_OOBINLINE = 5,
	GENODE_SO_REUSEPORT = 6,
	GENODE_SO_SNDBUF = 7,
	GENODE_SO_RCVBUF = 8,
	GENODE_SO_SNDLOWAT = 9,
	GENODE_SO_RCVLOWAT = 10,
	GENODE_SO_SNDTIMEO = 11,
	GENODE_SO_RCVTIMEO = 12,
	GENODE_SO_ERROR = 13,
	GENODE_SO_TYPE = 14,
	GENODE_SO_BINDTODEVICE = 15,
};

enum Sock_level {
	GENODE_SOL_SOCKET = 1,
};

struct genode_socket_handle;

struct genode_in_addr
{
	genode_uint32_t s_addr; /* be */
};

struct genode_sockaddr
{
	genode_uint16_t family;
	union {
		/* AF_INET (or IPv4) */
		struct {
			genode_uint16_t       sin_port; /* be */
			struct genode_in_addr sin_addr; /* be */
		} in;
	};
};


void genode_socket_init(struct genode_env *env);

void genode_socket_wait_for_progress(void);

struct genode_socket_handle *
genode_socket(int domain, int type, int protocol, enum Errno *);

enum Errno genode_socket_bind(struct genode_socket_handle *,
                              struct genode_sockaddr const *);

enum Errno genode_socket_listen(struct genode_socket_handle *,
                                int backlog);
/* non-blocking call */
struct genode_socket_handle *
genode_socket_accept(struct genode_socket_handle *,
                     struct genode_sockaddr *,
                     enum Errno *);

/* non-blocking call */
enum Errno genode_socket_connect(struct genode_socket_handle *,
                                 struct genode_sockaddr *);

/* poll */
unsigned genode_socket_pollin_set(void);
unsigned genode_socket_pollout_set(void);
unsigned genode_socket_pollex_set(void);

unsigned genode_socket_poll(struct genode_socket_handle *);

enum Errno genode_socket_getsockopt(struct genode_socket_handle *,
                                    enum Sock_level, enum Sock_opt,
                                    void *optval, unsigned *optlen);


struct genode_iovec
{
	void         *iov_base;
	unsigned long iov_size;
};


struct genode_msghdr
{
	struct genode_sockaddr *msg_name;   /* can be NULL for TCP    */
	struct genode_iovec    *msg_iov;    /* array of iovecs        */
	unsigned long           msg_iovlen; /* nr elements in msg_iov */
};

/* non-blocking call */
enum Errno genode_socket_sendmsg(struct genode_socket_handle *,
                                 struct genode_msghdr *,
                                 unsigned long *bytes_send);
/* non-blocking call
 * XXX: we might need MSG_PEEK support
 */
enum Errno genode_socket_recvmsg(struct genode_socket_handle *,
                                 struct genode_msghdr *,
                                 unsigned long *bytes_recv);

enum Errno genode_socket_shutdown(struct genode_socket_handle *,
                                  int how);

enum Errno genode_socket_release(struct genode_socket_handle *);

#ifdef __cplusplus
} /* extern "C" */
#endif
