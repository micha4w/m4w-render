#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "FrameBuffer.h"
#include "Shader.h"

Texture::Texture(unsigned int width, unsigned int height, unsigned char* data)
    : m_Width(width), m_Height(height)
{
    glGenTextures(1, &m_ID);
    this->Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = { 0.f, 0.f, 0.f, 0.f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
}

m4w::Pointer<Texture> Texture::FromPath(const char* path) {
    int width, height;
    unsigned char* data = stbi_load("container.jpg", &width, &height, nullptr, 0);
    return new Texture(width, height, data);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_ID); 
}

void Texture::Bind(unsigned short slot) {
    m_Slot = slot;
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind() {
    glActiveTexture(GL_TEXTURE0 + m_Slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Use(Shader& shader, unsigned short slot) {
    this->Bind(slot);
    shader.Bind();
    shader.SetUniform1i("u_Texture", slot);
    shader.SetUniform1i("u_TextureID", slot);
}

