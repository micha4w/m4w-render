#include "VertexBuffer.h"

#include "Context.h"
#include "VertexArray.h"

VertexBuffer::VertexBuffer (unsigned int size, void* data)
    : m_Size(size)//, m_Data(data)
{

    glGenBuffers(1, &m_ID);
    this->Bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer () {
    glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::Bind () {
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::Unbind () {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
