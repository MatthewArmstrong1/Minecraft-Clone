#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "vertexBuffer.h"

VertexBuffer::VertexBuffer(int type) {
	this->type = type;
	glGenBuffers(1, &this->id);
};

void VertexBuffer::bind() {
	glBindBuffer(this->type, this->id);
}

void VertexBuffer::destroy() {
	glDeleteBuffers(1, &this->id);
}

void VertexBuffer::buffer(void* data, size_t offset, size_t count, float sizeOfData) {
	this->bind();
	glBufferData(this->type, sizeOfData, data, this->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}