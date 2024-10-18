#ifndef EGG_TEXTURE_H
#define EGG_TEXTURE_H

#include <glad/glad.h>

namespace gl
{
    class Texture
    {
    private:
        unsigned int texture;

    public:
        Texture();
        Texture(const char *path);
        ~Texture();

        void bind(unsigned int textureUnit) const;
    };
}

#endif