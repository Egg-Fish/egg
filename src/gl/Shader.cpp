#include "gl/Shader.hpp"
#include "gl/gl_utils.hpp"

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

    unsigned int shader;
    GL_CALL(shader = glCreateShader(shaderType));
    GL_CALL(glShaderSource(shader, 1, &shaderCode, 0));
    GL_CALL(glCompileShader(shader));
    GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success)
    {
        GL_CALL(glGetShaderInfoLog(shader, 512, NULL, infoLog));
        std::cout << "Failed to compile [\n"
                  << shaderCode << "\n]\n"
                  << infoLog << std::endl;
    }

    return shader;
}

gl::Shader::Shader()
{
    program = 0;
}

gl::Shader::Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath)
{
    int success;
    char infoLog[512];

    GL_CALL(program = glCreateProgram());

    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int geometryShader;

    vertexShader = createShader(GL_VERTEX_SHADER, vertexPath);
    fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentPath);

    GL_CALL(glAttachShader(program, vertexShader));
    GL_CALL(glAttachShader(program, fragmentShader));

    if (!std::string(geometryPath).empty())
    {
        geometryShader = createShader(GL_GEOMETRY_SHADER, geometryPath);
        GL_CALL(glAttachShader(program, geometryShader));
    }

    GL_CALL(glLinkProgram(program));
    GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &success));
    if (!success)
    {
        GL_CALL(glGetProgramInfoLog(program, 512, NULL, infoLog));
        std::cout << "Failed to link shaders \n"
                  << infoLog << std::endl;
        program = 0;
    }

    GL_CALL(glDeleteShader(vertexShader));
    GL_CALL(glDeleteShader(fragmentShader));

    if (!std::string(geometryPath).empty())
    {
        GL_CALL(glDeleteShader(geometryShader));
    }
}

void gl::Shader::release()
{
    if (program != 0)
        GL_CALL(glDeleteProgram(program));
}

gl::Shader::~Shader()
{
    release();
}

void gl::Shader::use() const
{
    if (program != 0)
        GL_CALL(glUseProgram(program));
}

int gl::Shader::getUniformLocation(const char *variable) const
{
    int uniformLocation;
    GL_CALL(uniformLocation = glGetUniformLocation(program, variable));
    if (uniformLocation == -1)
    {
        std::cerr << "Error: Could not find uniform location associated with name " << variable << std::endl;
        return -1;
    }

    return uniformLocation;
}

void gl::Shader::setUniform1f(const char *variable, float v0)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform1f(location, v0););
}

void gl::Shader::setUniform2f(const char *variable, float v0, float v1)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform2f(location, v0, v1););
}

void gl::Shader::setUniform3f(const char *variable, float v0, float v1, float v2)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform3f(location, v0, v1, v2););
}

void gl::Shader::setUniform4f(const char *variable, float v0, float v1, float v2, float v3)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform4f(location, v0, v1, v2, v3););
}

// 1i, 2i, 3i, 4i
void gl::Shader::setUniform1i(const char *variable, int v0)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform1i(location, v0););
}

void gl::Shader::setUniform2i(const char *variable, int v0, int v1)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform2i(location, v0, v1););
}

void gl::Shader::setUniform3i(const char *variable, int v0, int v1, int v2)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform3i(location, v0, v1, v2););
}

void gl::Shader::setUniform4i(const char *variable, int v0, int v1, int v2, int v3)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform4i(location, v0, v1, v2, v3););
}

// 1ui, 2ui, 3ui, 4ui
void gl::Shader::setUniform1ui(const char *variable, unsigned int v0)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform1ui(location, v0););
}

void gl::Shader::setUniform2ui(const char *variable, unsigned int v0, unsigned int v1)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform2ui(location, v0, v1););
}

void gl::Shader::setUniform3ui(const char *variable, unsigned int v0, unsigned int v1, unsigned int v2)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform3ui(location, v0, v1, v2););
}

void gl::Shader::setUniform4ui(const char *variable, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform4ui(location, v0, v1, v2, v3););
}

// Float arrays (1fv, 2fv, 3fv, 4fv)
void gl::Shader::setUniform1fv(const char *variable, int count, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform1fv(location, count, value););
}

void gl::Shader::setUniform2fv(const char *variable, int count, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform2fv(location, count, value););
}

void gl::Shader::setUniform3fv(const char *variable, int count, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform3fv(location, count, value););
}

void gl::Shader::setUniform4fv(const char *variable, int count, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform4fv(location, count, value););
}

// Integer arrays (1iv, 2iv, 3iv, 4iv)
void gl::Shader::setUniform1iv(const char *variable, int count, const int *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform1iv(location, count, value););
}

void gl::Shader::setUniform2iv(const char *variable, int count, const int *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform2iv(location, count, value););
}

void gl::Shader::setUniform3iv(const char *variable, int count, const int *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform3iv(location, count, value););
}

void gl::Shader::setUniform4iv(const char *variable, int count, const int *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform4iv(location, count, value););
}

// Unsigned integer arrays (1uiv, 2uiv, 3uiv, 4uiv)
void gl::Shader::setUniform1uiv(const char *variable, int count, const unsigned int *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform1uiv(location, count, value););
}

void gl::Shader::setUniform2uiv(const char *variable, int count, const unsigned int *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform2uiv(location, count, value););
}

void gl::Shader::setUniform3uiv(const char *variable, int count, const unsigned int *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform3uiv(location, count, value););
}

void gl::Shader::setUniform4uiv(const char *variable, int count, const unsigned int *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniform4uiv(location, count, value););
}

// Matrix Uniforms (2x2, 3x3, 4x4, and mixed types)
void gl::Shader::setUniformMatrix2fv(const char *variable, int count, bool transpose, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniformMatrix2fv(location, count, transpose, value););
}

void gl::Shader::setUniformMatrix3fv(const char *variable, int count, bool transpose, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniformMatrix3fv(location, count, transpose, value););
}

void gl::Shader::setUniformMatrix4fv(const char *variable, int count, bool transpose, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniformMatrix4fv(location, count, transpose, value););
}

void gl::Shader::setUniformMatrix2x3fv(const char *variable, int count, bool transpose, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniformMatrix2x3fv(location, count, transpose, value););
}

void gl::Shader::setUniformMatrix3x2fv(const char *variable, int count, bool transpose, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniformMatrix3x2fv(location, count, transpose, value););
}

void gl::Shader::setUniformMatrix2x4fv(const char *variable, int count, bool transpose, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniformMatrix2x4fv(location, count, transpose, value););
}

void gl::Shader::setUniformMatrix4x2fv(const char *variable, int count, bool transpose, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniformMatrix4x2fv(location, count, transpose, value););
}

void gl::Shader::setUniformMatrix3x4fv(const char *variable, int count, bool transpose, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniformMatrix3x4fv(location, count, transpose, value););
}

void gl::Shader::setUniformMatrix4x3fv(const char *variable, int count, bool transpose, const float *value)
{
    GLint location = getUniformLocation(variable);
    if (location == -1) return;
    GL_CALL(glUniformMatrix4x3fv(location, count, transpose, value););
}
