#include <libc/component.h>
#include <window.h>

static Genode::Env *_env;

void Window::sync_handler() { }
void Window::mode_handler() { }


Genode::Env &genode_env()
{
	return *_env;
}

extern "C" int ioq3_main(int argc, char *argv[]);
extern void drm_init(Genode::Env &env);


void Libc::Component::construct(Libc::Env &env)
{
	_env = &env;

	//XXX: does not work for swrast
	drm_init(env);

	Libc::with_libc([] () { ioq3_main(1, nullptr); });
}
