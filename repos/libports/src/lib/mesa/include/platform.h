#ifndef _PLATFORM_H_
#define _PLATFORM_H_

struct Genode_egl_window;
void genode_framebuffer_refresh(struct Genode_egl_window *win, int x, int y, int w, int h);

#endif
