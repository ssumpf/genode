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
#include <bo_map.h>
#include <platform.h>


static EGLBoolean dri2_genode_swap_interval(_EGLDriver *drv, _EGLDisplay *disp,
                                            _EGLSurface *surf, EGLint interval)
{
	if (interval > surf->Config->MaxSwapInterval)
		interval = surf->Config->MaxSwapInterval;
	else if (interval < surf->Config->MinSwapInterval)
		interval = surf->Config->MinSwapInterval;

	surf->SwapInterval = interval;

	return EGL_TRUE;
}


static _EGLSurface *
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


static int stride(int value)
{
	/* RGB556 */
	return value * 2;
}

/*
extern void
tiled_to_linear(uint32_t xt1, uint32_t xt2,
                uint32_t yt1, uint32_t yt2,
                char *dst, const char *src,
                int32_t dst_pitch, uint32_t src_pitch,
                bool has_swizzling,
                uint32_t tiling,
                mem_copy_fn mem_copy);
*/

static void
dri2_genode_put_image(__DRIdrawable * draw, int op,
                      int x, int y, int w, int h,
                      char *data, void *loaderPrivate)
{
	struct dri2_egl_surface *dri2_surf  = loaderPrivate;
	struct dri2_egl_display *dri2_dpy   = dri2_egl_display(dri2_surf->base.Resource.Display);
	struct Genode_egl_window  *window   = dri2_surf->g_win;
	unsigned char * dst                 = window->addr;

	int src_stride;
	int dst_stride = stride(dri2_surf->base.Width);
	dri2_dpy->image->queryImage(dri2_surf->back_image, __DRI_IMAGE_ATTRIB_STRIDE, &src_stride);

	/* copy to frame buffer and refresh */
	tiled_to_linear(0, dst_stride,
	                0, h,
	                dst, data,
	                dst_stride, src_stride,
	                false, 1, memcpy);

	genode_framebuffer_refresh(window, x, y, w, h);
}



static void
dri2_genode_swrast_put_image(__DRIdrawable * draw, int op,
                             int x, int y, int w, int h,
                             char *data, void *loaderPrivate)
{
	struct dri2_egl_surface *dri2_surf  = loaderPrivate;
	struct Genode_egl_window  *window   = dri2_surf->g_win;
	unsigned char * dst                 = window->addr;

	int dst_stride = stride(dri2_surf->base.Width);
	int copy_width = stride(w);
	int x_offset = stride(x);
	int src_stride = copy_width;

	dst += x_offset;
	dst += y * dst_stride;

	/* copy width over stride boundary */
	if (copy_width >dst_stride - x_offset)
		copy_width = dst_stride - x_offset;

	/* limit height */
	if (h > dri2_surf->base.Height - y)
		h = dri2_surf->base.Height - y;

	/* copy to frame buffer and refresh */
	genode_blit(data, src_stride, dst, dst_stride, copy_width, h);
	genode_framebuffer_refresh(window, x, y, w, h);
}


static EGLBoolean
dri2_genode_swrast_swap_buffers(_EGLDriver *drv, _EGLDisplay *disp, _EGLSurface *draw)
{
	struct dri2_egl_display *dri2_dpy = dri2_egl_display(disp);
	struct dri2_egl_surface *dri2_surf = dri2_egl_surface(draw);

	dri2_dpy->core->swapBuffers(dri2_surf->dri_drawable);
	return EGL_TRUE;
}


static EGLBoolean
dri2_genode_swap_buffers(_EGLDriver *drv, _EGLDisplay *disp, _EGLSurface *draw)
{
	struct dri2_egl_surface *dri2_surf = dri2_egl_surface(draw);

	void *data = genode_map_image(dri2_surf->back_image);
	dri2_genode_put_image(dri2_surf->dri_drawable, 0, 0, 0,
	                      dri2_surf->base.Width, dri2_surf->base.Height,
	                      (char *)data, (void *)dri2_surf);

	genode_unmap_image(dri2_surf->back_image);


	return EGL_TRUE;
}


