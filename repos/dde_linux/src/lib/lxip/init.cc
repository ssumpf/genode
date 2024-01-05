#include <lx_kit/env.h>
#include <lx_emul/init.h>
#include <lx_emul/task.h>

#include <genode_c_api/nic_client.h>
#include <genode_c_api/socket.h>

#include "init.h"
#include "lx_user.h"
#include "net_driver.h"


using namespace Genode;

struct Main
{
	Env &env;
	genode_socket_io_progress *io_progress;

	Signal_handler<Main> schedule_handler   { env.ep(), *this,
		&Main::handle_schedule };

	Io_signal_handler<Main> nic_client_handler { env.ep(), *this,
		&Main::handle_nic_client };

	Main(Env &env, genode_socket_io_progress *io_progress)
	: env(env), io_progress(io_progress)
	{ }

	void handle_schedule()
	{
		Lx_kit::env().scheduler.execute();

		if (io_progress && io_progress->callback)
			io_progress->callback(io_progress->data);
	}

	void handle_nic_client()
	{

		lx_emul_task_unblock(lx_nic_client_rx_task());
		Lx_kit::env().scheduler.execute();

		if (io_progress && io_progress->callback)
			io_progress->callback(io_progress->data);
	}

	void kernel_initialized()
	{
		if (!io_progress || !io_progress->initialized_callback) return;
		io_progress->initialized_callback(io_progress->initialized_data);
	}

	void init()
	{
		genode_nic_client_init(genode_env_ptr(env),
		                       genode_allocator_ptr(Lx_kit::env().heap),
		                       genode_signal_handler_ptr(nic_client_handler));
	}

	Main(const Main&) = delete;
	Main operator=(const Main&) = delete;
};


static Main &_main(Env *env = nullptr, genode_socket_io_progress *io_progress = nullptr)
{
	static Main main { *env, io_progress };
	return main;
}


/* detect if static constructors have been called */
static bool _constructors_called = false;
static bool _initialized         = false;

bool lx_emul_socket_constructors_called()
{
	return _constructors_called;
}


bool lx_emul_socket_initialized()
{
	return _initialized;
}


static void __attribute__((constructor)) static_constructor()
{
	_constructors_called = true;
}


void lx_emul_socket_start_kernel()
{
	_main().init();

	/* must be called before initcalls */
	lx_user_configure_ip_stack();

	lx_emul_start_kernel(nullptr);

	/* wait to finish initialization before returning to callee */
	lx_emul_execute_kernel_until(lx_user_startup_complete, nullptr);

	_initialized = true;
	_main().kernel_initialized();
}


void genode_socket_init(struct genode_env *_env,
                        bool exec_static_constructors,
                        struct genode_socket_io_progress *io_progress)
{
	Env *env = static_cast<Env *>(_env);

	Main &main = _main(env, io_progress);

	Lx_kit::initialize(*env, main.schedule_handler);

	if (!exec_static_constructors) return;

	env->exec_static_constructors();

	lx_emul_socket_start_kernel();
}
