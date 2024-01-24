#include <base/component.h>
#include <genode_c_api/socket.h>

using namespace Genode;


void Component::construct(Env & env)
{
	genode_socket_init(genode_env_ptr(env), nullptr);

	genode_socket_config address_config { };
	address_config.dhcp = true;
	genode_socket_address(&address_config);
}
