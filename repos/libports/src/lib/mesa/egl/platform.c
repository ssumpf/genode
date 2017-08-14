/*
 * Mesa
 */
#include <egl_dri2.h>
#include <egl_dri2_fallbacks.h>
#include <drivers/dri/common/utils.h>

/*
 * Libc
 */
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
/*
 * Local
 */
#include <platform.h>


EGLBoolean dri2_genode_swap_interval(_EGLDriver *drv, _EGLDisplay *disp,
                                     _EGLSurface *surf, EGLint interval)
{
	if (interval > surf->Config->MaxSwapInterval)
		interval = surf->Config->MaxSwapInterval;
	else if (interval < surf->Config->MinSwapInterval)
		interval = surf->Config->MinSwapInterval;

	surf->SwapInterval = interval;

	return EGL_TRUE;
}


_EGLSurface *
dri2_genode_create_window_surface(_EGLDriver *drv, _EGLDisplay *disp,
                                  _EGLConfig *conf, void *native_window,
                                  const EGLint *attrib_list)
{
	struct dri2_egl_display *dri2_dpy = dri2_egl_display(disp);
	struct dri2_egl_config *dri2_conf = dri2_egl_config(conf);
	struct Genode_egl_window  *window = native_window;
	struct dri2_egl_surface *dri2_surf;
	const __DRIconfig *config;

	dri2_surf = calloc(1, sizeof *dri2_surf);

	if (!dri2_surf)
	{
		_eglError(EGL_BAD_ALLOC, "dri2_create_surface");
		return NULL;
	}

	if (!_eglInitSurface(&dri2_surf->base, disp, EGL_WINDOW_BIT, conf, attrib_list))
	   goto cleanup_surf;

	dri2_surf->g_win = window;
	dri2_surf->base.Width  = window->width;;
	dri2_surf->base.Height = window->height;

	config = dri2_get_dri_config(dri2_conf, EGL_WINDOW_BIT,
	                             dri2_surf->base.GLColorspace);

	if (dri2_dpy->dri2) {
		dri2_surf->dri_drawable = (*dri2_dpy->dri2->createNewDrawable)(dri2_dpy->dri_screen, config,
		                                                               dri2_surf);
		/* create back buffer image */
		dri2_surf->back_image = dri2_dpy->image->createImage(dri2_dpy->dri_screen,
		                                                     dri2_surf->base.Width,
		                                                     dri2_surf->base.Height,
		                                                     __DRI_IMAGE_FORMAT_RGB565,
		                                                     dri2_dpy->is_different_gpu ?
		                                                     0 : __DRI_IMAGE_USE_SHARE,
		                                                     NULL);
	} else {
		assert(dri2_dpy->swrast);
		dri2_surf->dri_drawable =
		   (*dri2_dpy->swrast->createNewDrawable)(dri2_dpy->dri_screen,
		                                          config, dri2_surf);
	}

	if (dri2_surf->dri_drawable == NULL)
	{
		_eglError(EGL_BAD_ALLOC, "swrast->createNewDrawable");
		 goto cleanup_dri_drawable;
	}

	dri2_genode_swap_interval(drv, disp, &dri2_surf->base,
	                          dri2_dpy->default_swap_interval);

	return &dri2_surf->base;

cleanup_dri_drawable:
	dri2_dpy->core->destroyDrawable(dri2_surf->dri_drawable);
cleanup_surf:
	free(dri2_surf);

	return NULL;
}


EGLBoolean
dri2_genode_destroy_surface(_EGLDriver *drv, _EGLDisplay *disp, _EGLSurface *surf)
{
	_eglError(EGL_BAD_PARAMETER, "destroy surface not implemented");
	return EGL_FALSE;
}

_EGLSurface *
dri2_genode_create_pixmap_surface(_EGLDriver *drv, _EGLDisplay *disp,
                                 _EGLConfig *conf, void *native_window,
                                 const EGLint *attrib_list)
{
	_eglError(EGL_BAD_PARAMETER, "pximap surface not implemented");
	return NULL;
}


EGLBoolean dri2_initialize_genode(_EGLDriver *drv, _EGLDisplay *disp)
{
	void *handle;

	if (!(handle = dlopen("egl_drv.lib.so", 0))) {
		printf("Error: could not open EGL back end driver ('egl_drv.lib.so')\n");
		return EGL_FALSE;
	}

	typedef EGLBoolean (*genode_backend)(_EGLDriver *, _EGLDisplay *);

	genode_backend init = (genode_backend)dlsym(handle, "dri2_initialize_genode_backend");
	if (!init) {
		printf("Error: could not find 'dri2_initialize_genode_backend'\n");
		return EGL_FALSE;
	}

	return init(drv, disp);
}