static EGLBoolean
dri2_genode_destroy_surface(_EGLDriver *drv, _EGLDisplay *disp, _EGLSurface *surf)
{
	_eglError(EGL_BAD_PARAMETER, "destroy surface not implemented");
	return EGL_FALSE;
}


static _EGLSurface *
dri2_genode_create_pixmap_surface(_EGLDriver *drv, _EGLDisplay *disp,
                                 _EGLConfig *conf, void *native_window,
                                 const EGLint *attrib_list)
{
	_eglError(EGL_BAD_PARAMETER, "pximap surface not implemented");
	return NULL;
}


/*
 * platform functions
 */
static struct dri2_egl_display_vtbl dri2_genode_display_vtbl = {
	.authenticate = NULL,
	.create_window_surface = dri2_genode_create_window_surface,
	.create_pixmap_surface = dri2_genode_create_pixmap_surface,
	.create_pbuffer_surface = dri2_fallback_create_pbuffer_surface,
	.destroy_surface = dri2_genode_destroy_surface,
	.create_image = dri2_fallback_create_image_khr,
	.swap_interval = dri2_genode_swap_interval,
	.swap_buffers = dri2_genode_swap_buffers,
	.swap_buffers_with_damage = dri2_fallback_swap_buffers_with_damage,
	.swap_buffers_region = dri2_fallback_swap_buffers_region,
	.post_sub_buffer = dri2_fallback_post_sub_buffer,
	.copy_buffers = dri2_fallback_copy_buffers,
	.query_buffer_age = dri2_fallback_query_buffer_age,
	.get_sync_values = dri2_fallback_get_sync_values,
	.get_dri_drawable = dri2_surface_get_dri_drawable,
};

static struct dri2_egl_display_vtbl dri2_genode_swrast_display_vtbl = {
	.authenticate = NULL,
	.create_window_surface = dri2_genode_create_window_surface,
	.create_pixmap_surface = dri2_genode_create_pixmap_surface,
	.create_pbuffer_surface = dri2_fallback_create_pbuffer_surface,
	.destroy_surface = dri2_genode_destroy_surface,
	.create_image = dri2_fallback_create_image_khr,
	.swap_interval = dri2_genode_swap_interval,
	.swap_buffers = dri2_genode_swrast_swap_buffers,
	.swap_buffers_with_damage = dri2_fallback_swap_buffers_with_damage,
	.swap_buffers_region = dri2_fallback_swap_buffers_region,
	.post_sub_buffer = dri2_fallback_post_sub_buffer,
	.copy_buffers = dri2_fallback_copy_buffers,
	.query_buffer_age = dri2_fallback_query_buffer_age,
	.get_sync_values = dri2_fallback_get_sync_values,
	.get_dri_drawable = dri2_surface_get_dri_drawable,
};


static void
dri2_genode_swrast_get_image(__DRIdrawable * read,
                             int x, int y, int w, int h,
                             char *data, void *loaderPrivate)
{
	struct dri2_egl_surface *dri2_surf  = loaderPrivate;
	struct Genode_egl_window  *window   = dri2_surf->g_win;
	unsigned char * src                 = window->addr;

	int src_stride = stride(dri2_surf->base.Width);
	int copy_width = stride(w);
	int x_offset = stride(x);
	int dst_stride = copy_width;

	assert(data != (char *)src);

	src += x_offset;
	src += y * src_stride;

	/* copy width over stride boundary */
	if (copy_width > src_stride - x_offset)
		copy_width = src_stride - x_offset;

	/* limit height */
	if (h > dri2_surf->base.Height - y)
		h = dri2_surf->base.Height - y;

	/* copy to surface */
	genode_blit(src, src_stride, data, dst_stride, copy_width, h);
}


static void
dri2_genode_swrast_get_drawable_info(__DRIdrawable * draw,
                                 int *x, int *y, int *w, int *h,
                                 void *loaderPrivate)
{
	struct dri2_egl_surface *dri2_surf = loaderPrivate;

	//XXX: (void) swrast_update_buffers(dri2_surf);
	*x = 0;
	*y = 0;
	*w = dri2_surf->base.Width;
	*h = dri2_surf->base.Height;
}


