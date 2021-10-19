#pragma once

#include <GL/glew.h>

class IndexBuffer {
private:
    friend class VertexArray;
    friend class Mesh;

    unsigned int m_ID;
    unsigned int m_Size;
    unsigned int m_IndexCount;
    
    unsigned int m_DataType;

    void Bind ();
    static void Unbind ();
public:
    IndexBuffer (unsigned int size, void* data, unsigned int glDataType);
    ~IndexBuffer ();

    unsigned int GetIndexCount() const;
};