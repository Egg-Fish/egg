#ifndef EGG_VERTEX_ARRAY_H
#define EGG_VERTEX_ARRAY_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "gl/VertexBuffer.hpp"
#include "gl/VertexBufferLayout.hpp"

namespace gl
{
    class VertexArray
    {
    private:
        unsigned int VAO;
        unsigned int count;

    public:
        VertexArray();
        ~VertexArray();

        void addBuffer(VertexBuffer &vb, VertexBufferLayout &vbl);

        void bind() const;
        void unbind() const;

        unsigned int getCount() { return count; };
    };
}

#endif