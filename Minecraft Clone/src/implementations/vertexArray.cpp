#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "vertexArray.h"
#include "vertexBuffer.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &this->id);
}

void VertexArray::bind() {
	glBindVertexArray(this->id);
}

void VertexArray::destroy() {
	glDeleteVertexArrays(1, &this->id);
}

void VertexArray::attribute(VertexBuffer vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset) {
	this->bind();
	vbo.bind();

	switch (type) {
        case GL_UNSIGNED_INT_2_10_10_10_REV:
            glVertexAttribIPointer(index, size, type, stride, (void*)offset);
            break;
        default:
            glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
            break;
	}
    glEnableVertexAttribArray(index);
}