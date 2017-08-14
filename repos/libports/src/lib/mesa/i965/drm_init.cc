#include <../include/util/list.h>
#include <base/env.h>

extern "C" {
#include <platform.h>
}

extern void drm_init(Genode::Env &env);

void genode_drm_init()
{
	drm_init(*genode_env);
}
