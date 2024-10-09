#include "egg/window.hpp"

void main()
{
    Window window(800, 600, "My Window!");

    while (!window.shouldClose())
    {
        window.pollEvents();
    }
}