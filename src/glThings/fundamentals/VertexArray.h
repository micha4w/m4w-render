#pragma once

#include <GL/glew.h>

#include "Pointer.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"

namespace m4w {

    class VertexArray {
    private:
        unsigned int m_ID;

    public:
        m4w::Pointer<IndexBuffer> m_IB;
        m4w::Pointer<VertexBuffer> m_VB;
        VertexLayout m_VBL;

        VertexArray (VertexLayout& vbl = VertexLayout::GetDefault());
        ~VertexArray ();

        void SetIndexBuffer(m4w::Pointer<IndexBuffer> ib);
        void SetVertexBuffer(m4w::Pointer<VertexBuffer> vb);

        void Bind ();
        void Unbind ();

        static m4w::Pointer<VertexArray> Sphere(unsigned int sub_divisions, float pos[3], float radius, float color[4], bool smooth = true);
        static m4w::Pointer<VertexArray> Sphere(unsigned int sub_divisions, float x, float y, float z, float radius, float r, float g, float b, float a, bool smooth = true);

        static m4w::Pointer<VertexArray> Cube(float pos1[3], float pos2[3], float color[4]);
        static m4w::Pointer<VertexArray> Cube(float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b, float a);
    };

}