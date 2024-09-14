#include "VertexBufferLayout.h"
#include "gl_debug.h"
#include <malloc.h>

unsigned int vbl_get_type_size(unsigned int type) {
	switch (type) {
	case GL_FLOAT:			return 4;
	case GL_UNSIGNED_INT:	return 4;
	case GL_UNSIGNED_BYTE:	return 1;
	}
	assert(GL_FALSE);
	return 0;
}

VertexBufferLayout* vbl_create() {
	VertexBufferLayout* layout = (VertexBufferLayout*)malloc(sizeof(VertexBufferLayout));
	assert(layout);
	layout->count = 0;
	layout->stride = 0;
	for (int i = 0; i < LAYOUT_SIZE; i++)
		layout->elements[i] = (VertexBufferLayoutElement){ 0, 0, 0 };

	return layout;
}

void vbl_push(VertexBufferLayout* vbl, unsigned int type, unsigned int count, unsigned char normalised) {
	vbl->elements[vbl->count++] = (VertexBufferLayoutElement){ .type = type, .count = count, .normalised = normalised };
	vbl->stride += count * vbl_get_type_size(type);
}
