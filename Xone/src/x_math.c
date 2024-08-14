#include "x_math.h"
#include <math.h>

float x_sqrt(float number)
{
	int i;
	float x, y;
	x = number * 0.5f;
	y = number;
	i = *(int*)&y;
	i = 0x5f375a86 - (i >> 1);
	y = *(float*)&i;
	y = y * (1.5f - (x * y * y));
	y = y * (1.5f - (x * y * y));
	return number * y;
}

// отличающиеся функции векторов большей размерности
void vec3_mul_cross(vec3 r, vec3 a, vec3 b)
{
	r[0] = a[1] * b[2] - a[2] * b[1];
	r[1] = a[2] * b[0] - a[0] * b[2];
	r[2] = a[0] * b[1] - a[1] * b[0];
}
void vec4_mul_cross(vec4 r, vec4 a, vec4 b)
{
	r[0] = a[1] * b[2] - a[2] * b[1];
	r[1] = a[2] * b[0] - a[0] * b[2];
	r[2] = a[0] * b[1] - a[1] * b[0];
	r[3] = 1.f;
}

// matrix[n][m] - n столбец, m строка.
void mat4_copy(mat4 r, mat4 src)
{
	float* ptr = (float*)r;
	float* srcptr = (float*)src;
	//assert(ptr != srcptr);
	for (int i = 0; i < sizeof(mat4) / sizeof(float); i++)
	{
		ptr[i] = srcptr[i];
	}
}
void mat4_transpose(mat4 r, mat4 M)
{
	mat4 temp;
	for (int col = 0; col < 4; col++)
		for (int row = 0; row < 4; row++)
			temp[col][row] = M[row][col];
	mat4_copy(r, temp);
}

void mat4_create_translation(mat4 M, float x, float y, float z)
{
	mat4 temp = { 
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{x,y,z,1} 
	};
	mat4_copy(M, temp);
}
void mat4_create_scaling(mat4 M, float x, float y, float z)
{
	mat4 temp = { 
		{x,0,0,0},
		{0,y,0,0},
		{0,0,z,0},
		{0,0,0,1} 
	};
	mat4_copy(M, temp);
}
void mat4_create_ortho(mat4 M, float left, float right, float bottom, float top, float zNear, float zFar)
{
	mat4 temp = { 
		{(2.0f) / (right - left),			0,									0,							0},
		{0,									(2.0f) / (top - bottom),			0,							0},
		{0,									0,									(1.0f) / (zFar - zNear),	0},
		{-(right + left) / (right - left),	-(top + bottom) / (top - bottom),	-zNear / (zFar - zNear),	1}
	};
	mat4_copy(M, temp);
}
void mat4_create_perspective(mat4 M, float left, float right, float bottom, float top, float zNear, float zFar)
{
	mat4 temp = { 
		{(2.0f * zNear) / (right - left),0,(right+left)/(right-left),	0},
		{0,	(2.0f * zNear) / (top - bottom),(top+bottom)/(top-bottom),	0},
		{0,	0, -((zFar+zNear) / (zFar - zNear)),	-((2 * zFar * zNear) / (zFar - zNear))},
		{0,	0,	-1, 0}
	};
	mat4_copy(M, temp);
}

void mat4_create_rotation_z(mat4 M, float theta)
{
	mat4 temp = {
		cosf(theta), sinf(theta), 0, 0,
		-sinf(theta),cosf(theta), 0, 0,
		0,			0,			1, 0,
		0,			0,			0, 1
	};
	mat4_copy(M, temp);
}
void mat4_create_rotation_y(mat4 M, float theta)
{
	mat4 temp = {
		cosf(theta), 0, -sinf(theta), 0,
				 0, 1,           0, 0,
		sinf(theta), 0,  cosf(theta), 0,
				 0, 0,           0, 1
	};
	mat4_copy(M, temp);
}
void mat4_create_rotation_x(mat4 M, float theta)
{
	mat4 temp = {
		1, 0, 0, 0,
		0, cosf(theta), sinf(theta), 0,
		0, -sinf(theta), cosf(theta), 0,
		0, 0, 0, 1
	};
	mat4_copy(M, temp);
}


void mat4_mul_vec4(vec4 r, mat4 M, vec4 v)
{
	vec4 temp;
	for (int row = 0; row < 4; row++)
	{
		float sum = 0;
		for (int col = 0; col < 4; col++)
		{
			sum += M[col][row] * v[col];
		}
		temp[row] = sum;
	}
	vec4_copy(r, temp);
}

void mat4_mul_mat4(mat4 r, mat4 left, mat4 right) {
	if (right == (void*)0) {
		mat4_copy(r, left);
		return;
	}
	if (left == (void*)0) {
		mat4_copy(r, right);
		return;
	}
	mat4 temp = {
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	};
	for (unsigned char i = 0; i < 4; i++)
		for (unsigned char j = 0; j < 4; j++)
			for (unsigned char k = 0; k < 4; k++)
				temp[j][i] += left[k][i] * right[j][k];
	mat4_copy(r, temp);
}