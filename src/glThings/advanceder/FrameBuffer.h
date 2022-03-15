#pragma once

#include <GL/glew.h>
#include <memory>

#include "Pointer.h"

#include "Texture.h"
#include "DepthBuffer.h"

class FrameBuffer {
private:
    friend class Window;
    friend class Camera;

    unsigned int m_ID;

    unsigned int m_Width, m_Height;
    float m_ClearColor[4];

    m4w::Pointer<Texture> m_Texture;
    m4w::Pointer<DepthBuffer> m_DepthBuffer;

    FrameBuffer(unsigned int width, unsigned int height, unsigned int id)
    : m_Width(width), m_Height(height), m_ID(id), m_ClearColor{ 0.f, 0.f, 0.f, 1.f }
    { }

public:
    FrameBuffer(unsigned int width, unsigned int height);
    ~FrameBuffer();

    void AddTexture();
    void AddDepthBuffer();
    bool HasTexture() const { return m_Texture; };
    bool HasDepthBuffer() const { return m_DepthBuffer; };
    m4w::Pointer<Texture> GetTexture() { return m_Texture; }
    m4w::Pointer<DepthBuffer> GetDepthBuffer() { return m_DepthBuffer; }

    void Bind();
    void Unbind();


    void SetClearColor(float r, float g, float b, float a = 1.f) {
        m_ClearColor[0] = r;
        m_ClearColor[1] = g;
        m_ClearColor[2] = b;
        m_ClearColor[3] = a;
    }

    void Clear() {
        this->Bind();
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }
    void ClearTexture() {
        this->Bind();
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void ClearDepthBuffer() {
        this->Bind();
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    unsigned int GetWidth() const { return m_Width; }
    unsigned int GetHeight() const { return m_Height; }
};