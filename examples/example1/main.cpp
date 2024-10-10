#include "egg/window.hpp"
#include "egg/shader.hpp"
#include "egg/VertexBuffer.h"
#include "egg/VertexBufferLayout.h"

void main()
{
    Window window(800, 600, "My Window!");

    Shader shader(
        "example1/shaders/vertex.glsl",
        "example1/shaders/fragment.glsl");

    shader.use();

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    float vertices[] = {

        +0.0f, +0.5f, +0.0f, 1.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, +0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, +0.0f, 0.0f, 1.0f, 0.0f

    };

    VertexBuffer vb(vertices, sizeof(vertices));

    VertexBufferLayout vbl;
    vbl.push(0, 3, GL_FLOAT);
    vbl.push(1, 3, GL_FLOAT);

    std::vector<VertexBufferLayoutElement> elements = vbl.getElements();

    for (VertexBufferLayoutElement el : elements)
    {
        glEnableVertexAttribArray(el.index);
        glVertexAttribPointer(
            el.index,
            el.count,
            el.type,
            el.normalized,
            el.stride,
            el.offset);
    }
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.pollEvents();
        window.swapBuffers();
    }
}