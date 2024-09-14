#include "gl_debug.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

unsigned char GLLogCall(const char* function, const char* file, unsigned int line)
{
	GLenum error;
	while (error = glGetError())
	{
		GLErrorPrint(error);
		return GL_FALSE;
	}
	return GL_TRUE;
}