#include "gl/VertexArray.hpp"
#include "gl/gl_utils.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "gl/VertexBuffer.hpp"
#include "gl/VertexBufferLayout.hpp"

#include <iostream>

gl::VertexArray::VertexArray()
{
    GL_CALL(glGenVertexArrays(1, &VAO));
    bind();
}

void gl::VertexArray::release()
{
    GL_CALL(glDeleteVertexArrays(1, &VAO));
}

gl::VertexArray::~VertexArray()
{
    release();
}

void gl::VertexArray::addBuffer(VertexBuffer &vb, VertexBufferLayout &vbl)
{
    bind();
    vb.bind();

    std::vector<VertexBufferLayoutElement> elements = vbl.getElements();

    for (VertexBufferLayoutElement el : elements)
    {
        GL_CALL(glEnableVertexAttribArray(el.index));
        GL_CALL(glVertexAttribPointer(
            el.index,
            el.count,
            el.type,
            el.normalized,
            el.stride,
            el.offset));
    }

    this->count = vb.getSize() / vbl.getStride();
    unbind();
}

void gl::VertexArray::bind() const { GL_CALL(glBindVertexArray(VAO)); }
void gl::VertexArray::unbind() const { GL_CALL(glBindVertexArray(0)); }