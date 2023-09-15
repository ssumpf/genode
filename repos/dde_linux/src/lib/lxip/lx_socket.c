#include <linux/net.h>
#include <net/sock.h>

#include "lx_socket.h"

extern struct net init_net;


static enum Errno _genode_errno(int errno)
{
	switch (-errno) {
	case 0:               return GENODE_ENONE;
	case E2BIG:           return GENODE_E2BIG;
	case EACCES:          return GENODE_EACCES;
	case EADDRINUSE:      return GENODE_EADDRINUSE;
	case EADDRNOTAVAIL:   return GENODE_EADDRNOTAVAIL;
	case EAFNOSUPPORT:    return GENODE_EAFNOSUPPORT;
	case EAGAIN:          return GENODE_EAGAIN;
	case EALREADY:        return GENODE_EALREADY;
	case EBADF:           return GENODE_EBADF;
	case EBADFD:          return GENODE_EBADFD;
	case EBADMSG:         return GENODE_EBADMSG;
	case EBADRQC:         return GENODE_EBADRQC;
	case EBUSY:           return GENODE_EBUSY;
	case ECONNABORTED:    return GENODE_ECONNABORTED;
	case ECONNREFUSED:    return GENODE_ECONNREFUSED;
	case EDESTADDRREQ:    return GENODE_EDESTADDRREQ;
	case EDOM:            return GENODE_EDOM;
	case EEXIST:          return GENODE_EEXIST;
	case EFAULT:          return GENODE_EFAULT;
	case EFBIG:           return GENODE_EFBIG;
	case EHOSTUNREACH:    return GENODE_EHOSTUNREACH;
	case EINPROGRESS:     return GENODE_EINPROGRESS;
	case EINTR:           return GENODE_EINTR;
	case EINVAL:          return GENODE_EINVAL;
	case EIO:             return GENODE_EIO;
	case EISCONN:         return GENODE_EISCONN;
	case ELOOP:           return GENODE_ELOOP;
	case EMLINK:          return GENODE_EMLINK;
	case EMSGSIZE:        return GENODE_EMSGSIZE;
	case ENAMETOOLONG:    return GENODE_ENAMETOOLONG;
	case ENETDOWN:        return GENODE_ENETDOWN;
	case ENETUNREACH:     return GENODE_ENETUNREACH;
	case ENFILE:          return GENODE_ENFILE;
	case ENOBUFS:         return GENODE_ENOBUFS;
	case ENODATA:         return GENODE_ENODATA;
	case ENODEV:          return GENODE_ENODEV;
	case ENOENT:          return GENODE_ENOENT;
	case ENOIOCTLCMD:     return GENODE_ENOIOCTLCMD;
	case ENOLINK:         return GENODE_ENOLINK;
	case ENOMEM:          return GENODE_ENOMEM;
	case ENOMSG:          return GENODE_ENOMSG;
	case ENOPROTOOPT:     return GENODE_ENOPROTOOPT;
	case ENOSPC:          return GENODE_ENOSPC;
	case ENOSYS:          return GENODE_ENOSYS;
	case ENOTCONN:        return GENODE_ENOTCONN;
	case ENOTSUPP:        return GENODE_ENOTSUPP;
	case ENOTTY:          return GENODE_ENOTTY;
	case ENXIO:           return GENODE_ENXIO;
	case EOPNOTSUPP:      return GENODE_EOPNOTSUPP;
	case EOVERFLOW:       return GENODE_EOVERFLOW;
	case EPERM:           return GENODE_EPERM;
	case EPFNOSUPPORT:    return GENODE_EPFNOSUPPORT;
	case EPIPE:           return GENODE_EPIPE;
	case EPROTO:          return GENODE_EPROTO;
	case EPROTONOSUPPORT: return GENODE_EPROTONOSUPPORT;
	case EPROTOTYPE:      return GENODE_EPROTOTYPE;
	case ERANGE:          return GENODE_ERANGE;
	case EREMCHG:         return GENODE_EREMCHG;
	case ESOCKTNOSUPPORT: return GENODE_ESOCKTNOSUPPORT;
	case ESPIPE:          return GENODE_ESPIPE;
	case ESRCH:           return GENODE_ESRCH;
	case ESTALE:          return GENODE_ESTALE;
	case ETIMEDOUT:       return GENODE_ETIMEDOUT;
	case ETOOMANYREFS:    return GENODE_ETOOMANYREFS;
	case EUSERS:          return GENODE_EUSERS;
	case EXDEV:           return GENODE_EXDEV;
	default:
		printk("%s:%d unsupported errno %d\n",
		       __func__, __LINE__, errno);
	}
	return GENODE_EINVAL;
}


static struct sockaddr _sockaddr(struct genode_sockaddr const *addr)
{
	struct sockaddr sock_addr = { };

	if (addr->family == AF_INET) {
		struct sockaddr_in in_addr = {
			.sin_family      = AF_INET,
			.sin_port        = addr->in.sin_port,
			.sin_addr.s_addr = addr->in.sin_addr.s_addr
		};
		memcpy(&sock_addr, &in_addr, sizeof(in_addr));
	}

	return sock_addr;
}


static int _sockaddr_len(struct genode_sockaddr const *addr)
{
	if (addr->family == AF_INET)
		return sizeof(struct sockaddr_in);

	return 0;
}


enum Errno lx_socket_create(int domain, int type, int protocol,
                            struct socket **res)
{
	int err = sock_create_kern(&init_net, domain, type, protocol, res);
	if (err) return _genode_errno(err);

	init_waitqueue_head(&(*res)->wq.wait);

	return GENODE_ENONE;
}


enum Errno lx_socket_bind(struct socket *sock, struct genode_sockaddr const *addr)
{
	struct sockaddr sock_addr = _sockaddr(addr);
	return _genode_errno(sock->ops->bind(sock, &sock_addr, _sockaddr_len(addr)));
}
