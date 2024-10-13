#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include "state.h"

bool gameRunning = true;
const char* gameTitle = "Minecraft Clone [BETA]";
State state;

void Init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int main() {
	Init();
	Window currentWindow = Window(gameTitle);
	state.currentWindow = &currentWindow;

	currentWindow.windowLoop();

	return 0;
}