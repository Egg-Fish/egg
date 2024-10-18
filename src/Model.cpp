#include "Model.hpp"

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

egg::Model::Model()
{

}

void egg::Model::processMesh(aiMesh *mesh)
{
    gl::VertexArray *va = new gl::VertexArray;
    gl::VertexBuffer *vb = new gl::VertexBuffer;

    std::vector<float> vertexData;

    const bool containsTextureCoords = mesh->mTextureCoords[0];

    for (int i = 0; i < mesh->mNumVertices; i++)
    {
        vertexData.push_back(mesh->mVertices[i].x);
        vertexData.push_back(mesh->mVertices[i].y);
        vertexData.push_back(mesh->mVertices[i].z);

        vertexData.push_back(mesh->mNormals[i].x);
        vertexData.push_back(mesh->mNormals[i].y);
        vertexData.push_back(mesh->mNormals[i].z);

        if(containsTextureCoords) 
        {
            vertexData.push_back(mesh->mTextureCoords[0][i].x);
            vertexData.push_back(mesh->mTextureCoords[0][i].y);
        }
    }

    vb->set(vertexData.data(), sizeof(float) * vertexData.size());

    // Define layout
    gl::VertexBufferLayout vbl; // FIXME just in case this stack alloc causes bugs
    vbl.push(0, 3, GL_FLOAT);
    vbl.push(1, 3, GL_FLOAT);
    if (containsTextureCoords)
    {
        vbl.push(2, 2, GL_FLOAT);
    }

    va->addBuffer(*vb, vbl);

    gl::ElementBuffer *eb = new gl::ElementBuffer();

    std::vector<unsigned int> indices;

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    } 

    eb->set(indices.data(), sizeof(unsigned int) * indices.size());

    this->meshes.push_back(
        egg::Mesh(
            *va,
            *eb
        )
    );
}

void egg::Model::processNode(aiNode *node)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i]);
    }
}

void egg::Model::load(const char *path)
{
    Assimp::Importer importer;
    const unsigned int flags = aiProcess_Triangulate | aiProcess_FlipUVs;
    scene = importer.ReadFile(path, flags);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "Error: " << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode);
}