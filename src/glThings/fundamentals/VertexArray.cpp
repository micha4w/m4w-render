#include "VertexArray.h"

#include "Context.h"

VertexArray::VertexArray(Context& context)
    : m_Context(context)
{
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
    m_Context.m_VAO = this;
    //if ( m_VB ) 
    //    m_VB->Bind();
    //if ( m_IB ) 
    //    m_IB->Bind();
}

void VertexArray::Unbind() {
    glBindVertexArray(0);
    m_Context.m_VAO = nullptr;
}
