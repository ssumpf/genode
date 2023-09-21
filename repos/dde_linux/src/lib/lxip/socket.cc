#include <base/log.h>
#include <util/fifo.h>

#include <lx_kit/env.h>
#include <lx_emul/task.h>

#include "lx_socket.h"
#include "lx_user.h"


using namespace Genode;

struct Lx_call;

typedef Fifo<Lx_call> Socket_queue;


struct genode_socket_handle
{
	struct socket      *sock  { nullptr };
	struct task_struct *task  { nullptr };
	Socket_queue       *queue { };
};


void genode_socket_wait_for_progress()
{
	Lx_kit::env().env.ep().wait_and_dispatch_one_io_signal();
	Lx_kit::env().scheduler.execute();
}


struct Lx_call : private Socket_queue::Element
{
	friend class Fifo<Lx_call>;

	genode_socket_handle &handle;

	enum Errno err { GENODE_ENONE };
	bool finished  { false };

	Lx_call(genode_socket_handle &handle)
	: handle(handle) { }

	virtual ~Lx_call() { }

	/* called from ep */
	void schedule()
	{
		handle.queue->enqueue(*this);

		lx_emul_task_unblock(handle.task);
		Lx_kit::env().scheduler.execute();

		while (!finished) {
			warning("EP returned unfinished");
			genode_socket_wait_for_progress();
		}
		warning("EP finished");
	}

	virtual void execute() = 0;
};


struct Lx_socket : Lx_call
{
	int domain, type, protocol;

	Lx_socket(genode_socket_handle &handle, int domain, int type, int protocol)
	: Lx_call(handle), domain(domain), type(type), protocol(protocol)
	{
		schedule();
	}

	/* called from root dispatch task */
	void execute() override
	{
		err = lx_socket_create(domain, type, protocol, &handle.sock);
		finished = true;
	}
};


struct Lx_bind : Lx_call
{
	genode_sockaddr const &addr;

	Lx_bind(genode_socket_handle &handle, genode_sockaddr const &addr)
	: Lx_call(handle), addr(addr)
	{
		schedule();
	}

	void execute() override
	{
		err = lx_socket_bind(handle.sock, &addr);
		finished = true;
	}
};


struct Lx_listen : Lx_call
{
	int length;

	Lx_listen(genode_socket_handle &handle, int length)
	: Lx_call(handle), length(length)
	{
		schedule();
	}

	void execute() override
	{
		err = lx_socket_listen(handle.sock, length);
		finished = true;
	}
};


struct Lx_accept : Lx_call
{
	genode_socket_handle &client;
	genode_sockaddr addr { };

	Lx_accept(genode_socket_handle &handle,
	          genode_socket_handle &client)
	: Lx_call(handle), client(client)
	{
		schedule();
	}

	void execute() override
	{
		client.sock = lx_sock_alloc();
		if (!client.sock) {
			err = GENODE_ENOMEM;
			finished = true;
			return;
		}

		err = lx_socket_accept(handle.sock, client.sock, &addr);
		if (err)
			lx_sock_release(client.sock);

		finished = true;
	}
};


struct Lx_connect : Lx_call
{
	genode_sockaddr &addr;

	Lx_connect(genode_socket_handle &handle,
	           genode_sockaddr &addr)
	: Lx_call(handle), addr(addr)
	{
		schedule();
	}

	void execute() override
	{
		err = lx_socket_connect(handle.sock, &addr);
		finished = true;
	}
};


struct Lx_poll : Lx_call
{
	unsigned result = 0;

	Lx_poll(genode_socket_handle &handle)
	: Lx_call(handle)
	{
		schedule();
	}

	void execute() override
	{
		result = lx_socket_poll(handle.sock);
		finished = true;
	}
};


struct Lx_getsockopt : Lx_call
{
	enum Sock_level level;
	enum Sock_opt   opt;
	void           *optval;
	unsigned       *optlen;

	Lx_getsockopt(genode_socket_handle &handle,
	              enum Sock_level level,
	              enum Sock_opt opt,
	              void *optval, unsigned *optlen)
	: Lx_call(handle), level(level), opt(opt), optval(optval), optlen(optlen)
	{
		schedule();
	}

	void execute() override
	{
		err = lx_socket_getsockopt(handle.sock, level, opt, optval, optlen);
		finished = true;
	}

	Lx_getsockopt(const Lx_getsockopt&) = delete;
	Lx_getsockopt operator=(const Lx_getsockopt&) = delete;
};


struct Lx_sendmsg : Lx_call
{
	genode_msghdr &msg;
	unsigned long bytes { 0 };

	Lx_sendmsg(genode_socket_handle &handle,
	           genode_msghdr &msg)
	: Lx_call(handle), msg(msg)
	{
		schedule();
	}

	void execute() override
	{
		err = lx_socket_sendmsg(handle.sock, &msg, &bytes);
		finished = true;
	}
};


struct Lx_recvmsg : Lx_call
{
	genode_msghdr &msg;
	unsigned long bytes { 0 };

