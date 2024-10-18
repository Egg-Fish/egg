#include "gl/Texture.hpp"
#include "gl/gl_utils.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

gl::Texture::Texture()
{
    texture = 0;
}

gl::Texture::Texture(const char *path)
{
    GL_CALL(glGenTextures(1, &texture));
    bind(0);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
        GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else
    {
        std::cerr << "Error: Failed to load texture at " << path << std::endl;
        std::cerr << stbi_failure_reason() << std::endl;
    }
    stbi_image_free(data);
}

gl::Texture::~Texture()
{
    // Silently ignores texture = 0;
    GL_CALL(glDeleteTextures(0, &texture));
}

void gl::Texture::bind(unsigned int textureUnit) const
{
    GL_CALL(glActiveTexture(GL_TEXTURE0 + textureUnit));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, texture));
}