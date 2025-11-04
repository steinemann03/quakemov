#pragma once
#include <math.h>
#define PI 3.14159265358979323846

//math
typedef struct vec2 {
	float f[2];
} vec2;
typedef struct vec3 {
	float f[3];
} vec3;
typedef struct vec4 {
	float f[4];
} vec4;
typedef struct mat4 {
	float m[4][4];
} mat4;

//vector
vec3 vector_combine(vec3 a, vec3 b);
vec3 vector_subtract(vec3 a, vec3 b);
vec3 vector_scalar(vec3 a, float b);
vec4 vector4_scalar(vec4 a, float b);
vec3 vector_multi(vec3 a, vec3 b);
//vec3 vector_rotate3d(vec3 vec, vec3 rot);
//vec3 vector_rotate2d(vec3 vec, vec3 rot);
//void vector_normalize(vec3* rot);//bruh
//void vector_clamp(vec3* rot);//bruh
int vector_isEqual(vec3 a, vec3 b);
vec3 vector_negate(vec3 vec);
float vector_lenght(vec3 dir);
float vector_dot(vec3 a, vec3 b);
vec3 vector_normalize(vec3 vec);
vec3 vector_cross(vec3 a, vec3 b);


//matrix
mat4 matrix_identity();
mat4 matrix_perspective(float fov, float aspect, float near, float far);
mat4 matrix_ortho(float left, float right, float bottom, float top, float near, float far);
mat4 matrix_scalar(mat4 a, float b);
mat4 matrix_multi(mat4 a, mat4 b);
mat4 matrix_rotate(mat4 mat, vec4 axis_angle);
mat4 matrix_translate(mat4 mat, vec3 vec);
mat4 matrix_scale(mat4 mat, vec3 scale);