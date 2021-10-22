#pragma once

#include <GL/glew.h>

#include "Pointer.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"

class VertexArray {
private:
    unsigned int m_ID;
    class Context& m_Context;

public:
    m4w::Pointer<IndexBuffer> m_IB;
    m4w::Pointer<VertexBuffer> m_VB;

    VertexArray (Context& context);
    ~VertexArray ();

    void SetIndexBuffer(m4w::Pointer<IndexBuffer> ib);
    void SetVertexBuffer(m4w::Pointer<VertexBuffer> vb);

    void Bind ();
    void Unbind ();
};