#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#ifdef __cplusplus
extern Genode::Env *genode_env;
#endif

#include <EGL/egl.h>
struct Genode_egl_window;
void genode_framebuffer_refresh(struct Genode_egl_window *win, int x, int y, int w, int h);
void genode_blit(void const *src, unsigned src_w, void *dst, unsigned dst_w, int w, int h);
void genode_drm_init();

struct _EGLSurface;
struct _EGLDriver;
struct _EGLConfig;
struct _EGLDisplay;

_EGLSurface *
dri2_genode_create_window_surface(_EGLDriver *drv, _EGLDisplay *disp,
                                  _EGLConfig *conf, void *native_window,
                                  const EGLint *attrib_list);
EGLBoolean
dri2_genode_destroy_surface(_EGLDriver *drv, _EGLDisplay *disp, _EGLSurface *surf);

_EGLSurface *
dri2_genode_create_pixmap_surface(_EGLDriver *drv, _EGLDisplay *disp,
                                 _EGLConfig *conf, void *native_window,
                                 const EGLint *attrib_list);

EGLBoolean
dri2_genode_swap_interval(_EGLDriver *drv, _EGLDisplay *disp,
                          _EGLSurface *surf, EGLint interval);

#endif
