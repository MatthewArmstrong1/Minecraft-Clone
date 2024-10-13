#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.h"
#include "shader.h"

#include "vertexBuffer.h"
#include "vertexArray.h"
#include "elementBuffer.h"
#include "texture.h"

float vertices[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f    // top left 
};

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};

void framebufferSizeCallback(GLFWwindow* windowRef, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		std::cout << "User wants to move forward but Mr Krabs said no" << std::endl;
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

	this->windowShader = new Shader("src/shaders/vertex.shader", "src/shaders/fragment.shader");
};

void Window::render(VertexArray* vertexArrays, int arraySize, Texture* textureArrays, int textureArraySize) {
	this->windowShader->use();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < textureArraySize; i++) {
		textureArrays[i].bind();
	}

	for (int i = 0; i < arraySize; i++) {
		vertexArrays[i].bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void Window::windowLoop() {

	VertexArray VAO;
	VertexBuffer VBO(GL_ARRAY_BUFFER);
	ElementBuffer EBO;
	Texture testTexture(GL_TEXTURE_2D);

	testTexture.loadFromPath("./resources/textures/grass.jpg");

	VBO.buffer(vertices, 0, 3, sizeof(vertices));
	VAO.attribute(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), 0); // actual verticies positions
	VAO.attribute(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), 3 * sizeof(float)); // colour values (unused when texture alone is rendered)
	VAO.attribute(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), 6 * sizeof(float)); // texture coordinates of image
	EBO.buffer(indices, sizeof(indices));

	VertexArray vertexArrays[] = { VAO };
	int arraySize = sizeof(vertexArrays) / sizeof(vertexArrays[0]);

	Texture textureArrays[] = { testTexture };
	int textureArraySize = sizeof(textureArrays) / sizeof(textureArrays[0]);

	while (!glfwWindowShouldClose(this->windowID)) {
		processInput(this->windowID);

		this->render(vertexArrays, arraySize, textureArrays, textureArraySize);
		
		glfwSwapBuffers(this->windowID);
		glfwPollEvents();
	}

	this->destroy();
}

void Window::destroy() {
	glfwTerminate();
	delete this->windowShader;
}