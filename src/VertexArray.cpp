#include "egg/VertexArray.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "egg/VertexBuffer.hpp"
#include "egg/VertexBufferLayout.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &VAO);
    bind();
}
VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &VAO);
}

void VertexArray::addBuffer(VertexBuffer &vb, VertexBufferLayout &vbl)
{
    bind();
    vb.bind();

    std::vector<VertexBufferLayoutElement> elements = vbl.getElements();

    for (VertexBufferLayoutElement el : elements)
    {
        glEnableVertexAttribArray(el.index);
        glVertexAttribPointer(
            el.index,
            el.count,
            el.type,
            el.normalized,
            el.stride,
            el.offset);
    }
}

void VertexArray::bind() const { glBindVertexArray(VAO); }
void VertexArray::unbind() const { glBindVertexArray(0); }