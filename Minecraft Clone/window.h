#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "vertexArray.h"

class Window {
	public:
		GLFWwindow* windowID;
		Shader* windowShader;

		Window(const char* title);

		void windowLoop();
	private:
		void destroy();
		void render(VertexArray vertexArrays[], int arraySize);
};

#endif