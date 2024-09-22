#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

typedef struct {
	unsigned int id;
} VertexArray;

VertexArray vao_create();
void vao_bind(VertexArray vao);
void vao_unbind();
void vao_add_buffer(VertexArray vao, VertexBuffer vbo, VertexBufferLayout* vbl);
