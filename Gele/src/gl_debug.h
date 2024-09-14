#pragma once
#include <glad/glad.h>
#include <stdio.h>
#include <assert.h>

#define GLCall(x) GLClearError();\
	x;\
	assert(GLLogCall(#x, __FILE__, __LINE__))

#define GLErrorPrint(x) printf("[OpenGL error] (%d): %s %s line %d\n", x, function, file, line)

void GLClearError();
unsigned char GLLogCall(const char* function, const char* file, unsigned int line);