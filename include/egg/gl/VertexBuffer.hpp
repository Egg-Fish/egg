#ifndef EGG_VERTEX_BUFFER_H
#define EGG_VERTEX_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace gl
{
    class VertexBuffer
    {
    private:
        unsigned int VBO;
        unsigned int size;

    public:
        VertexBuffer();
        VertexBuffer(void *data, unsigned int size);
        ~VertexBuffer();

        void set(void *data, unsigned int size, GLenum usage = GL_DYNAMIC_DRAW);

        unsigned int getSize() { return size; };

        void bind() const;
        void unbind() const;
    };
}

#endif