	Lx_recvmsg(genode_socket_handle &handle,
	           genode_msghdr &msg)
	: Lx_call(handle), msg(msg)
	{
		schedule();
	}

	void execute() override
	{
		err = lx_socket_recvmsg(handle.sock, &msg, &bytes);
		finished = true;
	}
};


struct Lx_shutdown : Lx_call
{
	int how;

	Lx_shutdown(genode_socket_handle &handle,
	            int how)
	: Lx_call(handle), how(how)
	{
		schedule();
	}

	void execute() override
	{
		err = lx_socket_shutdown(handle.sock, how);
		finished = true;
	}
};


struct Lx_release : Lx_call
{
	Lx_release(genode_socket_handle &handle) : Lx_call(handle)
	{
		schedule();
	}

	void execute() override
	{
		err = lx_socket_release(handle.sock);
		finished = true;
	}
};


void *lx_socket_dispatch_queue(void)
{
	static Socket_queue queue;
	return &queue;
}


int lx_socket_dispatch(void *arg)
{
	Socket_queue &queue = *static_cast<Socket_queue *>(arg);

	while (true) {

		if (queue.empty())
			lx_emul_task_schedule(true);

		queue.dequeue([] (Lx_call &call) { call.execute(); });
	}
}


static genode_socket_handle * _create_handle()
{
	genode_socket_handle *handle = new (Lx_kit::env().heap) genode_socket_handle();

	handle->task  = lx_socket_dispatch_root();
	handle->queue = static_cast<Socket_queue *>(lx_socket_dispatch_queue());
	handle->sock  = nullptr;

	return handle;
}


static void _destroy_handle(genode_socket_handle *handle)
{
	if (handle->sock) lx_sock_release(handle->sock);

	destroy(Lx_kit::env().heap, handle);
}


genode_socket_handle *
genode_socket(int domain, int type, int protocol, enum Errno *errno)
{
	genode_socket_handle *handle  = _create_handle();

	if (!handle) {
		*errno = GENODE_ENOMEM;
		return nullptr;
	}

	Lx_socket socket { *handle, domain, type, protocol };

	*errno = socket.err;

	return handle;
}


enum Errno genode_socket_bind(struct genode_socket_handle  *handle,
                              struct genode_sockaddr const *addr)
{
	Lx_bind bind { *handle, *addr };
	return bind.err;
}


enum Errno genode_socket_listen(struct genode_socket_handle *handle,
                                int backlog)
{
	Lx_listen listen { *handle, backlog };
	return listen.err;
}


genode_socket_handle *
genode_socket_accept(struct genode_socket_handle *handle,
                     struct genode_sockaddr *addr,
                     enum Errno *errno)
{
	genode_socket_handle *client = _create_handle();
	if (!handle) {
		*errno = GENODE_ENOMEM;
		return nullptr;
	}

	Lx_accept accept { *handle, *client };
	*errno = accept.err;

	if (*errno) {
		_destroy_handle(client);
		return nullptr;
	}

	if (addr)
		*addr = accept.addr;

	return client;
}


enum Errno genode_socket_connect(struct genode_socket_handle *handle,
                                 struct genode_sockaddr *addr)
{
	Lx_connect connect  { *handle, *addr };
	return connect.err;
}


unsigned genode_socket_pollin_set(void)
{
	return lx_socket_pollin_set();
}


unsigned genode_socket_pollout_set(void)
{
	return lx_socket_pollout_set();
}


unsigned genode_socket_pollex_set(void)
{
	return lx_socket_pollex_set();
}


unsigned genode_socket_poll(struct genode_socket_handle *handle)
{
	Lx_poll poll { *handle };
	return poll.result;
}


enum Errno genode_socket_getsockopt(struct genode_socket_handle *handle,
                                    enum Sock_level level, enum Sock_opt opt,
                                    void *optval, unsigned *optlen)
{
	Lx_getsockopt sock_opt { *handle, level, opt, optval, optlen };
	return sock_opt.err;
}


enum Errno genode_socket_sendmsg(struct genode_socket_handle *handle,
                                 struct genode_msghdr *msg,
                                 unsigned long *bytes_send)
{
	Lx_sendmsg send { *handle, *msg };
	*bytes_send = send.bytes;
	return send.err;
}


enum Errno genode_socket_recvmsg(struct genode_socket_handle *handle,
                                 struct genode_msghdr *msg,
                                 unsigned long *bytes_recv)
{
	Lx_recvmsg recv { *handle, *msg };
	*bytes_recv = recv.bytes;
	return recv.err;
}


enum Errno genode_socket_shutdown(struct genode_socket_handle *handle,
                                  int how)
{
	Lx_shutdown shutdown { *handle, how };
	return shutdown.err;
}


enum Errno genode_socket_release(struct genode_socket_handle *handle)
{
	Lx_release release { *handle };
	handle->sock = nullptr;
	_destroy_handle(handle);
	return release.err;
}
