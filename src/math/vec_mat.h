/*
 * vec_mat.h
 * Header file for library of vector and matrix maths functions
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

#ifndef VEC_MAT
#define VEC_MAT

#include "types.h" 

typedef ft vec4[4];
typedef ft vec3[3];
/*
 *!! Need to be stored column major !!
 */
typedef vec4 mat4[4];

/* Vector functions */
void create_vec3(vec3 a, ft a1, ft a2, ft a3);
void create_vec4(vec4 a, ft a1, ft a2, ft a3, ft a4);

void add_vec3(vec3 a, vec3 b, /*return*/vec3 c);
void add_vec4(vec4 a, vec4 b, /*return*/vec4 c);


void mag_vec3(vec3 a, float* mag);
void scale_vec3(vec3 a, float factor);
void dotprod_vec3(vec3 a, vec3 b, ft* result);
void crossprod_vec3(vec3 a, vec3 b, /*return*/vec3 c);
void normalize_vec3(vec3 a);
void copy_vec3(vec3 a, /*return*/vec3 b);
void copy_vec4(vec4 a, /*return*/vec4 b);

/* Matrix functions */
void create_mat4(/*return*/mat4 a, vec4 col0, vec4 col1, vec4 col2, vec4 col3);
void getidentity_mat4(/*return*/mat4 a);
void add_mat4(mat4 a, mat4 b, mat4 c);
void copy_mat4(mat4 a, mat4 b);

void mult_mat4(mat4 a, mat4 b, mat4 c);

void mult_mat4vec4(mat4 a, vec4 b, vec4 c);

#endif
