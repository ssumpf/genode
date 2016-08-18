#include <base/heap.h>
#include <base/printf.h>

extern "C" {
#include "eglutint.h"
}

#include <window.h>


struct Env
{
	Genode::Env &env;
	Genode::Heap heap { env.ram(), env.rm() };

	Env(Genode::Env &env) : env(env) { }
};


static Env *_e;


void _eglutNativeInitDisplay()
{
	_eglut->surface_type = EGL_WINDOW_BIT;
}


void Window::sync_handler()
{
	struct eglut_window *win =_eglut->current;

	static unsigned long count = 0;

	/* 50 Hz */
	if ((count++ % 2) && _eglut->idle_cb) {
		_eglut->idle_cb();
		return;
	}

	if (win->display_cb)
		win->display_cb();

	eglSwapBuffers(_eglut->dpy, win->surface);
}


void Window::mode_handler()
{
	if (!framebuffer.is_constructed())
		return;

	Framebuffer::Mode mode = framebuffer->mode();

	eglut_window *win  = _eglut->current;
	win->native.width  = mode.width();
	win->native.height = mode.height();

	if (win->reshape_cb)
		win->reshape_cb(win->native.width, win->native.height);
}


void _eglutNativeFiniDisplay(void)
{
	PDBG("not implemented");
}


void _eglutNativeInitWindow(struct eglut_window *win, const char *title,
                            int x, int y, int w, int h)
{
	Genode_egl_window *native = new (_e->heap) Window(_e->env, w, h);
	win->native.u.window = native;
	win->native.width = w;
	win->native.height = h;
}


void _eglutNativeFiniWindow(struct eglut_window *win)
{
	PDBG("not implemented");
}


void _eglutNativeEventLoop()
{
	while (true) {
		_e->env.ep().wait_and_dispatch_one_signal();
	}
}


/*
 * 'eglut_main' will be called instead of 'main' by component initialization
 */
extern "C" int eglut_main(int argc, char *argv[]);


/*
 * Use as component, so signals can be dispatched easily
 */
namespace Component {
	Genode::size_t stack_size()      { return  4096 * sizeof(long); }

	void construct(Genode::Env &env)
	{
		static Env e(env);
		_e = &e;

		eglut_main(1, nullptr);
	}
}
