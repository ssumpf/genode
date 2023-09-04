#include <lx_kit/env.h>
#include <lx_emul/init.h>

#include <lxip.h>

using namespace Genode;

struct Main
{
	Env &env;

	Signal_handler<Main> signal_handler { env.ep(), *this, &Main::handle_signal };

	Main(Env &env) : env(env) { }

	void handle_signal()
	{
		Lx_kit::env().scheduler.execute();
	}
};

extern "C" void wait_for_continue(void);

void Lxip::construct(Env &env)
{
	static Main main { env };

	log("WAIT");
	wait_for_continue();

	log("Lx_kit::initialize");
	Lx_kit::initialize(env, main.signal_handler);

	log("exec_static_constructors");
	env.exec_static_constructors();

	log("lx_emul_start_kernel");
	lx_emul_start_kernel(nullptr);
}
