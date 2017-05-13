#include <libc/component.h>
#include <window.h>
#include <os/backtrace.h>

static Genode::Env *_env;

void Window::sync_handler() { }
void Window::mode_handler() { }

extern "C" void genode_backtrace()
{
	Genode::backtrace();
}


Genode::Env &genode_env()
{
	return *_env;
}

extern "C" int ioq3_main(int argc, char *argv[]);
extern void drm_init(Genode::Env &env);

Genode::size_t Libc::Component::stack_size() { return 1024UL*1024*sizeof(long); }

void Libc::Component::construct(Libc::Env &env)
{
	_env = &env;

	//XXX: does not work for swrast

	static char *argv[] = { "ioq3" };
	Libc::with_libc([] () { ioq3_main(1, argv); });
}
