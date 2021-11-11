/**
 * \brief  eglut bindings for Genode Mesa demos
 * \author Sebastian Sumpf
 * \date   2017-08-17
 */

/*
 * Copyright (C) Genode Labs GmbH
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <base/attached_dataspace.h>
#include <base/heap.h>
#include <base/debug.h>
#include <gui_session/connection.h>
#include <libc/component.h>
#include <libc/args.h>

extern "C" {
#include "eglutint.h"
#include "gl_wrap.h"
#include <sys/select.h>
}


Genode::Env *genode_env;

struct Window : Genode_egl_window
{
	using View_handle = Gui::Session::View_handle;
	using Command = Gui::Session::Command;

	Genode::Env      &env;
	Framebuffer::Mode mode;
	Gui::Connection   gui { env };
	Genode::Constructible<Genode::Attached_dataspace> ds { };
	View_handle       view { };

	Genode::addr_t fb_addr { 0 };
	Genode::addr_t fb_size { 0 };
	Genode::Ram_dataspace_capability buffer_cap { };

	Window(Genode::Env &env, int w, int h)
	:
		env(env), mode { .area = Gui::Area(w, h) }
	{
		width  = w;
		height = h;
		type   = WINDOW;

		gui.buffer(mode, false);
		view = gui.create_view();

		mode_change();

		gui.enqueue<Command::Title>(view, "eglut");
		gui.enqueue<Command::To_front>(view, View_handle());
		gui.execute();
	}

	void mode_change()
	{
		if (ds.constructed())
			ds.destruct();

		ds.construct(env.rm(), gui.framebuffer()->dataspace());

		addr = ds->local_addr<unsigned char>();

		Gui::Rect rect { Gui::Point { 0, 0 }, mode.area };
		gui.enqueue<Command::Geometry>(view, rect);
		gui.execute();
	}

	void refresh()
	{
		gui.framebuffer()->refresh(0, 0, mode.area.w(), mode.area.h());
	}
};


static Genode::Constructible<Window> eglut_win;


void _eglutNativeInitDisplay()
{
	_eglut->surface_type = EGL_WINDOW_BIT;
}


void _eglutNativeFiniDisplay(void)
{
	PDBG("not implemented");
}


void _eglutNativeInitWindow(struct eglut_window *win, const char *title,
                            int x, int y, int w, int h)
{
	eglut_win.construct(*genode_env, w, h);
	Genode_egl_window *native = &*eglut_win;
	win->native.u.window = native;
	win->native.width = w;
	win->native.height = h;
}


void _eglutNativeFiniWindow(struct eglut_window *win)
{
	PDBG("not implemented");
}

struct Gui3d
{
	Genode::Env &_env; 
	Gui::Connection _3d  { _env, "threed" };
	Gui::Session::View_handle  _3d_view { _3d.create_view() };
	Framebuffer::Mode const    _3d_mode { .area = { 1280, 800 }};
	Genode::Constructible<Genode::Attached_dataspace> _3d_ds { };
	uint8_t *_framebuffer { nullptr };

	void _init_3d()
	{
		_3d.buffer(_3d_mode, false);

		_3d_ds.construct(_env.rm(), _3d.framebuffer()->dataspace());
		_framebuffer = _3d_ds->local_addr<uint8_t>();

		using Command = Gui::Session::Command;
		using namespace Gui;

		_3d.enqueue<Command::Geometry>(_3d_view, Gui::Rect(Gui::Point(0, 0), _3d_mode.area));
		_3d.enqueue<Command::To_front>(_3d_view, Gui::Session::View_handle());
		_3d.enqueue<Command::Title>(_3d_view, "3D from back end");
		_3d.execute();
	}

	Gui3d(Genode::Env &env) : _env(env) { _init_3d(); }

	unsigned char *fb() const { return _framebuffer; }

	void refresh() {
		_3d.framebuffer()->refresh(0, 0, _3d_mode.area.w(), _3d_mode.area.h());
	}
};

Genode::Constructible<Gui3d> _3dfb { };

void _eglutNativeEventLoop()
{
	struct eglut_window *w = _eglut->current;
	//eglMakeCurrent(_eglut->dpy, w->surface_shared, w->surface_shared, w->context_shared);
	GLuint id, fid, framebuffer, rid, wid;
	glGenFramebuffers(1, &framebuffer);
	glGenFramebuffers(1, &rid);
	glGenFramebuffers(1, &wid);
	Genode::log("glGenFramebuffers");
	glGenTextures(1, &id);
	glGenTextures(1, &fid);
	Genode::log("glGenTextures: id: ", id);
	GLenum t = GL_TEXTURE_2D;
	Genode::log("glBindTexture");
	glTexParameteri(t, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(t, GL_TEXTURE_MAX_LEVEL, 0);


	Genode::log("BASE parameter set");
	void *data = malloc(600*600*4);
	void *fdata = malloc(1280*800*4);
	Genode::log("MALLOC done");
	glBindTexture(t, id);
	glTexImage2D(t, 0, GL_RGBA8, 600, 600, 0, GL_RGBA, 
	             GL_UNSIGNED_INT_8_8_8_8_REV, data);

	glBindTexture(t, fid);
	glTexImage2D(t, 0, GL_RGBA8, 1280, 800, 0, GL_RGBA, 
	             GL_UNSIGNED_INT_8_8_8_8_REV, fdata);
	Genode::log("IMAGE generated");

	_3dfb.construct(*genode_env);

	void *buf = malloc(600*600*4);
	void *fbuf = malloc(1280*800*4);
	while (true) {
		struct eglut_window *win =_eglut->current;
		Genode::log("MAKE render current");
		//eglMakeCurrent(_eglut->dpy, w->surface, w->surface ,w->context);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glBindTexture(t, id);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);

		if (_eglut->idle_cb)
			_eglut->idle_cb();

		if (win->display_cb)
			win->display_cb();

		if (eglut_win.constructed()) {

			Genode::log("MAKE blit current");
			//eglMakeCurrent(_eglut->dpy, w->surface_shared, w->surface_shared, w->context_shared);
			/* blit to back end */
			glGetTexImage(t, 0, GL_RGBA,  GL_UNSIGNED_INT_8_8_8_8_REV, buf);
			Genode::memcpy(eglut_win->addr, buf, 600*600*4);
			eglut_win->refresh();
			Genode::log(__func__, ":", __LINE__);
			/* copy framebuffer and blit to back end */
			glBindFramebuffer(GL_READ_FRAMEBUFFER, rid);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, wid);
			glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fid, 0);
			Genode::log(__func__, ":", __LINE__);
			glBlitFramebuffer(0, 0, 600, 600,
			                  100, 100, 700, 700,
			                  GL_COLOR_BUFFER_BIT,
			                  GL_NEAREST);
			Genode::log(__func__, ":", __LINE__);
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
			glBindTexture(t, fid);
			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fid, 0);
//			glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fid, 0);
			Genode::log(__func__, ":", __LINE__);
			glGetTexImage(t, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, fbuf);
			Genode::log(__func__, ":", __LINE__);
			Genode::memcpy(_3dfb->fb(), fbuf, 1280*800*4);
			Genode::log(__func__, ":", __LINE__);
			_3dfb->refresh();
#if 0
			for (unsigned i = 0; i < 1280 * 800; i++) {
				unsigned *f = (unsigned *)fbuf;
				if (f[i] != 0) {
					Genode::log("STOP");
					while (1) ;
				}
			}
#endif
		}
	}
}


/*
 * 'eglut_main' will be called instead of 'main' by component initialization
 */
extern "C" int eglut_main(int argc, char *argv[]);


/* initial environment for the FreeBSD libc implementation */
extern char **environ;


static void construct_component(Libc::Env &env)
{
	int argc    = 0;
	char **argv = nullptr;
	char **envp = nullptr;

	populate_args_and_env(env, argc, argv, envp);

	environ = envp;

	exit(eglut_main(argc, argv));
}


void Libc::Component::construct(Libc::Env &env)
{
	genode_env = &env;
	Libc::with_libc([&] () { construct_component(env); });
}
