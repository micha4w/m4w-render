#include "VertexArray.h"

#include "Context.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_ID);
    this->Bind();
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::SetIndexBuffer(m4w::Pointer<IndexBuffer> ib) {
    this->Bind();
    m_IB = ib;
    m_IB->Bind();
}

void VertexArray::SetVertexBuffer(m4w::Pointer<VertexBuffer> vb) {
    this->Bind();
    m_VB = vb;
    m_VB->Bind();
}

void VertexArray::Bind() {
    glBindVertexArray(m_ID);
    Context::Get()->m_VAO = this;
    //if ( m_VB ) 
    //    m_VB->Bind();
    //if ( m_IB ) 
    //    m_IB->Bind();
}

void VertexArray::Unbind() {
    glBindVertexArray(0);
    Context::Get()->m_VAO = nullptr;
}
