#ifndef EGG_MODEL_H
#define EGG_MODEL_H

#include "Mesh.hpp"
#include "Material.hpp"

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace egg
{
    class Model
    {
    private:
        std::vector<egg::Mesh> meshes;
        std::vector<egg::Material> materials;

        // glm::mat4 modelMatrix;

        const aiScene *scene;

        void processMesh(aiMesh *mesh);
        void processNode(aiNode *node);

    public:
        Model();

        void load(const char *path);

        std::vector<egg::Mesh> getMeshes() { return meshes; };
        std::vector<egg::Material> getMaterials() { return materials; };
    };
}

#endif