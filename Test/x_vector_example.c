#include <stdio.h>
#include <Xone/x_vector.h>

#pragma comment(lib, "Xone")

typedef struct {
	unsigned int id;
	unsigned int count;
} objtype;

void x_vector_example() {
	objtype object = { 0, 1 };
	x_vector* vector = vector_create();
	vector_push(vector, &object);
	vector_push(vector, &(objtype){1, 2});

	for (unsigned int i = 0; i < vector->count; i++) {
		printf("%d. id = %d, count = %d\n", i, ((objtype*)vector->data[i])->id, ((objtype*)vector->data[i])->count);
	}
}