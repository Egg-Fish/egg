#include "egg/ElementBuffer.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

ElementBuffer::ElementBuffer()
{
    glGenBuffers(1, &VBO);
    bind();
}

ElementBuffer::ElementBuffer(unsigned int *data, unsigned int size)
{
    glGenBuffers(1, &VBO);
    set(data, size);
}

ElementBuffer::~ElementBuffer()
{
    glDeleteBuffers(1, &VBO);
}

void ElementBuffer::set(unsigned int *data, unsigned int size, GLenum usage)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void ElementBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO);
}
void ElementBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}