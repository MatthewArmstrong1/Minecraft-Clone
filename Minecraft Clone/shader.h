#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <iostream>

class Shader {
    public:
        unsigned int shaderID;
        Shader(const char* vertexShaderSourcePath, const char* fragmentShaderSourcePath);

        void use();

        void setBool(const std::string& name, bool value);
        void setFloat(const std::string& name, float value);
        void setInt(const std::string& name, int value);
    private:
        void CheckForCompilationErrors(unsigned int shader, std::string type);
};

#endif