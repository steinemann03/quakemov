#pragma once
#include "gl_math.h"
//vector
vec3 vector_combine(vec3 a, vec3 b) {
	for (int i = 0; i < 3; i++) a.f[i] += b.f[i];
	return a;
}
vec3 vector_subtract(vec3 a, vec3 b) {
	for (int i = 0; i < 3; i++) a.f[i] -= b.f[i];
	return a;
}
vec3 vector_scalar(vec3 a, float b) {
	for (int i = 0; i < 3; i++) a.f[i] *= b;
	return a;
}
vec4 vector4_scalar(vec4 a, float b) {
	for (int i = 0; i < 4; i++) a.f[i] *= b;
	return a;
}
vec3 vector_multi(vec3 a, vec3 b) {
	for (int i = 0; i < 3; i++) a.f[i] *= b.f[i];
	return a;
}
int vector_isEqual(vec3 a, vec3 b) {
	return (
		a.f[0] == b.f[0] &&
		a.f[1] == b.f[1] &&
		a.f[2] == b.f[2]
		);
}
vec3 vector_negate(vec3 vec) {
	for (int i = 0; i < 3; i++)
		vec.f[i] *= -1;
	return vec;
}
float vector_lenght(vec3 dir) {
	return sqrtf(dir.f[0] * dir.f[0] + dir.f[1] * dir.f[1] + dir.f[2] * dir.f[2]);
}
float vector_dot(vec3 a, vec3 b) {
	return a.f[0] * b.f[0] + a.f[1] * b.f[1] + a.f[2] * b.f[2];
}
vec3 vector_normalize(vec3 vec) {
	float len = vector_lenght(vec);
	if (len != 0.f) {
		return (vec3) { vec.f[0] / len, vec.f[1] / len, vec.f[2] / len };
	}
	else
		return (vec3) { 0, 0, 0 };
}
vec3 vector_cross(vec3 a, vec3 b) {
	vec3 normal;
	normal.f[0] = a.f[1] * b.f[2] - a.f[2] * b.f[1];
	normal.f[1] = a.f[2] * b.f[0] - a.f[0] * b.f[2];
	normal.f[2] = a.f[0] * b.f[1] - a.f[1] * b.f[0];
	return normal;
}

//matrix
mat4 matrix_identity() {
	mat4 mat = { 0 };
	for (int i = 0; i < 4; i++) mat.m[i][i] = 1;
	return mat;
}
mat4 matrix_perspective(float dfov, float aspect, float near, float far) {
	mat4 mat = { 0 };
	float fov = dfov * (PI / 180);
	float tanHalfFOV = tanf(fov / 2.0f);
	mat.m[0][0] = 1.0f / (aspect * tanHalfFOV);
	mat.m[1][1] = 1.0f / tanHalfFOV;
	mat.m[2][2] = -(far + near) / (far - near);
	mat.m[2][3] = -1.0f;
	mat.m[3][2] = -(2.0f * far * near) / (far - near);
	return mat;
}
mat4 matrix_ortho(float left, float right, float bottom, float top, float near, float far) {
	mat4 mat = { 0 };
	mat.m[0][0] = 2.0f / (right - left);
	mat.m[1][1] = 2.0f / (top - bottom);
	mat.m[2][2] = -(2 / (far - near));
	mat.m[3][3] = 1;
	mat.m[3][0] = -((right + left) / (right - left));
	mat.m[3][1] = -((top + bottom) / (top - bottom));
	mat.m[3][2] = -((far + near) / (far - near));
	return mat;
}
mat4 matrix_scalar(mat4 a, float b) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			a.m[i][j] *= b;
	return a;
}
mat4 matrix_multi(mat4 a, mat4 b) {
	mat4 result = { 0 };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				result.m[i][j] += a.m[i][k] * b.m[k][j];
	return result;
}
mat4 matrix_rotate(mat4 mat, vec4 axis_angle) { //ty chatgpt
	vec3 axis = { { axis_angle.f[0], axis_angle.f[1], axis_angle.f[2] } };
	float angle = axis_angle.f[3];

	float axis_length = sqrt(axis.f[0] * axis.f[0] + axis.f[1] * axis.f[1] + axis.f[2] * axis.f[2]);
	axis.f[0] /= axis_length;
	axis.f[1] /= axis_length;
	axis.f[2] /= axis_length;

	float cos_theta = cos(angle);
	float sin_theta = sin(angle);
	float one_minus_cos = 1.0f - cos_theta;

	float x = axis.f[0], y = axis.f[1], z = axis.f[2];
	mat4 rotation = { 0 };
	rotation.m[0][0] = cos_theta + x * x * one_minus_cos;
	rotation.m[0][1] = x * y * one_minus_cos - z * sin_theta;
	rotation.m[0][2] = x * z * one_minus_cos + y * sin_theta;
	rotation.m[0][3] = 0.0f;
	rotation.m[1][0] = y * x * one_minus_cos + z * sin_theta;
	rotation.m[1][1] = cos_theta + y * y * one_minus_cos;
	rotation.m[1][2] = y * z * one_minus_cos - x * sin_theta;
	rotation.m[1][3] = 0.0f;
	rotation.m[2][0] = z * x * one_minus_cos - y * sin_theta;
	rotation.m[2][1] = z * y * one_minus_cos + x * sin_theta;
	rotation.m[2][2] = cos_theta + z * z * one_minus_cos;
	rotation.m[2][3] = 0.0f;
	rotation.m[3][0] = 0.0f;
	rotation.m[3][1] = 0.0f;
	rotation.m[3][2] = 0.0f;
	rotation.m[3][3] = 1.0f;

	return matrix_multi(mat, rotation);
}
mat4 matrix_translate(mat4 mat, vec3 vec) {
	mat4 mat_translate = matrix_identity();
	for (int i = 0; i < 3; i++) mat_translate.m[3][i] = vec.f[i];
	return matrix_multi(mat, mat_translate);
}
mat4 matrix_scale(mat4 mat, vec3 scale) {
	for (int i = 0; i < 3; i++) mat.m[i][i] *= scale.f[i];
	return mat;
}