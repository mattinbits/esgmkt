#ifndef VEC_MAT
#define VEC_MAT

#include "types.h" 

typedef ft vec4[4];
typedef ft vec3[3];
typedef vec4 mat4[4];


void add_vec3(vec3 a, vec3 b, vec3 c);
void add_vec4(vec4 a, vec4 b, vec4 c);
void add_mat4(mat4 a, mat4 b, mat4 c);

void mag_vec3(vec3 a, float* mag);
void scale_vec3(vec3 a float* factor);
void mag_vec4(vec4 a, float* mag);
void scale_vec4(vec4 a float* factor);

#endif
