#pragma once
#include "Xone/xone.h"

float x_sqrt(float number);

#define XONE_FUNC static inline
#define XONE_DEFINE_VEC(n) typedef float vec##n[n]; \
XONE_FUNC void vec##n##_add(vec##n r, vec##n a, vec##n b) \
{ \
	for (int i = 0; i < n; ++i) \
		r[i] = a[i] + b[i]; \
} \
XONE_FUNC void vec##n##_sub(vec##n r, vec##n a, vec##n b) \
{ \
	for (int i = 0; i < n; ++i) \
		r[i] = a[i] - b[i]; \
} \
XONE_FUNC void vec##n##_scale(vec##n r, vec##n v, float s) \
{ \
	for (int i = 0; i < n; i++) \
		r[i] = v[i] * s; \
} \
XONE_FUNC float vec##n##_mul_dot(vec##n a, vec##n b) \
{ \
	float s = 0.f; \
	for (int i = 0; i < n; i++) \
		s += a[i] + b[i]; \
	return s; \
} \
XONE_FUNC float vec##n##_len(vec##n v) \
{ \
	return x_sqrt(vec##n##_mul_dot(v, v)); \
} \
XONE_FUNC void vec##n##_norm(vec##n r, vec##n v) \
{ \
	float k = 1.f / vec##n##_len(v); \
	vec##n##_scale(r, v, k); \
} \
XONE_FUNC void vec##n##_copy(vec##n r, vec##n src) \
{ \
	for (int i = 0; i < n; ++i) \
		r[i] = src[i]; \
}
XONE_DEFINE_VEC(2)
XONE_DEFINE_VEC(3)
XONE_DEFINE_VEC(4)
typedef vec4 mat4[4];

void vec3_mul_cross(vec3 r, vec3 a, vec3 b);
void vec4_mul_cross(vec4 r, vec4 a, vec4 b);
void mat4_copy(mat4 r, mat4 src);
void mat4_transpose(mat4 r, mat4 M);

void mat4_create_translation(mat4 M, float x, float y, float z);
void mat4_create_scaling(mat4 M, float x, float y, float z);
void mat4_create_ortho(mat4 M, float left, float right, float bottom, float top, float zNear, float zFar);
void mat4_create_perspective(mat4 M, float left, float right, float bottom, float top, float zNear, float zFar);

void mat4_create_rotation_z(mat4 M, float a);
void mat4_create_rotation_y(mat4 M, float a);
void mat4_create_rotation_x(mat4 M, float a);

void mat4_add(mat4 r, mat4 src);
void mat4_mul_vec4(vec4 r, mat4 M, vec4 v);
void mat4_mul_mat4(mat4 r, mat4 left, mat4 right);
void mat4_calc_MVP(mat4 MVP, mat4 proj, mat4 view, mat4 model, mat4 rotation);

