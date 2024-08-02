#pragma once

#include "gl_debug.h"

typedef struct {
	unsigned int id;
	char* filepath;
	unsigned char* localbuffer;
	int width, height, BPP;
} Texture;

Texture texture_create(const char* filepath);
void texture_delete(Texture texture);
void texture_bind();
void texture_bind_slot(unsigned int slot);