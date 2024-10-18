#ifndef EGG_TEXTURE_H
#define EGG_TEXTURE_H

#include <glad/glad.h>
#include <algorithm>

namespace gl
{
    class Texture
    {
    private:
        unsigned int texture;

        void release();

    public:
        Texture();
        Texture(const char *path);
        ~Texture();

        // Delete copy constructor and assignment operator
        Texture(const Texture &) = delete;
        Texture &operator=(const Texture &) = delete;

        // Move constructor
        Texture(Texture &&other) noexcept : texture(other.texture)
        {
            other.texture = 0;
        }

        Texture &operator=(Texture &&other)
        {
            // ALWAYS check for self-assignment.
            if (this != &other)
            {
                release();
                std::swap(texture, other.texture);
            }

            return *this;
        }

        void bind(unsigned int textureUnit) const;
    };
}

#endif