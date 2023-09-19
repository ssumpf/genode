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
			Lx_kit::env().env.ep().wait_and_dispatch_one_io_signal();
			Lx_kit::env().scheduler.execute();
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
	Flags flags;
	genode_sockaddr addr { };

	Lx_accept(genode_socket_handle &handle,
	          genode_socket_handle &client,
	          Flags flags)
	: Lx_call(handle), client(client), flags(flags)
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

		err = lx_socket_accept(handle.sock, client.sock, &addr, flags);
		finished = true;
	}
};



struct Lx_connect : Lx_call
{
	genode_sockaddr &addr;
	Flags flags;

	Lx_connect(genode_socket_handle &handle,
	           genode_sockaddr &addr, enum Flags flags)
	: Lx_call(handle), addr(addr), flags(flags)
	{
		schedule();
	}


	void execute() override
	{
		err = lx_socket_connect(handle.sock, &addr,flags);
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
                     enum Flags flags, enum Errno *errno)
{

	genode_socket_handle *client = _create_handle();
	if (!handle) {
		*errno = GENODE_ENOMEM;
		return nullptr;
	}

	Lx_accept accept { *handle, *client, flags };
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
                                 struct genode_sockaddr *addr,
                                 enum Flags flags)
{
	Lx_connect connect  { *handle, *addr, flags };
	return connect.err;
}
