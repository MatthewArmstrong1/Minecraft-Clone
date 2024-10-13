#pragma once

#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ElementBuffer {
	public:
		unsigned int id;

		ElementBuffer();

		void bind();
		void buffer(unsigned int* data, int dataSize);
		void destroy();
};

#endif