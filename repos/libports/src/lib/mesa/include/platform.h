#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#ifdef __cplusplus
extern Genode::Env *genode_env;
#endif

struct Genode_egl_window;
void genode_framebuffer_refresh(struct Genode_egl_window *win, int x, int y, int w, int h);
void genode_blit(void const *src, unsigned src_w, void *dst, unsigned dst_w, int w, int h);
int  genode_start_intel_fb_drv(void);

#endif
