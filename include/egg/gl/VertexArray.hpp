#ifndef EGG_VERTEX_ARRAY_H
#define EGG_VERTEX_ARRAY_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "gl/VertexBuffer.hpp"
#include "gl/VertexBufferLayout.hpp"

#include <algorithm>

namespace gl
{
    class VertexArray
    {
    private:
        unsigned int VAO;
        unsigned int count;

        void release();

    public:
        VertexArray();
        ~VertexArray();

        VertexArray(const VertexArray &) = delete;
        VertexArray &operator=(const VertexArray &) = delete;

        // Move constructor
        VertexArray(VertexArray &&other) noexcept : VAO(other.VAO), count(other.count)
        {
            other.VAO = 0;
            other.count = 0;
        }

        VertexArray &operator=(VertexArray &&other)
        {
            // ALWAYS check for self-assignment.
            if (this != &other)
            {
                release();
                std::swap(VAO, other.VAO);
                std::swap(count, other.count);
            }

            return *this;
        }

        void addBuffer(VertexBuffer &vb, VertexBufferLayout &vbl);

        void bind() const;
        void unbind() const;

        unsigned int getCount() { return count; };
    };
}

#endif