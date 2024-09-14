#include "Xone/x_vector.h"
#include "malloc.h"

const size_t VECTOR_INIT_CAPACITY = 4;

x_vector* vector_create() {
	x_vector* vector = (x_vector*)malloc(sizeof(x_vector));
	if (!vector) return NULL;

	vector->count = 0;
	vector->capacity = VECTOR_INIT_CAPACITY;
	
	vector->data = (void*)malloc(vector->capacity * sizeof(void*));

	if (!vector->data) {
		vector_free(vector);
		return NULL;
	}

	return vector;
}

void vector_free(x_vector* vector) {
	if (vector) {
		if (vector->data)
			free(vector->data);
		free(vector);
	}
}

static int _vector_resize(x_vector* vector, size_t capacity) {
	void** data = realloc(vector->data, capacity * sizeof(void*));
	vector->capacity = capacity;

	if (!data) return -1;
	if (data != vector->data)
		vector->data = data;
	data = NULL;

	return 0;
}

int vector_push(x_vector* vector, void* item) {
	if (!vector || !vector->data) return -1;

	if (vector->count == vector->capacity) {
		if (_vector_resize(vector, vector->capacity * 2) == -1)
			return -1;
	}

	vector->data[vector->count++] = item;

	return 0;
}