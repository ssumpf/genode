#ifndef _X11__X_H_
#define _X11__X_H_


/* X11/Xmd.h */

typedef unsigned int CARD32;


/* X11/X.h */

typedef CARD32 XID;
typedef CARD32 VisualID;
typedef XID    Window;
typedef XID    Colormap;

#define None        0L
#define InputOutput 1
#define AllocNone   0

#define StructureNotifyMask (1L<<17)


/* X11/Xlib.h */

#define Bool   int
#define Status int
#define True   1
#define False  0

typedef struct { void *dummy; } Display;
typedef struct { void *dummy; } Screen;
typedef struct { void *dummy; } Visual;

typedef struct {
//	int x, y;			/* location of window */
//	int width, height;		/* width and height of window */
//	int border_width;		/* border width of window */
//	int depth;          	/* depth of window */
//	Visual *visual;		/* the associated visual structure */
//	Window root;        	/* root of screen containing window */
//#if defined(__cplusplus) || defined(c_plusplus)
//	int c_class;		/* C++ InputOutput, InputOnly*/
//#else
//	int class;			/* InputOutput, InputOnly*/
//#endif
//	int bit_gravity;		/* one of bit gravity values */
//	int win_gravity;		/* one of the window gravity values */
//	int backing_store;		/* NotUseful, WhenMapped, Always */
//	unsigned long backing_planes;/* planes to be preserved if possible */
//	unsigned long backing_pixel;/* value to be used when restoring planes */
//	Bool save_under;		/* boolean, should bits under be saved? */
//	Colormap colormap;		/* color map to be associated with window */
//	Bool map_installed;		/* boolean, is color map currently installed*/
//	int map_state;		/* IsUnmapped, IsUnviewable, IsViewable */
//	long all_event_masks;	/* set of events all people have interest in*/
//	long your_event_mask;	/* my event mask */
//	long do_not_propagate_mask; /* set of events that should not propagate */
//	Bool override_redirect;	/* boolean value for override-redirect */
	Screen *screen;
} XWindowAttributes;

typedef struct {
//	Pixmap background_pixmap;	/* background or None or ParentRelative */
	unsigned long background_pixel;
//	Pixmap border_pixmap;	/* border of the window */
	unsigned long border_pixel;
//	int bit_gravity;		/* one of bit gravity values */
//	int win_gravity;		/* one of the window gravity values */
//	int backing_store;		/* NotUseful, WhenMapped, Always */
//	unsigned long backing_planes;/* planes to be preseved if possible */
//	unsigned long backing_pixel;/* value to use in restoring planes */
//	Bool save_under;		/* should bits under be saved? (popups) */
	long event_mask;
//	long do_not_propagate_mask;	/* set of events that should not propagate */
	Bool override_redirect;
	Colormap colormap;
//	Cursor cursor;		/* cursor to be displayed (or None) */
} XSetWindowAttributes;

typedef struct { unsigned char error_code; } XErrorEvent;

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
extern Status XGetWindowAttributes(Display *, Window, XWindowAttributes *);
extern int XScreenNumberOfScreen(Screen *);

typedef int (*XErrorHandler) (Display *, XErrorEvent *);
extern XErrorHandler XSetErrorHandler(XErrorHandler);

#define DefaultScreen(display) (0)


/* X11/Xutil.h */

typedef struct {
	Visual *visual;
	VisualID visualid;
	int screen;
	int depth;
//#if defined(__cplusplus) || defined(c_plusplus)
//	int c_class;					/* C++ */
//#else
//	int class;
//#endif
	unsigned long red_mask;
	unsigned long green_mask;
	unsigned long blue_mask;
	int colormap_size;
	int bits_per_rgb;
} XVisualInfo;


#endif /* _X11__X_H_ */

