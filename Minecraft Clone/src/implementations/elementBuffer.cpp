#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "elementBuffer.h"

ElementBuffer::ElementBuffer() {
	glGenBuffers(1, &this->id);
}

void ElementBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
}

void ElementBuffer::destroy() {
	glDeleteBuffers(1, &this->id);
}

void ElementBuffer::buffer(unsigned int* data, int dataSize) {
	this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}