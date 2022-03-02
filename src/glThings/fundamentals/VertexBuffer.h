#pragma once

#include <GL/glew.h>

class VertexBuffer {
private:
    friend class VertexArray;

    unsigned int m_ID;

    unsigned int m_Size;
    //void* m_Data;

    void Bind ();
    static void Unbind ();
public:
    VertexBuffer (unsigned int size, void* data);
    ~VertexBuffer ();
};