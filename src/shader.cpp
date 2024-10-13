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
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Failed to link shaders \n"
                  << infoLog << std::endl;
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
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Failed to link shaders \n"
                  << infoLog << std::endl;
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

unsigned int Shader::getUniformLocation(const char *variable) const
{
    return glGetUniformLocation(program, variable);
}

void Shader::setUniform1f(const char *variable, float v0)
{
    glUniform1f(getUniformLocation(variable), v0);
}

void Shader::setUniform2f(const char *variable, float v0, float v1)
{
    glUniform2f(getUniformLocation(variable), v0, v1);
}

void Shader::setUniform3f(const char *variable, float v0, float v1, float v2)
{
    glUniform3f(getUniformLocation(variable), v0, v1, v2);
}

void Shader::setUniform4f(const char *variable, float v0, float v1, float v2, float v3)
{
    glUniform4f(getUniformLocation(variable), v0, v1, v2, v3);
}

// 1i, 2i, 3i, 4i
void Shader::setUniform1i(const char *variable, int v0)
{
    glUniform1i(getUniformLocation(variable), v0);
}

void Shader::setUniform2i(const char *variable, int v0, int v1)
{
    glUniform2i(getUniformLocation(variable), v0, v1);
}

void Shader::setUniform3i(const char *variable, int v0, int v1, int v2)
{
    glUniform3i(getUniformLocation(variable), v0, v1, v2);
}

void Shader::setUniform4i(const char *variable, int v0, int v1, int v2, int v3)
{
    glUniform4i(getUniformLocation(variable), v0, v1, v2, v3);
}

// 1ui, 2ui, 3ui, 4ui
void Shader::setUniform1ui(const char *variable, unsigned int v0)
{
    glUniform1ui(getUniformLocation(variable), v0);
}

void Shader::setUniform2ui(const char *variable, unsigned int v0, unsigned int v1)
{
    glUniform2ui(getUniformLocation(variable), v0, v1);
}

void Shader::setUniform3ui(const char *variable, unsigned int v0, unsigned int v1, unsigned int v2)
{
    glUniform3ui(getUniformLocation(variable), v0, v1, v2);
}

void Shader::setUniform4ui(const char *variable, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3)
{
    glUniform4ui(getUniformLocation(variable), v0, v1, v2, v3);
}

// Float arrays (1fv, 2fv, 3fv, 4fv)
void Shader::setUniform1fv(const char *variable, int count, const float *value)
{
    glUniform1fv(getUniformLocation(variable), count, value);
}

void Shader::setUniform2fv(const char *variable, int count, const float *value)
{
    glUniform2fv(getUniformLocation(variable), count, value);
}

void Shader::setUniform3fv(const char *variable, int count, const float *value)
{
    glUniform3fv(getUniformLocation(variable), count, value);
}

void Shader::setUniform4fv(const char *variable, int count, const float *value)
{
    glUniform4fv(getUniformLocation(variable), count, value);
}

// Integer arrays (1iv, 2iv, 3iv, 4iv)
void Shader::setUniform1iv(const char *variable, int count, const int *value)
{
    glUniform1iv(getUniformLocation(variable), count, value);
}

void Shader::setUniform2iv(const char *variable, int count, const int *value)
{
    glUniform2iv(getUniformLocation(variable), count, value);
}

void Shader::setUniform3iv(const char *variable, int count, const int *value)
{
    glUniform3iv(getUniformLocation(variable), count, value);
}

void Shader::setUniform4iv(const char *variable, int count, const int *value)
{
    glUniform4iv(getUniformLocation(variable), count, value);
}

// Unsigned integer arrays (1uiv, 2uiv, 3uiv, 4uiv)
void Shader::setUniform1uiv(const char *variable, int count, const unsigned int *value)
{
    glUniform1uiv(getUniformLocation(variable), count, value);
}

void Shader::setUniform2uiv(const char *variable, int count, const unsigned int *value)
{
    glUniform2uiv(getUniformLocation(variable), count, value);
}

void Shader::setUniform3uiv(const char *variable, int count, const unsigned int *value)
{
    glUniform3uiv(getUniformLocation(variable), count, value);
}

void Shader::setUniform4uiv(const char *variable, int count, const unsigned int *value)
{
    glUniform4uiv(getUniformLocation(variable), count, value);
}

// Matrix Uniforms (2x2, 3x3, 4x4, and mixed types)
void Shader::setUniformMatrix2fv(const char *variable, int count, bool transpose, const float *value)
{
    glUniformMatrix2fv(getUniformLocation(variable), count, transpose, value);
}

void Shader::setUniformMatrix3fv(const char *variable, int count, bool transpose, const float *value)
{
    glUniformMatrix3fv(getUniformLocation(variable), count, transpose, value);
}

void Shader::setUniformMatrix4fv(const char *variable, int count, bool transpose, const float *value)
{
    glUniformMatrix4fv(getUniformLocation(variable), count, transpose, value);
}

void Shader::setUniformMatrix2x3fv(const char *variable, int count, bool transpose, const float *value)
{
    glUniformMatrix2x3fv(getUniformLocation(variable), count, transpose, value);
}

void Shader::setUniformMatrix3x2fv(const char *variable, int count, bool transpose, const float *value)
{
    glUniformMatrix3x2fv(getUniformLocation(variable), count, transpose, value);
}

void Shader::setUniformMatrix2x4fv(const char *variable, int count, bool transpose, const float *value)
{
    glUniformMatrix2x4fv(getUniformLocation(variable), count, transpose, value);
}

void Shader::setUniformMatrix4x2fv(const char *variable, int count, bool transpose, const float *value)
{
    glUniformMatrix4x2fv(getUniformLocation(variable), count, transpose, value);
}

void Shader::setUniformMatrix3x4fv(const char *variable, int count, bool transpose, const float *value)
{
    glUniformMatrix3x4fv(getUniformLocation(variable), count, transpose, value);
}

void Shader::setUniformMatrix4x3fv(const char *variable, int count, bool transpose, const float *value)
{
    glUniformMatrix4x3fv(getUniformLocation(variable), count, transpose, value);
}