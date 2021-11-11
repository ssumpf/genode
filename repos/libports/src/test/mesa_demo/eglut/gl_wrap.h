#ifndef GL_WRAP_H
#define GL_WRAP_H

#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#else
#  include <GL/gl.h>
#  include <GL/glext.h>
#endif

#ifndef GLAPIENTRY
#define GLAPIENTRY
#endif

#endif /* ! GL_WRAP_H */
