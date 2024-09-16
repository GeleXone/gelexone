#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#pragma comment(lib, "glfw3")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glad")
#pragma comment(lib, "Xone")

#include <Xone/x_math.h>

#include "Renderer.h"
#include "Texture.h"

#include "Camera.h"

#define VERTEXCOUNT 8 * 5
#define INDICESCOUNT 6 * 6

float positions[VERTEXCOUNT] = {
	-1.0f, -1.0f,  1.0f, 0.0f, 0.0f, //0
	-1.0f,  1.0f,  1.0f, 0.0f, 1.0f, //1
	 1.0f,  1.0f,  1.0f, 1.0f, 1.0f, //2
	 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, //3

	 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, //4
	 1.0f,  1.0f, -1.0f, 0.0f, 1.0f, //5
	-1.0f,  1.0f, -1.0f, 1.0f, 1.0f, //6
	-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, //7
};
unsigned int indices[INDICESCOUNT] = {
	0, 1, 7, //лево
	7, 6, 1,
	0, 7, 4, //низ
	4, 3, 0,
	2, 3, 4, //право
	4, 5, 2,
	6, 7, 4, //зад
	4, 5, 6,
	1, 6, 5, //верх
	2, 5, 1,
	0, 1, 2, //перед
	2, 3, 0
};

float angle = 0.0f * PI;
void gx_keyfunc(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_SPACE) {
		angle += 0.05f * PI;
		if (angle > PI)
			angle -= PI;
	}
}

int main() {
	//инициализация
	if (!glfwInit()) {
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	//окно
	const float width = 400, height = 300;
	GLFWwindow* window = glfwCreateWindow((int)width, (int)height, "gelexone render", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	printf("OpenGL version:\n%s\n", glGetString(GL_VERSION));

	//настройка функций glfw
	//glfwSetKeyCallback(window, gx_keyfunc);

	//blending для png файлов с прозрачностью
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//массив вершин
	VertexArray vao = vao_create();

	//буфер вершин
	VertexBuffer vbo = vbo_create(positions, VERTEXCOUNT * sizeof(float));

	//layout буфера вершин
	VertexBufferLayout* vbl = vbl_create();
	vbl_push(vbl, GL_FLOAT, 3, GL_FALSE);
	vbl_push(vbl, GL_FLOAT, 2, GL_FALSE);
	vao_add_buffer(vao, vbo, vbl);

	//буфер индексов
	IndexBuffer ibo = ibo_create(indices, INDICESCOUNT);

	//шейдер
	ShaderProgramSource src = ParseShader("res/shaders/projected.shader");
	printf("vertex shader:\n%s\n", src.VertexSource);
	printf("fragment shader:\n%s\n", src.FragmentSource);
	Shader shader = shader_create(src.VertexSource, src.FragmentSource);
	shader_bind(shader);


	//матрицы
	mat4 mvp, proj, view, model, camera_rotation, pyr_rotation0, pyr_rotation1;
	//mat4_create_ortho(proj, -2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	mat4_create_perspective(proj, -1, 1, -height / width, height / width, -1, 1);
	mat4_create_translation(view,  0, 0, 4);
	mat4_create_translation(model, 0, 0, 0);
	mat4_create_rotation_x(pyr_rotation0, PI);
	
	//текстура
	Texture texture0 = texture_create("res/textures/epic_yozhik.png");
	texture_bind_slot(texture0, 0);
	shader_set_uniform1i(shader, "u_Texture", 0);

	//сбрасываем все бинды буферов для отладки
	shader_unbind();
	vao_unbind();
	vbo_unbind();
	ibo_unbind();

	// Enable depth test
	GLCall(glEnable(GL_DEPTH_TEST));
	// Accept fragment if it closer to the camera than the former one
	GLCall(glDepthFunc(GL_LESS));

	//рендер
	GLCall(glClearColor(0.2f,0.7f,0.4f,0.0f));
	while (!glfwWindowShouldClose(window))
	{
		render_clear();

		camera_move(window, view);
		mat4_create_rotation_y(pyr_rotation1, angle);
			mat4_mul_mat4(mvp, proj, 0);
			//mat4_mul_mat4(mvp, mvp, camera_rotation);
			mat4_mul_mat4(mvp, mvp, view);
			mat4_mul_mat4(mvp, mvp, model);
			mat4_mul_mat4(mvp, mvp, pyr_rotation1);
			mat4_mul_mat4(mvp, mvp, pyr_rotation0);
		shader_set_uniformMat4f(shader, "u_MVP", mvp);
		render_draw(vao, ibo, shader);
		
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			angle += 0.05f * PI;
		}
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//завершение работы
	glfwTerminate();
	return 0;
}