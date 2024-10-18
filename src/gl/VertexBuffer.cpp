#include "gl/VertexBuffer.hpp"
#include "gl/gl_utils.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

gl::VertexBuffer::VertexBuffer()
{
    GL_CALL(glGenBuffers(1, &VBO));
    bind();
}

gl::VertexBuffer::VertexBuffer(void *data, unsigned int size)
{
    GL_CALL(glGenBuffers(1, &VBO));
    set(data, size);
}

gl::VertexBuffer::~VertexBuffer()
{
    GL_CALL(glDeleteBuffers(1, &VBO));
}

void gl::VertexBuffer::set(void *data, unsigned int size, GLenum usage)
{
    bind();
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
    this->size = size;
}

void gl::VertexBuffer::bind() const
{
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
}
void gl::VertexBuffer::unbind() const
{
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}