#ifndef EGG_VERTEX_BUFFER_LAYOUT_H
#define EGG_VERTEX_BUFFER_LAYOUT_H

#include <vector>
#include <string>

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace gl
{
    struct VertexBufferLayoutElement
    {
        unsigned int index;
        unsigned int count;
        GLenum type;
        bool normalized;
        unsigned int stride = 0;
        void *offset = (void *)0;
    };

    class VertexBufferLayout
    {
    private:
        std::vector<VertexBufferLayoutElement> elements;

        unsigned int currentStride = 0;

    public:
        VertexBufferLayout();

        void push(unsigned int index, unsigned int count, GLenum type);

        std::vector<VertexBufferLayoutElement> getElements();

        unsigned int getStride() { return currentStride; };
    };
}

#endif