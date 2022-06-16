#include "VertexBuffer.h"

#include "Context.h"
#include "VertexArray.h"

m4w::VertexBuffer::VertexBuffer (unsigned int size, void* data)
    : m_Size(size)
{
    glGenBuffers(1, &m_ID);
    this->Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

m4w::VertexBuffer::~VertexBuffer () {
    glDeleteBuffers(1, &m_ID);
}

void m4w::VertexBuffer::Bind () {
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void m4w::VertexBuffer::Unbind () {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
