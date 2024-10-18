#ifndef EGG_VERTEX_BUFFER_H
#define EGG_VERTEX_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <algorithm>

namespace gl
{
    class VertexBuffer
    {
    private:
        unsigned int VBO;
        unsigned int size;

        void release();

    public:
        VertexBuffer();
        VertexBuffer(void *data, unsigned int size);
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer &) = delete;
        VertexBuffer &operator=(const VertexBuffer &) = delete;

        // Move constructor
        VertexBuffer(VertexBuffer &&other) noexcept : VBO(other.VBO), size(other.size)
        {
            other.VBO = 0;
            other.size = 0;
        }

        VertexBuffer &operator=(VertexBuffer &&other)
        {
            // ALWAYS check for self-assignment.
            if (this != &other)
            {
                release();
                std::swap(VBO, other.VBO);
                std::swap(size, other.size);
            }

            return *this;
        }

        void set(void *data, unsigned int size, GLenum usage = GL_DYNAMIC_DRAW);

        unsigned int getSize() { return size; };

        void bind() const;
        void unbind() const;
    };
}

#endif