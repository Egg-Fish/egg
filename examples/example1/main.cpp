#include "egg/window.hpp"
#include "egg/shader.hpp"
#include "egg/VertexBuffer.h"
#include "egg/VertexBufferLayout.h"
#include "egg/VertexArray.hpp"

void main()
{
    Window window(800, 600, "My Window!");

    Shader shader(
        "example1/shaders/vertex.glsl",
        "example1/shaders/fragment.glsl");

    shader.use();

    VertexArray va;

    float vertices[] = {

        +0.0f, +0.5f, +0.0f, 1.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, +0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, +0.0f, 0.0f, 1.0f, 0.0f

    };

    VertexBuffer vb(vertices, sizeof(vertices));

    VertexBufferLayout vbl;
    vbl.push(0, 3, GL_FLOAT);
    vbl.push(1, 3, GL_FLOAT);

    va.addBuffer(vb, vbl);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.pollEvents();
        window.swapBuffers();
    }
}