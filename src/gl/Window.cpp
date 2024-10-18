#include "gl/Window.hpp"
#include "gl/gl_utils.hpp"

#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

gl::Window::Window(unsigned int width, unsigned int height, const char *title)
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
        GL_CALL(glfwTerminate());
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        GL_CALL(glfwDestroyWindow(window));
        GL_CALL(glfwTerminate());
        return;
    }

    width = width;
    height = height;
}

gl::Window::~Window()
{
    if (window) {
        GL_CALL(glfwDestroyWindow(window));
    }

    GL_CALL(glfwTerminate());
}

void gl::Window::pollEvents() const
{
    GL_CALL(glfwPollEvents());
}

void gl::Window::swapBuffers() const
{
    GL_CALL(glfwSwapBuffers(window));
}

bool gl::Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}