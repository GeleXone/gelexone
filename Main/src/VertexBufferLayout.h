#pragma once 

typedef struct {
	unsigned int type;
	unsigned char count; //предположительно количество параметров < 256
	unsigned char normalised;
} VertexBufferLayoutElement;

unsigned int vbl_get_type_size(unsigned int type);

#define LAYOUT_SIZE 10

typedef struct {
	unsigned int stride;
	unsigned int count;
	VertexBufferLayoutElement elements[LAYOUT_SIZE];
} VertexBufferLayout;

VertexBufferLayout* vbl_create();

void vbl_push(VertexBufferLayout* vbl, unsigned int type, unsigned int count, unsigned char normalised);