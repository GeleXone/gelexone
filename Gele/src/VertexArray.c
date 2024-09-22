#include "VertexArray.h"
#include "gl_debug.h"

VertexArray vao_create() {
	VertexArray vao;
	GLCall(glGenVertexArrays(1, &vao.id));
	return vao;
}

void vao_bind(VertexArray vao) {
	GLCall(glBindVertexArray(vao.id));
}

void vao_unbind() {
	GLCall(glBindVertexArray(0));
}

void vao_add_buffer(VertexArray vao, VertexBuffer vbo, VertexBufferLayout* vbl) {
	vao_bind(vao);
	vbo_bind(vbo);
	unsigned int offset = 0;
	for (unsigned int i = 0; i < vbl->count; i++)
	{
		VertexBufferLayoutElement element = vbl->elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalised, vbl->stride, (const void*)offset));
		offset += element.count * vbl_get_type_size(element.type);
	}
}
