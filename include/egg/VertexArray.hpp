#ifndef EGG_VERTEX_ARRAY_H
#define EGG_VERTEX_ARRAY_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "egg/VertexBuffer.h"
#include "egg/VertexBufferLayout.h"

class VertexArray
{
private:
    unsigned int VAO;

public:
    VertexArray();
    ~VertexArray();

    void addBuffer(VertexBuffer &vb, VertexBufferLayout &vbl);

    void bind() const;
    void unbind() const;
};

#endif