static EGLBoolean
dri2_initialize_genode_swrast(_EGLDriver *drv, _EGLDisplay *disp)
{
	struct dri2_egl_display *dri2_dpy;
	static unsigned rgb565_masks[4] = { 0xf800, 0x07e0, 0x001f, 0 };
	int i;

	dri2_dpy = calloc(1, sizeof *dri2_dpy);

	if (!dri2_dpy)
		return _eglError(EGL_BAD_ALLOC, "eglInitialize");

	disp->DriverData = (void *)dri2_dpy;
	dri2_dpy->vtbl   = &dri2_genode_swrast_display_vtbl;

	dri2_dpy->fd = -1;
	dri2_dpy->driver_name = strdup("swrast");
	if (!dri2_load_driver_swrast(disp))
		goto close_driver;

	dri2_dpy->swrast_loader_extension.base.name       = __DRI_SWRAST_LOADER;
	dri2_dpy->swrast_loader_extension.base.version    = 2;
	dri2_dpy->swrast_loader_extension.getDrawableInfo = dri2_genode_swrast_get_drawable_info;
	dri2_dpy->swrast_loader_extension.putImage        = dri2_genode_swrast_put_image;
	dri2_dpy->swrast_loader_extension.getImage        = dri2_genode_swrast_get_image;

	dri2_dpy->extensions[0] = &dri2_dpy->swrast_loader_extension.base;
	dri2_dpy->extensions[1] = NULL;

	if (!dri2_create_screen(disp))
		goto close_screen;

	/* add RGB565 only */
	EGLint attrs[] = {
		EGL_DEPTH_SIZE, 0, /* set in loop below (from DRI config) */
		EGL_NATIVE_VISUAL_TYPE, 0,
		EGL_NATIVE_VISUAL_ID, 0,
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_NONE };

	for (i = 1; dri2_dpy->driver_configs[i]; i++) {
		/* set depth size in attrs */
		attrs[1] = dri2_dpy->driver_configs[i]->modes.depthBits;
		dri2_add_config(disp, dri2_dpy->driver_configs[i], i, EGL_WINDOW_BIT, attrs, rgb565_masks);
	}

	return EGL_TRUE;

close_screen:
	dlclose(dri2_dpy->driver);
close_driver:
	free(dri2_dpy);

	return EGL_FALSE;
}


static __DRIbuffer *
dri2_genode_get_buffers(__DRIdrawable * driDrawable,
                        int *width, int *height,
                        unsigned int *attachments, int count,
                        int *out_count, void *loaderPrivate)
{
	_eglError(EGL_BAD_PARAMETER, "dri2_genode_get_buffers not implemented");
	return NULL;
}


static void
dri2_genode_flush_front_buffer(__DRIdrawable * driDrawable, void *loaderPrivate)
{
	_eglError(EGL_BAD_PARAMETER, "dri2_genode_flush_front_buffer not implemented");
}


static void
back_bo_to_dri_buffer(struct dri2_egl_surface *dri2_surf, __DRIbuffer *buffer)
{
	struct dri2_egl_display *dri2_dpy = dri2_egl_display(dri2_surf->base.Resource.Display);
	__DRIimage *image;
	int name, pitch;

	image = dri2_surf->back_image;

	dri2_dpy->image->queryImage(image, __DRI_IMAGE_ATTRIB_NAME, &name);
	dri2_dpy->image->queryImage(image, __DRI_IMAGE_ATTRIB_STRIDE, &pitch);

	buffer->attachment = __DRI_BUFFER_BACK_LEFT;
	buffer->name = name;
	buffer->pitch = pitch;
	buffer->cpp = 4;
	buffer->flags = 0;
}


