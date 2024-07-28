#include "x_math.h"

float d_sqrt(float number)
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