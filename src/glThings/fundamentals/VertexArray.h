#pragma once

#include <GL/glew.h>

#include "Pointer.h"

#include "IndexBuffer.h"
#include "VertexBuffer.h"

class VertexArray {
private:
    unsigned int m_ID;
    
public:
    m4w::Pointer<IndexBuffer> m_IB;
    m4w::Pointer<VertexBuffer> m_VB;

    VertexArray ();
    ~VertexArray ();

    void SetIndexBuffer(m4w::Pointer<IndexBuffer> ib);
    void SetVertexBuffer(m4w::Pointer<VertexBuffer> vb);

    void Bind ();
    static void Unbind ();
};