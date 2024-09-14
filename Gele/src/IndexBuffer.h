#pragma once

typedef struct {
	unsigned int id;
	unsigned int count;
} IndexBuffer;

IndexBuffer ibo_create(const unsigned int* data, unsigned int count);
void ibo_delete(IndexBuffer ibo);
void ibo_bind(IndexBuffer ibo);
void ibo_unbind();