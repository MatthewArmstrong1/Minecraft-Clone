#pragma once

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "vertexBuffer.h"

class VertexArray {
	public:
		unsigned int id;

		VertexArray();

		void bind();
		void destroy();
		void attribute(VertexBuffer vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);
};

#endif