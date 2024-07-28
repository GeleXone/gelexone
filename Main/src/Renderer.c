#include "Renderer.h"

void render_clear() {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void render_draw(VertexArray vao, IndexBuffer ibo, Shader shader) {
	vao_bind(vao);
	ibo_bind(ibo);
	shader_bind(shader);

	GLCall(glDrawElements(GL_TRIANGLES, ibo.count, GL_UNSIGNED_INT, 0));
}