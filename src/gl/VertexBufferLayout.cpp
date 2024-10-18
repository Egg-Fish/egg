#include "gl/VertexBufferLayout.hpp"

#include <unordered_map>
#include <string>
#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

unsigned int getSizeOfType(GLenum type)
{
    switch (type)
    {
    case GL_FLOAT:
    case GL_INT:
    case GL_UNSIGNED_INT:
        return 4;

    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
        return 1;

    default:
        std::cerr << "Warning: Could not get size of GLenum #" << type << "." << std::endl;
        return 0;
    }
}

gl::VertexBufferLayout::VertexBufferLayout()
{
    currentStride = 0;
}

void gl::VertexBufferLayout::push(unsigned int index, unsigned int count, GLenum type)
{
    unsigned int elementSize = getSizeOfType(type) * count;

    VertexBufferLayoutElement element = {
        index,
        count,
        type,
        false,
        0,
        reinterpret_cast<void *>(currentStride)}; 

    elements.push_back(element);

    currentStride += elementSize;
}

std::vector<gl::VertexBufferLayoutElement> gl::VertexBufferLayout::getElements()
{
    for (int i = 0; i < elements.size(); i++)
    {
        elements[i].stride = currentStride;
    }

    return elements;
}