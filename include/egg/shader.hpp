#ifndef EGG_SHADER_H
#define EGG_SHADER_H

#include <glad/glad.h>

class Shader
{
private:
    unsigned int program;

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);

    ~Shader();

    void use() const;
};

#endif