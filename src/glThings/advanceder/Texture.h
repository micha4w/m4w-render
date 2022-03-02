#pragma once

#include <GL/glew.h>

#include "Shader.h"

#include "Pointer.h"

class Texture {
private:
    friend class FrameBuffer;

    unsigned int m_ID;

    unsigned int m_Width, m_Height;
    unsigned short m_Slot;

public:
    Texture(unsigned int width, unsigned int height, unsigned char* data = nullptr);
    static m4w::Pointer<Texture> FromPath(const char* path);
    ~Texture();

    void Bind(unsigned short slot = 0);
    void Unbind();

    void Use(Shader& shader, unsigned short slot);

    void ReadImage();
    void FromPNG();
};