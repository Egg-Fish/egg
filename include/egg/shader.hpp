#ifndef EGG_SHADER_H
#define EGG_SHADER_H

#include <glad/glad.h>

class Shader
{
private:
    unsigned int program;

    unsigned int getUniformLocation(const char *variable) const;

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);

    ~Shader();

    void use() const;

    void setUniform1f(const char *variable, float v0);    
    void setUniform2f(const char *variable, float v0, float v1);    
    void setUniform3f(const char *variable, float v0, float v1, float v2);    
    void setUniform4f(const char *variable, float v0, float v1, float v2, float v3);

    // 1i, 2i, 3i, 4i
    void setUniform1i(const char *variable, int v0);    
    void setUniform2i(const char *variable, int v0, int v1);    
    void setUniform3i(const char *variable, int v0, int v1, int v2);    
    void setUniform4i(const char *variable, int v0, int v1, int v2, int v3);

    // 1ui, 2ui, 3ui, 4ui
    void setUniform1ui(const char *variable, unsigned int v0);
    void setUniform2ui(const char *variable, unsigned int v0, unsigned int v1);
    void setUniform3ui(const char *variable, unsigned int v0, unsigned int v1, unsigned int v2);
    void setUniform4ui(const char *variable, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);

    // Float arrays (1fv, 2fv, 3fv, 4fv)
    void setUniform1fv(const char *variable, int count, const float *value);
    void setUniform2fv(const char *variable, int count, const float *value);
    void setUniform3fv(const char *variable, int count, const float *value);
    void setUniform4fv(const char *variable, int count, const float *value);

    // Integer arrays (1iv, 2iv, 3iv, 4iv)
    void setUniform1iv(const char *variable, int count, const int *value);
    void setUniform2iv(const char *variable, int count, const int *value);
    void setUniform3iv(const char *variable, int count, const int *value);
    void setUniform4iv(const char *variable, int count, const int *value);

    // Unsigned integer arrays (1uiv, 2uiv, 3uiv, 4uiv)
    void setUniform1uiv(const char *variable, int count, const unsigned int *value);
    void setUniform2uiv(const char *variable, int count, const unsigned int *value);
    void setUniform3uiv(const char *variable, int count, const unsigned int *value);
    void setUniform4uiv(const char *variable, int count, const unsigned int *value);

    // Matrix Uniforms (2x2, 3x3, 4x4, and mixed types)
    void setUniformMatrix2fv(const char *variable, int count, bool transpose, const float *value);
    void setUniformMatrix3fv(const char *variable, int count, bool transpose, const float *value);
    void setUniformMatrix4fv(const char *variable, int count, bool transpose, const float *value);
    void setUniformMatrix2x3fv(const char *variable, int count, bool transpose, const float *value);
    void setUniformMatrix3x2fv(const char *variable, int count, bool transpose, const float *value);
    void setUniformMatrix2x4fv(const char *variable, int count, bool transpose, const float *value);
    void setUniformMatrix4x2fv(const char *variable, int count, bool transpose, const float *value);
    void setUniformMatrix3x4fv(const char *variable, int count, bool transpose, const float *value);
    void setUniformMatrix4x3fv(const char *variable, int count, bool transpose, const float *value);
};

#endif