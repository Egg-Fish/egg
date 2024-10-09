#ifndef EGG_WINDOW_H
#define EGG_WINDOW_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

class Window
{
private:
    GLFWwindow *window;

public:
    Window(unsigned int width, unsigned int height, const char *title);
    ~Window();

    void pollEvents();
    bool shouldClose() const;
};

#endif