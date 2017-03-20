#include <base/heap.h>
#include <base/printf.h>
#include <libc/component.h>

extern "C" {
#include "eglutint.h"
#include <sys/select.h>
}

#include <window.h>
#include <platform.h>

static bool initialized = false;

struct Eglut_env
{
	Libc::Env &env;
	Genode::Heap heap { env.ram(), env.rm() };

	Eglut_env(Libc::Env &env) : env(env) { }
};

Genode::Constructible<Eglut_env> eglut_env;

void _eglutNativeInitDisplay()
{
	_eglut->surface_type = EGL_WINDOW_BIT;
}

void Window::sync_handler()
{
	PDBG("called");
#if 1
	struct eglut_window *win =_eglut->current;

	if (_eglut->idle_cb)
		_eglut->idle_cb();


	if (win->display_cb)
		win->display_cb();

	if (initialized) {
		eglSwapBuffers(_eglut->dpy, win->surface);
		//XXX: may be required
		eglWaitClient();
	}
#endif
}


void Window::mode_handler()
{
	PDBG("MODE: %p", framebuffer);

	if (!framebuffer.is_constructed())
		return;

	initialized = true;
	Framebuffer::Mode mode = framebuffer->mode();

	eglut_window *win  = _eglut->current;
	if (win) {
		win->native.width  = mode.width();
		win->native.height = mode.height();

		if (win->reshape_cb)
			win->reshape_cb(win->native.width, win->native.height);
	}

	update();
}


void _eglutNativeFiniDisplay(void)
{
	PDBG("not implemented");
}


void _eglutNativeInitWindow(struct eglut_window *win, const char *title,
                            int x, int y, int w, int h)
{
	Genode_egl_window *native = new (eglut_env->heap) Window(eglut_env->env, w, h);
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
		select(0, nullptr, nullptr, nullptr, nullptr);
	}
}


/*
 * 'eglut_main' will be called instead of 'main' by component initialization
 */
extern "C" int eglut_main(int argc, char *argv[]);
extern void drm_init(Genode::Env &env);


void Libc::Component::construct(Libc::Env &env)
{
	eglut_env.construct(env);

	//XXX: does not work for swrast
	drm_init(env);

	Libc::with_libc([] () { eglut_main(1, nullptr); });
}
