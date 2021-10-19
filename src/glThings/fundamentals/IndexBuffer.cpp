#include "IndexBuffer.h"

#include "Context.h"
#include "VertexArray.h"
#include "VertexLayout.h"

IndexBuffer::IndexBuffer (unsigned int size, void* data, unsigned int glDataType)
    : m_Size(size), /*m_Data(data),*/ m_DataType(glDataType), m_IndexCount( m_Size / VertexLayout::glSizeof(glDataType) )
{
    glGenBuffers(1, &m_ID);
    this->Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer () {
    glDeleteBuffers(1, &m_ID);
}

unsigned int IndexBuffer::GetIndexCount() const {
    return m_IndexCount;
}

void IndexBuffer::Bind () {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind () {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}