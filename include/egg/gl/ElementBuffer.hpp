#ifndef EGG_ELEMENT_BUFFER_H
#define EGG_ELEMENT_BUFFER_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <algorithm>

namespace gl
{
    class ElementBuffer
    {
    private:
        unsigned int VBO;
        unsigned int count;

        void release();

    public:
        ElementBuffer();
        ElementBuffer(unsigned int *data, unsigned int size);
        ~ElementBuffer();

        ElementBuffer(const ElementBuffer &) = delete;
        ElementBuffer &operator=(const ElementBuffer &) = delete;

        // Move constructor
        ElementBuffer(ElementBuffer &&other) noexcept : VBO(other.VBO), count(other.count)
        {
            other.VBO = 0;
            other.count = 0;
        }

        ElementBuffer &operator=(ElementBuffer &&other)
        {
            // ALWAYS check for self-assignment.
            if (this != &other)
            {
                release();
                std::swap(VBO, other.VBO);
                std::swap(count, other.count);
            }

            return *this;
        }

        void set(unsigned int *data, unsigned int size, GLenum usage = GL_DYNAMIC_DRAW);

        void bind() const;
        void unbind() const;

        unsigned int getCount() { return count; };
    };
}

#endif