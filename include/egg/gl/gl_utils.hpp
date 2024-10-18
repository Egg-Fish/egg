#ifndef EGG_GL_UTILS_H
#define EGG_GL_UTILS_H

#include <glad/glad.h>
#include <iostream>

// Function to check OpenGL errors
inline void check_gl_error(const char *file, int line)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "[OpenGL Error] (" << error << "): " << file << ":" << line << std::endl;
    }
}

// If DEBUG is defined, enable GL_CALL, otherwise make it a no-op
#ifdef DEBUG
    #define GL_CALL(x) do { \
        x; \
        check_gl_error(__FILE__, __LINE__); \
    } while (0)
#else
    // In release builds, GL_CALL does nothing
    #define GL_CALL(x) x
#endif

#endif // EGG_GL_UTILS_H
