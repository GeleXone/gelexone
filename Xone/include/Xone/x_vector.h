#pragma once
#include "Xone/xone.h"
#include <stdio.h>

typedef struct {
	void** data;
	size_t count;
	size_t capacity;
} x_vector;

static int _vector_resize(x_vector* vector, size_t capacity);
x_vector* vector_create();
void vector_free(x_vector*);
int vector_push(x_vector* vector, void* x);

//прикол для векторов любого типа. работает как template, но без C++
#define X_VECTOR_TYPED_DEF(type) typedef struct {\
	##type##* data;\
	size_t count;\
	size_t capacity;\
} x_vector_##type##;\

X_VECTOR_TYPED_DEF(float)