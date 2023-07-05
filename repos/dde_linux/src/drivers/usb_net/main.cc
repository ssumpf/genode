
#include <base/component.h>
#include <base/env.h>

#include <lx_kit/env.h>
#include <lx_emul/init.h>

using namespace Genode;

void Component::construct(Env & env)
{
	Lx_kit::initialize(env);

	env.exec_static_constructors();

	lx_emul_start_kernel(nullptr);
}
