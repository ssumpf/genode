#include <base/heap.h>
#include <base/printf.h>

extern "C" {
#include "eglutint.h"
}

#include <window.h>
#include <platform.h>

//XXX: dde_linux internals, remove
#include <lx_kit/scheduler.h>

Genode::Env *genode_env;
Lx::Task    *event_loop_task;


struct Env
{
	Genode::Env                   &env;
	Genode::Heap                   heap { env.ram(), env.rm() };
	Genode::Attached_rom_dataspace config { env, "config" };

	Env(Genode::Env &env) : env(env) { }
};


static Env *_e;
static bool initialized = false;

void _eglutNativeInitDisplay()
{
	_eglut->surface_type = EGL_WINDOW_BIT;
}

#if 0
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
#endif

void Window::sync_handler()
{
	PDBG("SYNC");
	event_loop_task->unblock();
	Lx::scheduler().schedule();
}


void Window::mode_handler()
{
	PDBG("MODE: %p", framebuffer);

	if (!framebuffer) //.is_constructed())
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
	//Genode_egl_window *native = new (_e->heap) Window(_e->env, w, h);
	Genode_egl_window *native = new (_e->heap) Window(_e->env, w, h, _e->config);
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
	static unsigned long count = 0;
	while (true) {
		//_e->env.ep().wait_and_dispatch_one_signal();
		//_e->env.ep().dispatch_pending();

		struct eglut_window *win =_eglut->current;

		/* 50 Hz */
		if ((count++ % 2) && _eglut->idle_cb) {
			_eglut->idle_cb();
		}

		if (win->display_cb)
			win->display_cb();

		PDBG("event %u", initialized);

		if (initialized)
			eglSwapBuffers(_eglut->dpy, win->surface);

		/* needed for task scheduling */
		Window *native = (Window*)win->native.u.window;
		Genode::Signal_transmitter(native->sync_dispatcher).submit();
		PDBG("block");
		Lx::scheduler().current()->block_and_schedule();
	}
}


/*
 * 'eglut_main' will be called instead of 'main' by component initialization
 */
extern "C" int eglut_main(int argc, char *argv[]);


void run_task(void * /* data */)
{
	PDBG("START task");
	/* wait for signal from intel driver */
	Lx::scheduler().current()->block_and_schedule();
	eglut_main(1, nullptr);
}


void start_framebuffer_driver(Genode::Env &env, Lx::Task &task, Genode::Signal_context_capability);
/*
 * Use as component, so signals can be dispatched easily
 */

struct Signal_schedule_helper
{
	Genode::Signal_handler<Signal_schedule_helper> handler;

	Signal_schedule_helper(Genode::Entrypoint &ep)
	: handler(ep, *this, &Signal_schedule_helper::dispatch) { }

	void dispatch() {
		PDBG("DISPATCH");
		event_loop_task->unblock();
		Lx::scheduler().schedule(); }
};


namespace Component {
	Genode::size_t stack_size()      { return  4096 * sizeof(long); }

	void construct(Genode::Env &env)
	{
		static Env e(env);
		_e = &e;
		genode_env = &env;

		static Signal_schedule_helper startup_helper(env.ep());

		static Lx::Task task(run_task, nullptr, "eglut_main", Lx::Task::PRIORITY_0,
		                     Lx::scheduler());

		//XXX: remove me
		start_framebuffer_driver(env, task, startup_helper.handler);
		event_loop_task = &task;

		Lx::scheduler().schedule();

	}
}
