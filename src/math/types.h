#ifndef ESGMKT_MATH_TYPES
#define ESGMKT_MATH_TYPES

#ifdef USE_GL_TYPES
#ifndef __gl2_h_
#error "using GL_TYPES without opengl types included"    
#endif
typedef GLfloat ft;
#else
typedef float ft;
#endif

#endif

