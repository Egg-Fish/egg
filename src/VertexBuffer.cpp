#include "egg/VertexBuffer.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &VBO);
}

VertexBuffer::VertexBuffer(void *data, unsigned int size)
{
    glGenBuffers(1, &VBO);
    set(data, size);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &VBO);
}

void VertexBuffer::set(void *data, unsigned int size, GLenum usage)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}
void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}