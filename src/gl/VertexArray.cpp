#include "gl/VertexArray.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "gl/VertexBuffer.hpp"
#include "gl/VertexBufferLayout.hpp"

#include <iostream>

gl::VertexArray::VertexArray()
{
    glGenVertexArrays(1, &VAO);
    bind();
}
gl::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &VAO);
}

void gl::VertexArray::addBuffer(VertexBuffer &vb, VertexBufferLayout &vbl)
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

    this->count = vb.getSize() / vbl.getStride();
    unbind();
}

void gl::VertexArray::bind() const { glBindVertexArray(VAO); }
void gl::VertexArray::unbind() const { glBindVertexArray(0); }