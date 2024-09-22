#include "Texture.h"
#include "vendor/stb_image/stb_image.h"

Texture texture_create(const char* filepath) {
	Texture texture;
	stbi_set_flip_vertically_on_load(1);
	texture.filepath = filepath;
	texture.localbuffer = stbi_load(texture.filepath, &texture.width, &texture.height, &texture.BPP, 4);
	
	GLCall(glGenTextures(1, &texture.id));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.id));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.localbuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	
	if (texture.localbuffer)
		stbi_image_free(texture.localbuffer);

	return texture;
}

void texture_delete(Texture texture) {
	GLCall(glDeleteTextures(1, &texture.id));
}

void texture_unbind() {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void texture_bind(Texture texture) {
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.id));
}

void texture_bind_slot(Texture texture, unsigned int slot) {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture.id));
}
