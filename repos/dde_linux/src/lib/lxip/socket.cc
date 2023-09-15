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


genode_socket_handle *
genode_socket(int domain, int type, int protocol, enum Errno *errno)
{
	genode_socket_handle *handle = new (Lx_kit::env().heap) genode_socket_handle();

	handle->task  = lx_socket_dispatch_root();
	handle->queue = static_cast<Socket_queue *>(lx_socket_dispatch_queue());

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
