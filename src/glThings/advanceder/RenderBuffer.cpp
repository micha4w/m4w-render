#include "RenderBuffer.h"


RenderBuffer::RenderBuffer(unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height)
{
    glGenRenderbuffers(1, &m_ID);
    this->Bind();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

RenderBuffer::~RenderBuffer() {
    glDeleteRenderbuffers(1, &m_ID);
}

void RenderBuffer::Bind() {
    glBindRenderbuffer(GL_RENDERBUFFER, m_ID);
}

void RenderBuffer::Unbind() {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
