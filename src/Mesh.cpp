#include "Mesh.hpp"

#include "egg.hpp"
#include <vector>

egg::Mesh::Mesh(gl::VertexArray &vertexArray)
{
    this->va = &vertexArray;
    std::vector<unsigned int> elements;
    for (unsigned int i = 0; i < vertexArray.getCount(); i++)
    {
        elements.push_back(i);
    }

    this->eb = new gl::ElementBuffer(elements.data(), sizeof(unsigned int) * vertexArray.getCount());
    bind();
}

egg::Mesh::Mesh(gl::VertexArray &vertexArray, gl::ElementBuffer &elementBuffer)
{
    this->va = &vertexArray;
    this->eb = &elementBuffer;
    
    bind();
}

void egg::Mesh::bind() const
{
    va->bind();
    eb->bind();
}

void egg::Mesh::unbind() const
{
    va->bind();
    eb->unbind();
}