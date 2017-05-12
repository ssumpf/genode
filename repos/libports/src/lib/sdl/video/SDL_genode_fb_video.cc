/*
 * \brief  Genode-specific video backend
 * \author Stefan Kalkowski
 * \date   2008-12-12
 */

/*
 * Copyright (c) <2008> Stefan Kalkowski
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#include <base/log.h>
#include <base/env.h>
#include <framebuffer_session/connection.h>

#include <window.h>

#define EGL_EGLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>

#define MAX_CONFIGS 10
#define MAX_MODES 100

#define GENODE_OPENGL 1

extern Genode::Env &genode_env();



extern "C" {

#include <dlfcn.h>

#include <SDL/SDL.h>
#include <SDL/SDL_video.h>
#include <SDL/SDL_mouse.h>
#include "SDL_sysvideo.h"
#include "SDL_pixels_c.h"
#include "SDL_events_c.h"
#include "SDL_genode_fb_events.h"
#include "SDL_genode_fb_video.h"

	static Framebuffer::Connection *framebuffer = 0;
	static Framebuffer::Mode scr_mode;
	static SDL_Rect *modes[2];
	static SDL_Rect df_mode;

	/***************************************
	 * Genode_Fb driver bootstrap functions
	 **************************************/

	static void Genode_Fb_GL_Init()
	{
	}


	static EGLDisplay display;
	static EGLSurface screen_surf;
	static EGLNativeWindowType native_window;

	/**
	 *
	 */
	static int Genode_Fb_Available(void) {
#ifndef GENODE_OPENGL
		if(framebuffer == 0)
			framebuffer = new(Genode::env()->heap()) Framebuffer::Connection();
		if (!framebuffer->cap().valid())
		{
			Genode::error("couldn't obtain framebuffer session");
			return 0;
		}
#endif
		return 1;
	}


	/**
	 *
	 */
	static void Genode_Fb_DeleteDevice(SDL_VideoDevice *device)
	{
		Genode::log("free framebuffer session object");
		if(framebuffer != 0)
			delete framebuffer;
		framebuffer = 0;
	}


	/**
	 *
	 */
	static SDL_VideoDevice *Genode_Fb_CreateDevice(int devindex)
	{
		SDL_VideoDevice *device;

		/* Initialize all variables that we clean on shutdown */
		device = (SDL_VideoDevice *)SDL_malloc(sizeof(SDL_VideoDevice));
		if ( device ) {
			SDL_memset(device, 0, (sizeof *device));
			device->hidden = (struct SDL_PrivateVideoData *)
				SDL_malloc((sizeof *device->hidden));
		}
		if ( (device == 0) || (device->hidden == 0) ) {
			SDL_OutOfMemory();
			if ( device ) {
				SDL_free(device);
			}
			return(0);
		}
		SDL_memset(device->hidden, 0, (sizeof *device->hidden));

		/* Set the function pointers */
		device->VideoInit        = Genode_Fb_VideoInit;
		device->ListModes        = Genode_Fb_ListModes;
		device->SetVideoMode     = Genode_Fb_SetVideoMode;
		device->SetColors        = Genode_Fb_SetColors;
		device->UpdateRects      = Genode_Fb_UpdateRects;
		device->VideoQuit        = Genode_Fb_VideoQuit;
		device->AllocHWSurface   = Genode_Fb_AllocHWSurface;
		device->LockHWSurface    = Genode_Fb_LockHWSurface;
		device->UnlockHWSurface  = Genode_Fb_UnlockHWSurface;
		device->FreeHWSurface    = Genode_Fb_FreeHWSurface;
		device->InitOSKeymap     = Genode_Fb_InitOSKeymap;
		device->PumpEvents       = Genode_Fb_PumpEvents;
		device->free             = Genode_Fb_DeleteDevice;
		device->CreateYUVOverlay = 0;
		device->CheckHWBlit      = 0;
		device->FillHWRect       = 0;
		device->SetHWColorKey    = 0;
		device->SetHWAlpha       = 0;
		device->FlipHWSurface    = 0;
		device->SetCaption       = 0;
		device->SetIcon          = 0;
		device->IconifyWindow    = 0;
		device->GrabInput        = 0;
		device->GetWMInfo        = 0;

		device->GL_MakeCurrent    = Genode_Fb_GL_MakeCurrent;
		device->GL_SwapBuffers    = Genode_Fb_GL_SwapBuffers;
		device->GL_LoadLibrary    = Genode_Fb_GL_LoadLibrary;
		device->GL_GetProcAddress = Genode_Fb_GL_GetProcAddress;
		return device;
	}


	VideoBootStrap Genode_fb_bootstrap = {
		"Genode_Fb", "SDL genode_fb video driver",
		Genode_Fb_Available, Genode_Fb_CreateDevice
	};


	/*****************
	 * Functionality
	 ****************/

	/**
	 * Initialize the native video subsystem, filling 'vformat' with the
	 * "best" display pixel format, returning 0 or -1 if there's an error.
	 */
	int Genode_Fb_VideoInit(SDL_VideoDevice *t, SDL_PixelFormat *vformat)
	{
#ifndef GENODE_OPENGL
		if(framebuffer == 0)
		{
			Genode::error("framebuffer isn't initialized");
			return -1;
		}

		/* Get the framebuffer size and mode infos */
		scr_mode = framebuffer->mode();
		t->info.current_w = scr_mode.width();
		t->info.current_h = scr_mode.height();
		Genode::log("Framebuffer has "
		            "width=",  t->info.current_w, " "
		            "height=", t->info.current_h);

		/* set mode specific values */
		switch(scr_mode.format())
		{
		case Framebuffer::Mode::RGB565:
			Genode::log("We use pixelformat rgb565.");
			vformat->BitsPerPixel  = 16;
			vformat->BytesPerPixel = scr_mode.bytes_per_pixel();
			vformat->Rmask = 0x0000f800;
			vformat->Gmask = 0x000007e0;
			vformat->Bmask = 0x0000001f;
			break;
		default:
			SDL_SetError("Couldn't get console mode info");
			Genode_Fb_VideoQuit(t);
			return -1;
		}
		modes[0] = &df_mode;
		df_mode.w = scr_mode.width();
		df_mode.h = scr_mode.height();
		modes[1] = 0;

		/* Map the buffer */
		Genode::Dataspace_capability fb_ds_cap = framebuffer->dataspace();
		if (!fb_ds_cap.valid()) {
			Genode::error("could not request dataspace for frame buffer");
			return -1;
		}
		t->hidden->buffer = Genode::env()->rm_session()->attach(fb_ds_cap);
#else
		int maj, min;
		EGLContext ctx;
		EGLConfig configs[MAX_CONFIGS];
		EGLBoolean b;
		GLboolean printInfo = GL_FALSE;
		EGLint width = 0, height = 0;

		/* DBR : Create EGL context/surface etc */
		display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if (!display) {
			printf("eglGetDisplay failed\n");
			return -1;
		}

		if (!eglInitialize(display, &maj, &min)) {
			printf("eglInitialize failed\n");
			return -1;
		}

		printf("EGL version = %d.%d\n", maj, min);
		printf("EGL_VENDOR = %s\n", eglQueryString(display, EGL_VENDOR));

		EGLConfig config;
		EGLint config_attribs[32];
		EGLint renderable_type, num_configs, i;

		i = 0;
		config_attribs[i++] = EGL_RED_SIZE;
		config_attribs[i++] = 1;
		config_attribs[i++] = EGL_GREEN_SIZE;
		config_attribs[i++] = 1;
		config_attribs[i++] = EGL_BLUE_SIZE;
		config_attribs[i++] = 1;
		config_attribs[i++] = EGL_DEPTH_SIZE;
		config_attribs[i++] = 1;

		config_attribs[i++] = EGL_SURFACE_TYPE;
		config_attribs[i++] = EGL_WINDOW_BIT;;

		config_attribs[i++] = EGL_RENDERABLE_TYPE;
		renderable_type = 0x0;
		renderable_type |= EGL_OPENGL_BIT;
		config_attribs[i++] = renderable_type;

		config_attribs[i] = EGL_NONE;

		if (!eglChooseConfig(display, config_attribs, &config, 1, &num_configs) || !num_configs) {
			printf("eglChooseConfig failed\n");
			return -1;
		}

		eglBindAPI(EGL_OPENGL_API);

		EGLint context_attribs[4]; context_attribs[0] = EGL_NONE;
		ctx = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attribs);
		if (!ctx) {
			printf("failed to create context\n");
			return -1;
		}

		width = 1920;
		height = 1080;

		native_window = new (Genode::env()->heap()) Window(genode_env(), width, height);

		screen_surf = eglCreateWindowSurface(display, config, native_window, NULL);
		if (screen_surf == EGL_NO_SURFACE) {
			printf("failed to create screen surface\n");
			return -1;
		}
		printf("returned from eglCreateScreenSurfaceMESA\n");

		b = eglMakeCurrent(display, screen_surf, screen_surf, ctx);
		if (!b) {
			printf("make current failed\n");
			return -1;
		}
		printf("returned from eglMakeCurrent\n");

		printf("GL_RENDERER   = %s\n", (char *) glGetString(GL_RENDERER));
		printf("GL_VERSION    = %s\n", (char *) glGetString(GL_VERSION));
		printf("GL_VENDOR     = %s\n", (char *) glGetString(GL_VENDOR));
		printf("GL_EXTENSIONS = %s\n", (char *) glGetString(GL_EXTENSIONS));

		t->info.current_w = width;
		t->info.current_h = height;
		vformat->BitsPerPixel  = 16;
		vformat->BytesPerPixel = scr_mode.bytes_per_pixel();
		vformat->Rmask = 0x0000f800;
		vformat->Gmask = 0x000007e0;
		vformat->Bmask = 0x0000001f;
		modes[0] = &df_mode;
		df_mode.w = width;
		df_mode.h = height;
		modes[1] = 0;
		t->gl_config.driver_loaded = 1;
