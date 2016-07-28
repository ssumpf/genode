
#include <egl_dri2.h>
#include <egl_dri2_fallbacks.h>

#include <string.h>
/*
 * XXX: implement commented out
 */
static struct dri2_egl_display_vtbl dri2_genode_swrast_display_vtbl = {
   .authenticate = NULL,
//   .create_window_surface = dri2_wl_swrast_create_window_surface,
 //  .create_pixmap_surface = dri2_wl_create_pixmap_surface,
   .create_pbuffer_surface = dri2_fallback_create_pbuffer_surface,
//   .destroy_surface = dri2_wl_destroy_surface,
   .create_image = dri2_fallback_create_image_khr,
//   .swap_interval = dri2_wl_swap_interval,
//   .swap_buffers = dri2_wl_swrast_swap_buffers,
   .swap_buffers_with_damage = dri2_fallback_swap_buffers_with_damage,
   .swap_buffers_region = dri2_fallback_swap_buffers_region,
   .post_sub_buffer = dri2_fallback_post_sub_buffer,
   .copy_buffers = dri2_fallback_copy_buffers,
   .query_buffer_age = dri2_fallback_query_buffer_age,
   .create_wayland_buffer_from_image = dri2_fallback_create_wayland_buffer_from_image,
   .get_sync_values = dri2_fallback_get_sync_values,
   .get_dri_drawable = dri2_surface_get_dri_drawable,
};


static EGLBoolean
dri2_initialize_genode_swrast(_EGLDriver *drv, _EGLDisplay *disp)
{
	struct dri2_egl_display *dri2_dpy;
	__DRIconfig const * config;
	static unsigned int rgb565_masks[4] = { 0xf800, 0x07e0, 0x001f, 0 };


	dri2_dpy = calloc(1, sizeof *dri2_dpy);

	if (!dri2_dpy)
		return _eglError(EGL_BAD_ALLOC, "eglInitialize");

	disp->DriverData = (void *)dri2_dpy;
	dri2_dpy->vtbl   = &dri2_genode_swrast_display_vtbl;

	dri2_dpy->fd = -1;
	dri2_dpy->driver_name = strdup("swrast");
	if (!dri2_load_driver_swrast(disp))
		goto close_driver;

	if (!dri2_create_screen(disp))
		goto close_screen;

	/* add RGB565 only */
  config = dri2_dpy->driver_configs[0];
	dri2_add_config(disp, config, 1, EGL_WINDOW_BIT, NULL, rgb565_masks);

	return EGL_TRUE;

close_screen:
	dlclose(dri2_dpy->driver);
close_driver:
	free(dri2_dpy);

	return EGL_FALSE;
}


EGLBoolean dri2_initialize_genode(_EGLDriver *drv, _EGLDisplay *disp)
{
	dri2_initialize_genode_swrast(drv, disp);
	return EGL_TRUE;
}

