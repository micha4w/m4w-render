#pragma once

#include <GL/glew.h>

class Texture {
private:
    friend class FrameBuffer;

    unsigned int m_ID;

    unsigned int m_Width, m_Height;
    unsigned short m_Slot;

public:
    Texture(unsigned int width, unsigned int height);
    ~Texture();

    void Bind(unsigned short slot = 0);
    void Unbind();

    void ReadImage();
    void FromPNG();
};