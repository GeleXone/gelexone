#pragma once

typedef struct {
	unsigned int id;
} VertexBuffer;

// size = кол-во вершин * размер вершины * sizeof(type)
VertexBuffer vbo_create(const void* data, unsigned int size);
void vbo_delete(VertexBuffer vbo);
void vbo_bind(VertexBuffer vbo);
void vbo_unbind();
