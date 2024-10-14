#include "egg/VertexBufferLayout.hpp"

#include <unordered_map>
#include <string>

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
        return 0;
    }
}

VertexBufferLayout::VertexBufferLayout()
{
}

void VertexBufferLayout::push(unsigned int index, unsigned int count, GLenum type)
{
    unsigned int elementSize = getSizeOfType(type) * count;

    VertexBufferLayoutElement element = {
        index,
        count,
        type,
        false,
        0,
        (void *)offset};

    elements.push_back(element);

    offset += elementSize;
}

std::vector<VertexBufferLayoutElement> VertexBufferLayout::getElements()
{
    for (int i = 0; i < elements.size(); i++)
    {
        elements[i].stride = offset;
    }

    return elements;
}