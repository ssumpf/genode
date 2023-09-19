#include <base/component.h>
#include <genode_c_api/socket.h>

using namespace Genode;

struct Main
{
	Main(Env &env)
	{
		Genode::log("CONTRUCT LXIP");
		genode_socket_init(genode_env_ptr(env));
	}
};

void Component::construct(Env & env)
{
	static Main main { env };
}
