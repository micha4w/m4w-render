#pragma once

#include <GL/glew.h>

#include "GraphicBuffer.h"
#include "Shader.h"

#include "Pointer.h"

class Texture : private GraphicBuffer {
private:
    friend class FrameBuffer;

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