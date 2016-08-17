#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <base/env.h>
#include <framebuffer_session/connection.h>
#include <util/volatile_object.h>

#include <EGL/eglplatform.h>

struct Window : Genode_egl_window
{
	Genode::Lazy_volatile_object<Framebuffer::Connection> framebuffer;
	Genode::Signal_handler<Window>                        sync_dispatcher;
	Genode::Signal_handler<Window>                        mode_dispatcher;

	Window(Genode::Env &env, int w, int h)
	: sync_dispatcher(env.ep(), *this, &Window::sync_handler),
	  mode_dispatcher(env.ep(), *this, &Window::mode_handler)
	  
	{
		width  = w;
		height = h;

		framebuffer.construct(width, height, Framebuffer::Mode::RGB565);
		addr = env.rm().attach(framebuffer->dataspace());

		framebuffer->sync_sigh(sync_dispatcher);
		framebuffer->mode_sigh(mode_dispatcher);
		PDBG("Window %dx%d", w, h);
	}

	void sync_handler();
	void mode_handler();
};

#endif /* _WINDOW_H_ */
