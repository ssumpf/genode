/* needed since there exists a 'util/list.h' in mesa */
#include <../include/util/list.h>
#include <window.h>

extern "C" {
#include <platform.h>
}


void genode_framebuffer_refresh(Genode_egl_window *win, int x, int y, int w, int h)
{
	Window *window = static_cast<Window *>(win);
	window->framebuffer->refresh(x, y, w, h);
}


