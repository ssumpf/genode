/* needed since there exists a 'util/list.h' in mesa */
#include <../include/util/list.h>
#include <blit/blit.h>
#include <window.h>

#include <base/log.h>

extern "C" {
#include <platform.h>
}


void genode_framebuffer_refresh(Genode_egl_window *win, int x, int y, int w, int h)
{
	Window *window = static_cast<Window *>(win);
	window->framebuffer->refresh(x, y, w, h);
}


void genode_blit(void const *src, unsigned src_w, void *dst, unsigned dst_w, int w, int h)
{
	blit(src, src_w, dst, dst_w, w, h);
}

/* defined in dde_linux intel */
//void start_framebuffer_driver(Genode::Env &env);

int genode_start_intel_fb_drv()
{
	//start_framebuffer_driver(*genode_env);
	Genode::error(__func__, "not implemented");
	return 1;
}
