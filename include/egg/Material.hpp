#ifndef EGG_MATERIAL_H
#define EGG_MATERIAL_H

#include "gl/Shader.hpp"
#include "gl/Texture.hpp"

namespace egg
{
    class Material
    {
    private:
        gl::Shader *shader;

        gl::Texture *albedoMap;
        gl::Texture *normalMap;
        gl::Texture *metallicMap;
        gl::Texture *roughnessMap;
        gl::Texture *ambientOcclusionMap;
        gl::Texture *heightMap;


    public:
        Material();

        void bind() const;
        void unbind() const;
    };
}

#endif