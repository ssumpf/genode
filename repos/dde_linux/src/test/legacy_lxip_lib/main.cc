#include <base/component.h>
#include <base/allocator.h>
#include <timer_session/connection.h>
#include <lx.h>

#include <legacy/lx_kit/env.h>
#include <legacy/lx_kit/malloc.h>


using namespace Genode;

static void poll_all()
{
	Genode::warning("poll_all");
}

struct Main
{
	Timer::Connection timer;

	Main(Env       &env)
	: timer(env, "lxip")
	{
		Lx_kit::Env &lx_env = Lx_kit::construct_env(env);

		Lx::lxcc_emul_init(lx_env);
		Lx::malloc_init(env, lx_env.heap());
		Lx::timer_init(env.ep(), timer, lx_env.heap(), &poll_all);
		Lx::nic_client_init(env, lx_env.heap(), &poll_all);

		lxip_init();
		lxip_configure_dhcp();
	}
};

void Component::construct(Env & env)
{
	static Main main { env };
}
