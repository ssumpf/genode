#include <base/printf.h>

extern "C" {
#include "eglutint.h"
}


void _eglutNativeInitDisplay()
{
	PDBG("not implemented");
}


void _eglutNativeFiniDisplay(void)
{
	PDBG("not implemented");
}


void _eglutNativeEventLoop()
{
	PDBG("not implemented");
}


void _eglutNativeInitWindow(struct eglut_window *win, const char *title,
                            int x, int y, int w, int h)
{
	PDBG("not implmented");
}


void _eglutNativeFiniWindow(struct eglut_window *win)
{
	PDBG("not implemented");
}
