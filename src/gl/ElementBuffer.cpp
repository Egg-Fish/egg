#include "gl/ElementBuffer.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

gl::ElementBuffer::ElementBuffer()
{
    glGenBuffers(1, &VBO);
    bind();
}

gl::ElementBuffer::ElementBuffer(unsigned int *data, unsigned int size)
{
    glGenBuffers(1, &VBO);
    set(data, size);
}

gl::ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &VBO);
}

void gl::ElementBuffer::set(unsigned int *data, unsigned int size, GLenum usage)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
    count = size / sizeof(unsigned int);
}

void gl::ElementBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
}
void gl::ElementBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}