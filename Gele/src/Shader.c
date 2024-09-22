#include <malloc.h>
#include <Xone/x_string.h>
#include <Xone/x_math.h>

#include "gl_debug.h"
#include "Shader.h"

//эта штука достаёт два шейдера из одного текстового файла
enum ShaderType {
	NONE = 0, VERTEX = 1, FRAGMENT = 2
};
ShaderProgramSource ParseShader(const char* filepath) {
	const char* vert = "#shader vertex\n";
	const char* frag = "#shader fragment\n";
	char vs[4000] = "";
	char fs[4000] = "";
	FILE* file = fopen(filepath, "r");
	char buffer[128];
	unsigned char mode = NONE;
	if (file) {
		while (fgets(buffer, 128, file))
		{
			if (x_is_substring(vert, buffer)) {
				mode = VERTEX;
			}
			else if (x_is_substring(frag, buffer)) {
				mode = FRAGMENT;
			}
			else {
				switch (mode) {
				case VERTEX:
					x_strcat(vs, buffer);
					break;
				case FRAGMENT:
					x_strcat(fs, buffer);
					break;
				default:
					break;
				}
			}
		}
		fclose(file);
	}
	else {
		printf("%s path not found\n", filepath);
	}

	ShaderProgramSource result = { vs, fs };
	return result;
}

//тут уже начинается OpenGL
#include <glad/glad.h>

unsigned int shader_compile(unsigned int type, const char** source)
{
	GLCall(unsigned int id = glCreateShader(type));
	GLCall(glShaderSource(id, 1, source, NULL));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)malloc(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		printf("Compile %s shader status: %s\n", (type == GL_VERTEX_SHADER) ? "vertex" : "fragment", message);
		free(message);
	}

	return id;
}

Shader shader_create(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	unsigned int vs = shader_compile(GL_VERTEX_SHADER, &vertexShaderSource);
	unsigned int fs = shader_compile(GL_FRAGMENT_SHADER, &fragmentShaderSource);

	Shader shader;
	GLCall(shader.id = glCreateProgram());
	unsigned int program = shader.id;
	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDetachShader(program, vs));
	GLCall(glDetachShader(program, fs));

	return shader;
}

void shader_bind(Shader shader) {
	GLCall(glUseProgram(shader.id));
}

void shader_unbind() {
	GLCall(glUseProgram(0));
}

int shader_get_uniform_location(Shader shader, const char* name) {
	GLCall(int location = glGetUniformLocation(shader.id, name));
	return location;
}

void shader_set_uniform1i(Shader shader, const char* name, int i) {
	shader_bind(shader);
	GLCall(glUniform1i(shader_get_uniform_location(shader, name), i));
}

void shader_set_uniform4f(Shader shader, const char* name, float f1, float f2, float f3, float f4) {
	shader_bind(shader);
	GLCall(glUniform4f(shader_get_uniform_location(shader, name), f1, f2, f3, f4));
}

void shader_set_uniformMat4f(Shader shader, const char* name, mat4 matrix) {
	shader_bind(shader);
	GLCall(glUniformMatrix4fv(shader_get_uniform_location(shader, name), 1, GL_FALSE, &matrix[0][0]));
}
