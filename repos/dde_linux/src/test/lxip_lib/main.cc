#include <base/component.h>

#include <lxip.h>

using namespace Genode;

struct Main
{
	Main(Env &env)
	{
		Genode::log("CONTRUCT LXIP");
		Lxip::construct(env);
	}
};

void Component::construct(Env & env)
{
	static Main main { env };
}
