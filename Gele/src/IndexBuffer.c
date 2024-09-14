#include "IndexBuffer.h"
#include "gl_debug.h"

IndexBuffer ibo_create(const unsigned int* data, unsigned int count) {
    assert(sizeof(unsigned int) == sizeof(GLuint));
    IndexBuffer ibo;
    GLCall(glGenBuffers(1, &ibo.id));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.id));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    ibo.count = count;
    return ibo;
}

void ibo_delete(IndexBuffer ibo) {
    GLCall(glDeleteBuffers(1, &ibo.id));
}

void ibo_bind(IndexBuffer ibo) {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.id));
}

void ibo_unbind() {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}