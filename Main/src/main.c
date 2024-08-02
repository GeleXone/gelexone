#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma comment(lib, "glfw3")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glad")
#pragma comment(lib, "Xone")

#include "Renderer.h"
#include "Texture.h"

float positions[4 * 4] = {
	-0.5f, -0.5f, 0.0f, 0.0f,
	 0.5f, -0.5f, 1.0f, 0.0f,
	 0.5f,  0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f
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

	//blending
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//массив вершин
	VertexArray vao = vao_create();

	//буфер вершин
	VertexBuffer vbo = vbo_create(positions, 4 * 4 * sizeof(float));

	//layout буфера вершин
	VertexBufferLayout* vbl = vbl_create();
	vbl_push(vbl, GL_FLOAT, 2, GL_FALSE);
	vbl_push(vbl, GL_FLOAT, 2, GL_FALSE);
	vao_add_buffer(vao, vbo, vbl);

	//буфер индексов
	IndexBuffer ibo = ibo_create(indices, 6);
	
	//шейдер
	ShaderProgramSource src = ParseShader("res/shaders/textured.shader");
	printf("vertex shader:\n%s\n", src.VertexSource);
	printf("fragment shader:\n%s\n", src.FragmentSource);
	Shader shader = shader_create(src.VertexSource, src.FragmentSource);
	shader_bind(shader);

	//текстура
	Texture texture = texture_create("res/textures/epic_yozhik.jpg");
	texture_bind(texture);
	shader_set_uniform1i(shader, "u_Texture", 0);

	//сбрасываем все бинды буферов для отладки
	shader_unbind();
	vao_unbind();
	vbo_unbind();
	ibo_unbind();

	//рендер
	GLCall(glClearColor(0.0f,0.0f,1.0f,0.0f));
	float r = 0.2f, increment = 0.05f;
	while (!glfwWindowShouldClose(window))
	{
		render_clear();

		/*shader_set_uniform4f(shader, "u_Color", r, r, 0, 0.0f);
		if (r > 1.0f) {
			increment = -0.05f;
		} else if (r < 0.0f) {
			increment = 0.05f;
		}
		r += increment;*/

		render_draw(vao, ibo, shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//завершение работы
	glfwTerminate();
	return 0;
}