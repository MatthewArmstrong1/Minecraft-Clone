#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

#include "texture.h"

Texture::Texture(int type) {
	glGenTextures(1, &this->id);
	this->type = type;
}

void Texture::bind() {
	glBindTexture(this->type, this->id);
}

void Texture::loadFromPath(const char* filePath) {
	const int currentType = this->type;
	glTexParameteri(currentType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(currentType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(currentType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(currentType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(currentType, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(currentType);
	}
	else {
		std::cout << "There was an issue initalising texture at path " << filePath << std::endl;
	}
	stbi_image_free(data);
}