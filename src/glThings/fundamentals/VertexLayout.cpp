#include "VertexLayout.h"
 
#include <iostream>

#include <GL/glew.h>

#include "Context.h"
#include "VertexArray.h"

unsigned int m4w::VertexLayout::Size() const {
    return m_Size;
}

unsigned int m4w::VertexLayout::glSizeof(unsigned int type) {
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

m4w::VertexLayout& m4w::VertexLayout::GetDefault () {
    return g_Context.DefaultVertexLayout;
}


void m4w::VertexLayout::AddElement (unsigned short position, unsigned short count, unsigned int type, bool normalize) {
    VertexLayoutElement newEl = { position, count, type, normalize };
    m_Elements.push_back(newEl);
    m_Size += count * glSizeof(type);
}

void m4w::VertexLayout::Use (VertexArray& vao) {
    vao.Bind();

    unsigned long offset = 0;
    for ( VertexLayoutElement element : m_Elements ) {
        glEnableVertexAttribArray(element.Position);

        glVertexAttribPointer(element.Position, element.Count, element.Type, element.Normalized, m_Size, (const void*) offset);
        offset += element.Count * glSizeof(element.Type);
    }
}