#endif
		return 0;
	}


	/**
	 * List the available video modes for the given pixel format,
	 * sorted from largest to smallest.
	 */
	SDL_Rect **Genode_Fb_ListModes(SDL_VideoDevice *t,
	                               SDL_PixelFormat *format,
	                               Uint32 flags)
	{
		if(format->BitsPerPixel != 16)
			return (SDL_Rect **) 0;
		return modes;
	}


	/**
	 * Set the requested video mode, returning a surface which will be
	 * set to the SDL_VideoSurface.  The width and height will already
	 * be verified by ListModes(), and the video subsystem is free to
	 * set the mode to a supported bit depth different from the one
	 * specified -- the desired bpp will be emulated with a shadow
	 * surface if necessary.  If a new mode is returned, this function
	 * should take care of cleaning up the current mode.
	 */
	SDL_Surface *Genode_Fb_SetVideoMode(SDL_VideoDevice *t,
	                                    SDL_Surface *current,
	                                    int width, int height,
	                                    int bpp, Uint32 flags)
	{
		Genode::log("Set video mode to: "
		            "width=", width, " " "height=", height, " " "bpp=", bpp);

#ifndef GENODE_OPENGL
		if ( ! t->hidden->buffer ) {
			Genode::error("no buffer for requested mode");
			return(0);
		}
		SDL_memset(t->hidden->buffer, 0, width * height * (bpp / 8));
#endif

		/* Allocate the new pixel format for the screen */
		if ( ! SDL_ReallocFormat(current, bpp, 0, 0, 0, 0) ) {
			Genode::error("couldn't allocate new pixel format for requested mode");
			return(0);
		}

		/* Set up the new mode framebuffer */
		current->flags = flags | SDL_FULLSCREEN;
		t->hidden->w = current->w = width;
		t->hidden->h = current->h = height;
		current->pitch = current->w * (bpp / 8);
#ifndef GENODE_OPENGL
		current->pixels = t->hidden->buffer;
#endif
		return(current);
	}


	/**
	 * We don't actually allow hardware surfaces other than the main one
	 */
	static int Genode_Fb_AllocHWSurface(SDL_VideoDevice *t,
	                                    SDL_Surface *surface)
	{
		Genode::log(__func__, " not supported yet ...");
		return -1;
	}


	static void Genode_Fb_FreeHWSurface(SDL_VideoDevice *t,
	                                    SDL_Surface *surface)
	{
		Genode::log(__func__, " not supported yet ...");
	}


	/**
	 * We need to wait for vertical retrace on page flipped displays
	 */
	static int Genode_Fb_LockHWSurface(SDL_VideoDevice *t,
	                                   SDL_Surface *surface)
	{
		Genode::log(__func__, " not supported yet ...");
		return 0;
	}


	static void Genode_Fb_UnlockHWSurface(SDL_VideoDevice *t,
	                                      SDL_Surface *surface)
	{
		Genode::log(__func__, " not supported yet ...");
	}


	static void Genode_Fb_UpdateRects(SDL_VideoDevice *t, int numrects,
	                                  SDL_Rect *rects)
	{
#ifndef GENODE_OPENGL
		int i;
		for(i=0;i<numrects;i++)
			framebuffer->refresh(rects[i].x, rects[i].y, rects[i].w, rects[i].h);
#endif
	}


	/**
	 * Sets the color entries { firstcolor .. (firstcolor+ncolors-1) }
	 * of the physical palette to those in 'colors'. If the device is
	 * using a software palette (SDL_HWPALETTE not set), then the
	 * changes are reflected in the logical palette of the screen
	 * as well.
	 * The return value is 1 if all entries could be set properly
	 * or 0 otherwise.
	 */
	int Genode_Fb_SetColors(SDL_VideoDevice *t, int firstcolor,
	                        int ncolors, SDL_Color *colors)
	{
		Genode::warning(__func__, " not implemented yet");
		return 1;
	}


	/**
	 *Note:  If we are terminated, this could be called in the middle of
	 * another SDL video routine -- notably UpdateRects.
	 */
	void Genode_Fb_VideoQuit(SDL_VideoDevice *t)
	{
		Genode::log("Quit video device ...");
		if (t->screen->pixels != 0)
		{
			SDL_free(t->screen->pixels);
			t->screen->pixels = 0;
		}
	}

	int Genode_Fb_GL_MakeCurrent(SDL_VideoDevice *t)
	{
		Genode::warning("%s: Not yet implemented", __func__);
		return 0;
	}

	void Genode_Fb_GL_SwapBuffers(SDL_VideoDevice *t)
	{
		eglWaitClient();
		eglSwapBuffers(display, screen_surf);
	}

	int Genode_Fb_GL_LoadLibrary(SDL_VideoDevice *t, const char *path)
	{
		Genode::warning("Not yet implemented");
		return 0;
	}


	static void* load_mesa()
	{
		static void *ptr = dlopen("mesa-11.lib.so", 0);
		return ptr;
	}


	void* Genode_Fb_GL_GetProcAddress(SDL_VideoDevice *t, const char *proc)
	{
		PDBG("get proc %s", proc);
		return dlsym(load_mesa(), proc);
	}

} //extern "C"
