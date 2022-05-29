#include "FrameBuffer.h"

#include "Context.h"
#include "Window.h"


m4w::FrameBuffer::FrameBuffer (unsigned int width, unsigned int height, unsigned int id)
    : m_Width(width), m_Height(height), m_ID(id), m_ClearColor{ 0.f, 0.f, 0.f, 1.f }
{ }

m4w::FrameBuffer::FrameBuffer (unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height), m_ClearColor{ 0.f, 0.f, 0.f, 0.f }
{
    glGenFramebuffers(1, &m_ID);
    
    this->Bind();
}

m4w::FrameBuffer::~FrameBuffer () {
    glDeleteFramebuffers(1, &m_ID);
}

void m4w::FrameBuffer::AddTexture () {
    this->Bind();
    m_Texture = new Texture(m_Width, m_Height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture->m_ID, 0);  
}

void m4w::FrameBuffer::AddDepthBuffer () {
    this->Bind();
    m_DepthBuffer = new DepthBuffer(m_Width, m_Height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthBuffer->m_ID, 0);
}

void m4w::FrameBuffer::Bind () {
    glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
    g_Context.m_FBO = this;
}

void m4w::FrameBuffer::Unbind () {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    g_Context.m_FBO = g_Context.m_Window->GetFrameBuffer();
}