static __DRIbuffer *
dri2_genode_get_buffers_with_format(__DRIdrawable * driDrawable,
                                    int *width, int *height,
                                    unsigned int *attachments, int count,
                                    int *out_count, void *loaderPrivate)
{
	struct dri2_egl_surface *dri2_surf = loaderPrivate;
	int i, j;

	for (i = 0, j = 0; i < 2 * count; i += 2, j++) {
		switch (attachments[i]) {
		case __DRI_BUFFER_BACK_LEFT:
			back_bo_to_dri_buffer(dri2_surf, &dri2_surf->buffers[j]);
			break;
		default:
//			if (get_aux_bo(dri2_surf, attachments[i], attachments[i + 1],
//			               &dri2_surf->buffers[j]) < 0) {
//				_eglError(EGL_BAD_ALLOC, "failed to allocate aux buffer");
//				return NULL;
//			}
			printf("aux buffer\n");
			printf("ERROR: not implemented\n");
			while (1);
			break;
		}
	}

	*out_count = j;
	if (j == 0)
		return NULL;

	*width = dri2_surf->base.Width;
	*height = dri2_surf->base.Height;

	return dri2_surf->buffers;
}


static EGLBoolean
dri2_initialize_genode_dri2(_EGLDriver *drv, _EGLDisplay *disp)
{
	struct dri2_egl_display *dri2_dpy;
	static unsigned rgb565_masks[4] = { 0xf800, 0x07e0, 0x001f, 0 };
	int i;

	dri2_dpy = calloc(1, sizeof *dri2_dpy);
	if (!dri2_dpy)
		return _eglError(EGL_BAD_ALLOC, "eglInitialize");

	dri2_dpy->fd          = -1;
	dri2_dpy->driver_name = strdup("i965");

	disp->DriverData = (void *)dri2_dpy;
	dri2_dpy->vtbl   = &dri2_genode_display_vtbl;

	if (!dri2_load_driver(disp))
		goto cleanup_dpy;

/* XXX: uncomment me
	if (!genode_start_intel_fb_drv())
		goto cleanup_dpy;
*/

	dri2_dpy->dri2_major = 2;
	dri2_dpy->dri2_minor = __DRI_DRI2_VERSION;
	dri2_dpy->dri2_loader_extension.base.name = __DRI_DRI2_LOADER;
	dri2_dpy->dri2_loader_extension.base.version = 3;
	dri2_dpy->dri2_loader_extension.getBuffers = dri2_genode_get_buffers;
	dri2_dpy->dri2_loader_extension.flushFrontBuffer = dri2_genode_flush_front_buffer;
	dri2_dpy->dri2_loader_extension.getBuffersWithFormat = dri2_genode_get_buffers_with_format;


	dri2_dpy->extensions[0] = &dri2_dpy->dri2_loader_extension.base;
	dri2_dpy->extensions[1] = &image_lookup_extension.base;
	dri2_dpy->extensions[2] = NULL;
	
	dri2_dpy->swap_available = (dri2_dpy->dri2_minor >= 2);
	dri2_dpy->invalidate_available = (dri2_dpy->dri2_minor >= 3);

	if (!dri2_create_screen(disp))
		goto close_screen;


	/* add RGB565 only */
	EGLint attrs[] = {
		EGL_DEPTH_SIZE, 0, /* set in loop below (from DRI config) */
		EGL_NATIVE_VISUAL_TYPE, 0,
		EGL_NATIVE_VISUAL_ID, 0,
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_NONE };

	for (i = 1; dri2_dpy->driver_configs[i]; i++) {
		/* set depth size in attrs */
		attrs[1] = dri2_dpy->driver_configs[i]->modes.depthBits;
		dri2_add_config(disp, dri2_dpy->driver_configs[i], i, EGL_WINDOW_BIT, attrs, rgb565_masks);
	}

	return EGL_TRUE;

close_screen:
	dlclose(dri2_dpy->driver);
cleanup_dpy:
	free(dri2_dpy);

	return EGL_FALSE;
}


EGLBoolean dri2_initialize_genode(_EGLDriver *drv, _EGLDisplay *disp)
{
	if (!dri2_initialize_genode_dri2(drv, disp)) {
		return  dri2_initialize_genode_swrast(drv, disp);
	}

	return EGL_TRUE;
}

