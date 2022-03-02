#include "VertexLayout.h"
 
#include <iostream>

#include <GL/glew.h>

#include "VertexArray.h"

unsigned int VertexLayout::Size() const {
    return m_Size;
}

unsigned int VertexLayout::glSizeof(unsigned int type) {
    switch (type) {
        case GL_SHORT: return sizeof(GLshort);
        case GL_UNSIGNED_SHORT: return sizeof(GLushort);
        case GL_FLOAT: return sizeof(GLfloat);
        case GL_INT: return sizeof(GLint);
        case GL_UNSIGNED_INT: return sizeof(GLuint);
        case GL_BYTE: return sizeof(GLbyte);
        case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        case GL_BOOL: return sizeof(GLboolean);
        case GL_DOUBLE: return sizeof(GLdouble);
        default: return 0;
    }
}

m4w::Pointer<VertexLayout> VertexLayout::Default() {
    VertexLayout* vbl = new VertexLayout();

    vbl->AddElement(0, 3, GL_FLOAT); // Position
    vbl->AddElement(1, 3, GL_FLOAT); // Normal
    vbl->AddElement(2, 4, GL_FLOAT); // Color
    vbl->AddElement(3, 2, GL_FLOAT); // TexCoord

    return vbl;
}

void VertexLayout::AddElement(unsigned short position, unsigned short count, unsigned int type, bool normalize) {
    VertexLayoutElement newEl = { position, count, type, normalize };
    m_Elements.push_back(newEl);
    m_Size += count * glSizeof(type);
}

void VertexLayout::Use(VertexArray& vao) {
    vao.Bind();

    unsigned long offset = 0;
    for ( VertexLayoutElement element : m_Elements ) {
        glEnableVertexAttribArray(element.Position);

        glVertexAttribPointer(element.Position, element.Count, element.Type, element.Normalized, m_Size, (const void*) offset);
        offset += element.Count * glSizeof(element.Type);
    }
}