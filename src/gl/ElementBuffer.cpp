#include "gl/ElementBuffer.hpp"
#include "gl/gl_utils.hpp"

#include <glad/glad.h>
#include <glfw/glfw3.h>

gl::ElementBuffer::ElementBuffer()
{
    GL_CALL(glGenBuffers(1, &VBO));
    bind();
}

gl::ElementBuffer::ElementBuffer(unsigned int *data, unsigned int size)
{
    GL_CALL(glGenBuffers(1, &VBO));
    set(data, size);
}

void gl::ElementBuffer::release()
{
    GL_CALL(glDeleteBuffers(1, &VBO));
}

gl::ElementBuffer::~ElementBuffer()
{
    release();
}

void gl::ElementBuffer::set(unsigned int *data, unsigned int size, GLenum usage)
{
    bind();
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
    count = size / sizeof(unsigned int);
}

void gl::ElementBuffer::bind() const
{
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO));
}
void gl::ElementBuffer::unbind() const
{
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}