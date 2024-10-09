#include "egg/shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

unsigned int createShader(GLenum shaderType, const char *shaderPath)
{
    // Fetch shader code from file
    std::ifstream shaderFile;
    std::string shaderFileText;
    shaderFile.exceptions(std::ifstream::badbit);

    try
    {
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderFileText = shaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "Failed to read file: " << shaderPath << std::endl;
    }

    const char *shaderCode = shaderFileText.c_str();

    // Compile shader code
    int success;
    char infoLog[512];

    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, 0);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Failed to compile [\n"
                  << shaderCode << "\n]\n"
                  << infoLog << std::endl;
    }

    return shader;
}

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    int success;
    char infoLog[512];

    unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexPath);
    unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentPath);

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Failed to link shaders \n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath)
{
    int success;
    char infoLog[512];

    unsigned int vertexShader = createShader(GL_VERTEX_SHADER, vertexPath);
    unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentPath);
    unsigned int geometryShader = createShader(GL_GEOMETRY_SHADER, geometryPath);

    program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glAttachShader(program, geometryShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Failed to link shaders \n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(geometryShader);
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::use() const
{
    glUseProgram(program);
}