#include "gl/VertexBuffer.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

gl::VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &VBO);
    bind();
}

gl::VertexBuffer::VertexBuffer(void *data, unsigned int size)
{
    glGenBuffers(1, &VBO);
    set(data, size);
}

gl::VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &VBO);
}

void gl::VertexBuffer::set(void *data, unsigned int size, GLenum usage)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    this->size = size;
}

void gl::VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}
void gl::VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}