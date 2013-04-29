/*
 * types.h
 * Defines floating point types with a switch for OpenGL or non-OpenGL contexts
 *
 * This file is part of esgmkt (OpenGL ES 2.0 Game Kit), 
 * Copyright Matthew Livesey 2013 (matt.computes@gmail.com)
 * 
 * This work is distributed under the BSD licence, a copy of which is
 * distributed with this work.
 * 
 * esgmkt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

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

