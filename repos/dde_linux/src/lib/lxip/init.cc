#include <lx_kit/env.h>
#include <lx_emul/init.h>
#include <lx_emul/task.h>

#include <genode_c_api/nic_client.h>

#include <lxip.h>
#include "net_driver.h"


using namespace Genode;

struct Main
{
	Env &env;

	Signal_handler<Main> schedule_handler   { env.ep(), *this,
		&Main::handle_schedule };

	Signal_handler<Main> nic_client_handler { env.ep(), *this,
		&Main::handle_nic_client };

	Main(Env &env) : env(env) { }

	void handle_schedule()
	{
		Lx_kit::env().scheduler.execute();
	}

	void handle_nic_client()
	{
		lx_emul_task_unblock(lx_nic_client_rx_task());
		Lx_kit::env().scheduler.execute();
	}

	void init()
	{
		genode_nic_client_init(genode_env_ptr(env),
		                       genode_allocator_ptr(Lx_kit::env().heap),
		                       genode_signal_handler_ptr(nic_client_handler));
	}
};

extern "C" void wait_for_continue(void);

void Lxip::construct(Env &env)
{
	static Main main { env };

	log("WAIT");
	wait_for_continue();

	log("Lx_kit::initialize");
	Lx_kit::initialize(env, main.schedule_handler);

	log("exec_static_constructors");
	env.exec_static_constructors();

	main.init();

	log("lx_emul_start_kernel");
	lx_emul_start_kernel(nullptr);
}
