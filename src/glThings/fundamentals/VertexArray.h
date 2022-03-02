#pragma once

#include <GL/glew.h>

#include "Pointer.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"

class VertexArray {
private:
    unsigned int m_ID;
    class Context& m_Context;

public:
    m4w::Pointer<IndexBuffer> m_IB;
    m4w::Pointer<VertexBuffer> m_VB;
    m4w::Pointer<VertexLayout> m_VBL;

    VertexArray (Context& context, m4w::Pointer<VertexLayout> vbl = VertexLayout::Default());
    ~VertexArray ();

    void SetIndexBuffer(m4w::Pointer<IndexBuffer> ib);
    void SetVertexBuffer(m4w::Pointer<VertexBuffer> vb);

    void Bind ();
    void Unbind ();

    static m4w::Pointer<VertexArray> Sphere(Context& context, unsigned int sub_divisions, float pos[3], float radius, float color[4]);
    static m4w::Pointer<VertexArray> Sphere(Context& context, unsigned int sub_divisions, float x, float y, float z, float radius, float r, float g, float b, float a);

    static m4w::Pointer<VertexArray> Cube(Context& context, float pos1[3], float pos2[3], float color[4]);
    static m4w::Pointer<VertexArray> Cube(Context& context, float x1, float y1, float z1, float x2, float y2, float z2, float r, float g, float b, float a);
};