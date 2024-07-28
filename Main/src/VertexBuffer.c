#include "VertexBuffer.h"
#include "gl_debug.h"

VertexBuffer vbo_create(const void* data, unsigned int size) {
    VertexBuffer vbo;
    GLCall(glGenBuffers(1, &vbo.id));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo.id));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    return vbo;
}

void vbo_delete(VertexBuffer vbo) {
    GLCall(glDeleteBuffers(1, &vbo.id));
}

void vbo_bind(VertexBuffer vbo) {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo.id));
}

void vbo_unbind() {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}