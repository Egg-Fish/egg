#ifndef EGG_WINDOW_H
#define EGG_WINDOW_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

class Window
{
private:
    GLFWwindow *window;
    unsigned int width;
    unsigned int height;

public:
    Window(unsigned int width, unsigned int height, const char *title);
    ~Window();

    unsigned int getWidth() { return width; };
    unsigned int getHeight() { return height; };

    void pollEvents() const;
    void swapBuffers() const;
    bool shouldClose() const;
};

#endif