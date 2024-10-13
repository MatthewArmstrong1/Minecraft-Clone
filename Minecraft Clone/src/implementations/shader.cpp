#include "shader.h"

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath) {
	std::string vertexSourceCode, fragmentSourceCode;
	std::ifstream vertexFile, fragmentFile;

	vertexFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	fragmentFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try {
		vertexFile.open(vertexShaderSourcePath);
		fragmentFile.open(fragmentShaderSourcePath);
		std::stringstream vertexStream, fragmentStream;

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexSourceCode = vertexStream.str();
		fragmentSourceCode = fragmentStream.str();
	}
	catch (std::ifstream::failure& errorObject) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << errorObject.what() << std::endl;
	}

	const char* vertexUseableCode = vertexSourceCode.c_str();
	const char* fragmentUseableCode = fragmentSourceCode.c_str();

	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexUseableCode, NULL);
	glCompileShader(vertexShader);
	this->CheckForCompilationErrors(vertexShader, "VERTEX SHADER");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentUseableCode, NULL);
	glCompileShader(fragmentShader);
	this->CheckForCompilationErrors(fragmentShader, "FRAGMENT SHADER");

	this->shaderID = glCreateProgram();
	glAttachShader(this->shaderID, vertexShader);
	glAttachShader(this->shaderID, fragmentShader);
	glLinkProgram(this->shaderID);
	this->CheckForCompilationErrors(this->shaderID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() {
	glUseProgram(this->shaderID);
}

void Shader::setBool(const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(this->shaderID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(this->shaderID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(this->shaderID, name.c_str()), value);
}

void Shader::CheckForCompilationErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}