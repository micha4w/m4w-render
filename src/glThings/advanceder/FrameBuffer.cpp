#include "FrameBuffer.h"

#include "Context.h"
#include "Window.h"

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height), m_ClearColor{ 0.f, 0.f, 0.f, 0.f }
{
    glGenFramebuffers(1, &m_ID);
    
    this->Bind();
}

FrameBuffer::~FrameBuffer() {
    glDeleteFramebuffers(1, &m_ID);
}

void FrameBuffer::AddTexture() {
    this->Bind();
    m_Texture = new Texture(m_Width, m_Height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture->m_ID, 0);  
}

void FrameBuffer::AddDepthBuffer() {
    this->Bind();
    m_DepthBuffer = new DepthBuffer(m_Width, m_Height);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthBuffer->m_ID, 0);
}

void FrameBuffer::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
    g_Context.m_FBO = this;
}

void FrameBuffer::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    g_Context.m_FBO = g_Context.m_Window->GetFrameBuffer();
}
