#ifndef EGG_MESH_H
#define EGG_MESH_H

#include "egg.hpp"

namespace egg
{
    class Mesh
    {
    private:
        gl::VertexArray *va;
        gl::ElementBuffer *eb;

    public:
        Mesh(gl::VertexArray &va);
        Mesh(gl::VertexArray &va, gl::ElementBuffer &eb);

        void bind() const;
        void unbind() const;

        unsigned int getCount() { return eb->getCount(); };
    };
}

#endif