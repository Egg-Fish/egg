#include "egg/window.hpp"

#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

Window::Window(unsigned int width, unsigned int height, const char *title)
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }

    window = glfwCreateWindow(width, height, title, 0, 0);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }
}

Window::~Window()
{
    if (window) {
        glfwDestroyWindow(window);
    }

    glfwTerminate();
}

void Window::pollEvents()
{
    glfwPollEvents();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}