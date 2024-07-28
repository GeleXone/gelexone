#pragma once

typedef struct {
	unsigned int id;
} VertexBuffer;

VertexBuffer vbo_create(const void* data, unsigned int size);
void vbo_delete(VertexBuffer vbo);
void vbo_bind(VertexBuffer vbo);
void vbo_unbind();