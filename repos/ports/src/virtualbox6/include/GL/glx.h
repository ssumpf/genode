#ifndef _GL__GLX_H_
#define _GL__GLX_H_

#include <X11/Xlib.h>
#include <GL/gl.h>


#ifdef __cplusplus
extern "C" {
#endif


/*
 * Tokens for glXChooseVisual and glXGetConfig:
 */
//#define GLX_USE_GL              1
//#define GLX_BUFFER_SIZE         2
//#define GLX_LEVEL               3
#define GLX_RGBA                4
#define GLX_DOUBLEBUFFER        5
//#define GLX_STEREO              6
//#define GLX_AUX_BUFFERS         7
#define GLX_RED_SIZE            8
#define GLX_GREEN_SIZE          9
#define GLX_BLUE_SIZE           10
//#define GLX_ALPHA_SIZE          11
//#define GLX_DEPTH_SIZE          12
//#define GLX_STENCIL_SIZE        13
//#define GLX_ACCUM_RED_SIZE      14
//#define GLX_ACCUM_GREEN_SIZE    15
//#define GLX_ACCUM_BLUE_SIZE     16
//#define GLX_ACCUM_ALPHA_SIZE    17

typedef void * GLXContext;
typedef XID    GLXDrawable;

extern Bool glXQueryVersion(Display *dpy, int *maj, int *min);

extern GLXContext glXCreateContext(Display *dpy, XVisualInfo *vis, GLXContext shareList, Bool direct);

extern XVisualInfo* glXChooseVisual(Display *dpy, int screen, int *attribList);

extern Bool glXMakeCurrent(Display *dpy, GLXDrawable drawable, GLXContext ctx);

extern void (*glXGetProcAddress(const GLubyte *procname))(void);


#ifdef __cplusplus
}
#endif

#endif /* _GL__GLX_H_ */
