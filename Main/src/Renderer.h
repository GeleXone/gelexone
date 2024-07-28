#pragma once

#include "gl_debug.h"
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

void render_clear();
void render_draw(VertexArray vao, IndexBuffer ibo, Shader shader);