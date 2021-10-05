#ifndef _X11__X_H_
#define _X11__X_H_


/* X11/Xmd.h */

typedef unsigned int CARD32;


/* X11/Xdefs.h */

typedef CARD32 XID;


/* X11/X.h */

typedef XID Window;
typedef XID Colormap;

#define None        0L
#define InputOutput 1


/* X11/Xlib.h */

#define Bool   int
#define Status int
#define True   1
#define False  0

typedef struct { void *dummy; } Display;
typedef struct { void *dummy; } Visual;
typedef struct { void *dummy; } XWindowAttributes;
typedef struct { void *dummy; } XSetWindowAttributes;
typedef struct { void *dummy; } XErrorEvent;

typedef union _XEvent {
	int         type;
	XErrorEvent xerror;
} XEvent;

extern Display * XOpenDisplay(char *name);
extern int XCloseDisplay(Display *);
extern int XPending(Display *);
extern int XNextEvent(Display *, XEvent *);
extern Window XDefaultRootWindow(Display *);
extern Window XCreateWindow( Display *, Window, int, int, unsigned int, unsigned int, unsigned int, int, unsigned int, Visual *, unsigned long, XSetWindowAttributes *);
extern int XDestroyWindow(Display *, Window);
extern int XSync(Display *, Bool);
extern int XFree(void *);
extern int XMapWindow(Display *, Window);
extern Colormap XCreateColormap(Display *, Window, Visual *, int);

typedef int (*XErrorHandler) (Display *, XErrorEvent *);
extern XErrorHandler XSetErrorHandler(XErrorHandler);

#define DefaultScreen(display) (0)


/* X11/Xutil.h */

typedef struct {
	Visual *visual;
} XVisualInfo;


#endif /* _X11__X_H_ */

