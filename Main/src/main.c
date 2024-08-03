#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma comment(lib, "glfw3")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glad")
#pragma comment(lib, "Xone")

#include <Xone/x_math.h>

#include "Renderer.h"
#include "Texture.h"

float positions0[4 * 4] = {
	-0.5f, -0.5f, 0.0f, 0.0f,
	 0.5f, -0.5f, 1.0f, 0.0f,
	 0.5f,  0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f
};
float positions[4 * 4] = {
	100.0f, 100.0f, 0.0f, 0.0f,
	200.0f, 100.0f, 1.0f, 0.0f,
	200.0f, 200.0f, 1.0f, 1.0f,
	100.0f, 200.0f, 0.0f, 1.0f
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
	const unsigned int width = 400, height = 300;
	GLFWwindow* window = glfwCreateWindow(width, height, "gelexone render", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	printf("OpenGL version:\n%s\n", glGetString(GL_VERSION));

	//blending для png файлов с прозрачностью
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
	ShaderProgramSource src = ParseShader("res/shaders/projected.shader");
	printf("vertex shader:\n%s\n", src.VertexSource);
	printf("fragment shader:\n%s\n", src.FragmentSource);
	Shader shader = shader_create(src.VertexSource, src.FragmentSource);
	shader_bind(shader);

	//матрицы
	mat4 mvp, proj, view, model1, model2;
	mat4_create_ortho(proj, 0, width, 0, height, -1, 1);
	mat4_create_translation(view, 0, 0, 0);
	mat4_create_translation(model1, 0, 0, 0);
	mat4_create_translation(model2, 100, 0, 0);
	
	//текстура
	Texture texture0 = texture_create("res/textures/yozhik_emoji.png"),
		texture1 = texture_create("res/textures/epic_yozhik.png");
	texture_bind_slot(texture0, 0);
	texture_bind_slot(texture1, 1);

	//сбрасываем все бинды буферов для отладки
	shader_unbind();
	vao_unbind();
	vbo_unbind();
	ibo_unbind();

	//рендер
	GLCall(glClearColor(0.2f,0.7f,0.4f,0.0f));
	float r = 0.2f, increment = 0.05f;
	while (!glfwWindowShouldClose(window))
	{
		render_clear();

		{
			mat4_calc_MVP(mvp, proj, view, model1);
			shader_set_uniformMat4f(shader, "u_MVP", mvp);
			shader_set_uniform1i(shader, "u_Texture", 0);
			render_draw(vao, ibo, shader);
		}

		{
			mat4_calc_MVP(mvp, proj, view, model2);
			shader_set_uniformMat4f(shader, "u_MVP", mvp);
			shader_set_uniform1i(shader, "u_Texture", 1);
			render_draw(vao, ibo, shader);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//завершение работы
	glfwTerminate();
	return 0;
}