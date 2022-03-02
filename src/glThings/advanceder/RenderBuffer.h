#pragma once

#include <GL/glew.h>

class RenderBuffer {
private:
    friend class FrameBuffer;

    unsigned int m_ID;

    unsigned int m_Width, m_Height;

public:
    RenderBuffer(unsigned int width, unsigned int height);
    ~RenderBuffer();

    void Bind();
    static void Unbind();
};