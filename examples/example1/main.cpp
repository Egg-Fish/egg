#include "egg/window.hpp"
#include "egg/shader.hpp"

void main()
{
    Window window(800, 600, "My Window!");

    Shader shader(
        "C:/Users/Eugenio/Desktop/egg/examples/example1/shaders/vertex.glsl",
        "C:/Users/Eugenio/Desktop/egg/examples/example1/shaders/fragment.glsl"
    );

    shader.use();

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    }; 

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!window.shouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.pollEvents();
        window.swapBuffers();
    }
}