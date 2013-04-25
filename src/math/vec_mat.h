#ifndef VEC_MAT
#define VEC_MAT

#include "types.h" 

typedef ft vec4[4];
typedef ft vec3[3];
typedef vec4 mat4[4];

/* Vector functions */
void add_vec3(vec3 a, vec3 b, vec3 c);
void add_vec4(vec4 a, vec4 b, vec4 c);


void mag_vec3(vec3 a, float* mag);
void scale_vec3(vec3 a, float factor);
void dotprod_vec3(vec3 a, vec3 b, ft* result);
void crossprod_vec3(vec3 a, vec3 b, vec3 c);
void normalize_vec3(vec3 a);
void copy_vec3(vec3 a, vec3 b);
void copy_vec4(vec4 a, vec4 b);

/* Matrix functions */
void add_mat4(mat4 a, mat4 b, mat4 c);
void copy_mat4(mat4 a, mat4 b);

void mult_mat4(mat4 a, mat4 b, mat4 c);

void mult_vec4mat4(vec4 a, mat4 b, vec4 c);

#endif
