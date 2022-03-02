#pragma once

#include <GL/glew.h>

#include "Pointer.h"

class IndexBuffer {
private:
    friend class VertexArray;
    friend class Mesh;

    unsigned int m_ID;
    unsigned int m_IndexCount;
    
    unsigned int m_DataType;
    unsigned int m_DrawMode;

    void Bind ();
    static void Unbind ();
public:
    IndexBuffer (unsigned int size, void* data, unsigned int glDataType, unsigned int glDrawMode = GL_TRIANGLES);
    IndexBuffer (void* data, unsigned int indexCount, unsigned int glDataType, unsigned int glDrawMode = GL_TRIANGLES);
    IndexBuffer (unsigned int indexCount, unsigned int glDataType, unsigned int glDrawMode = GL_TRIANGLES);
    ~IndexBuffer ();

    unsigned int GetIndexCount () const;

    static m4w::Pointer<IndexBuffer> Squares (unsigned int square_count);
};