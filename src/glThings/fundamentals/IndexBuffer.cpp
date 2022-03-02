#include "IndexBuffer.h"

#include "Context.h"
#include "VertexArray.h"
#include "VertexLayout.h"

IndexBuffer::IndexBuffer (unsigned int size, void* data, unsigned int glDataType, unsigned int glDrawMode)
    : m_IndexCount( size / VertexLayout::glSizeof(glDataType) ),
      m_DataType(glDataType), m_DrawMode(glDrawMode)
{
    glGenBuffers(1, &m_ID);
    this->Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer (void* data, unsigned int indexCount, unsigned int glDataType, unsigned int glDrawMode)
    : m_IndexCount( indexCount ),
      m_DataType(glDataType), m_DrawMode(glDrawMode)
{
    glGenBuffers(1, &m_ID);
    this->Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * VertexLayout::glSizeof(glDataType), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer (unsigned int indexCount, unsigned int glDataType, unsigned int glDrawMode)
    : m_DrawMode(glDrawMode), m_ID(0), m_IndexCount( indexCount )
{
    // Intentionally made empty
    // Dont need a buffer, just draw Triangles 0,1,2, 3,4,5, 6,7,8, ...
}

IndexBuffer::~IndexBuffer () {
    if ( m_ID )
        glDeleteBuffers(1, &m_ID);
}

unsigned int IndexBuffer::GetIndexCount() const {
    return m_IndexCount;
}

void IndexBuffer::Bind () {
    if ( m_ID )
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind () {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

m4w::Pointer<IndexBuffer> IndexBuffer::Squares (unsigned int square_count) {
    unsigned int* indices = new unsigned int[square_count * 6];

    for ( unsigned int current_square = 0 ; current_square < square_count ; current_square += 1) {
        indices[current_square * 6 + 0] = current_square * 4 + 0;
        indices[current_square * 6 + 1] = current_square * 4 + 1;
        indices[current_square * 6 + 2] = current_square * 4 + 2;
        
        indices[current_square * 6 + 3] = current_square * 4 + 2;
        indices[current_square * 6 + 4] = current_square * 4 + 3;
        indices[current_square * 6 + 5] = current_square * 4 + 0;
    }

    IndexBuffer* ib = new IndexBuffer(indices, square_count * 6, GL_UNSIGNED_INT);
    delete[] indices;
    return ib;
}
