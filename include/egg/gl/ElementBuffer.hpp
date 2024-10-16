#ifndef EGG_ELEMENT_BUFFER_H
#define EGG_ELEMENT_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace gl
{
    class ElementBuffer
    {
    private:
        unsigned int VBO;
        unsigned int count;

    public:
        ElementBuffer();
        ElementBuffer(unsigned int *data, unsigned int size);
        ~ElementBuffer();

        void set(unsigned int *data, unsigned int size, GLenum usage = GL_DYNAMIC_DRAW);

        void bind() const;
        void unbind() const;

        unsigned int getCount() { return count; };
    };
}

#endif