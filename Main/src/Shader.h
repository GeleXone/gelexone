#pragma once

typedef struct {
	char* VertexSource;
	char* FragmentSource;
} ShaderProgramSource;

typedef struct {
	unsigned int id;
} Shader;

ShaderProgramSource ParseShader(const char* filepath);
unsigned int shader_compile(unsigned int type, const char** source);
Shader shader_create(const char* vertexShaderSource, const char* fragmentShaderSource);


void shader_bind(Shader);
void shader_unbind();

int shader_get_uniform_location(Shader shader, const char* name);
void shader_set_uniform4f(Shader shader, const char* name, float, float, float, float);