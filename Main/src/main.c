#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma comment(lib, "glfw3")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glad")
#pragma comment(lib, "Xone")

#include "Renderer.h"

float positions[4 * 2] = {
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	 0.5f,  0.5f,
	-0.5f,  0.5f
};

unsigned int indices[6] = {
	0, 1, 2,
	2, 3, 0
};

int main() {
	//инициализация
	if (!glfwInit()) {
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//окно
	GLFWwindow* window = glfwCreateWindow(500, 500, "gelexone render", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	printf("OpenGL version:\n%s\n", glGetString(GL_VERSION));

	//массив вершин
	VertexArray vao = vao_create();

	//буфер вершин
	VertexBuffer vbo = vbo_create(positions, 4 * 2 * sizeof(float));

	//layout буфера вершин
	VertexBufferLayout* vbl = vbl_create();
	vbl_push(vbl, GL_FLOAT, 2, GL_FALSE);
	vao_add_buffer(vao, vbo, vbl);

	//буфер индексов
	IndexBuffer ibo = ibo_create(indices, 6);
	
	//шейдер
	ShaderProgramSource src = ParseShader("shaders/shader.glsl");
	printf("vertex shader:\n%s\n", src.VertexSource);
	printf("fragment shader:\n%s\n", src.FragmentSource);
	Shader shader = shader_create(src.VertexSource, src.FragmentSource);
	shader_bind(shader);

	//переменные шейдера
	float r = 0.2f, increment = 0.05f;
	//рендер
	while (!glfwWindowShouldClose(window))
	{
		render_clear();

		shader_set_uniform4f(shader, "u_Color", r, r, 0, 0.0f);
		if (r > 1.0f) {
			increment = -0.05f;
		} else if (r < 0.0f) {
			increment = 0.05f;
		}
		r += increment;

		render_draw(vao, ibo, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//завершение работы
	glfwTerminate();
	return 0;
}