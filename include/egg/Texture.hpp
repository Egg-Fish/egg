#ifndef EGG_TEXTURE_H
#define EGG_TEXTURE_H

#include <glad/glad.h>

class Texture
{
private:
    unsigned int texture;

public:
    Texture(const char *path);

    void bind(unsigned int textureUnit) const;
};

#endif