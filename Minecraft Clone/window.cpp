#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.h"
#include "shader.h"
#include "vertexBuffer.h"
#include "vertexArray.h"

#include <stb_image.h>

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

void framebufferSizeCallback(GLFWwindow* windowRef, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


Window::Window(const char* title) {
	this->windowID = glfwCreateWindow(800, 600, title, NULL, NULL);

	if (this->windowID == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(this->windowID);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(this-> windowID, framebufferSizeCallback);

	this->windowShader = new Shader("vertex.shader", "fragment.shader");
};

void Window::render(VertexArray* vertexArrays, int arraySize) {
	this->windowShader->use();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < arraySize; i++) {
		vertexArrays[i].bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

void Window::windowLoop() {

	VertexArray VAO;
	VertexBuffer VBO(GL_ARRAY_BUFFER);

	VBO.buffer(vertices, 0, 3, sizeof(vertices));
	VAO.attribute(VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);

	VertexArray vertexArrays[] = { VAO };
	int arraySize = sizeof(vertexArrays) / sizeof(vertexArrays[0]);

	while (!glfwWindowShouldClose(this->windowID)) {
		processInput(this->windowID);

		this->render(vertexArrays, arraySize);
		
		glfwSwapBuffers(this->windowID);
		glfwPollEvents();
	}

	this->destroy();
}

void Window::destroy() {
	glfwTerminate();
	delete this->windowShader;
}