#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "FrameBuffer.h"
#include "Shader.h"

Texture::Texture(unsigned int width, unsigned int height, unsigned char* data)
    : GraphicBuffer(width, height)
{
    glGenTextures(1, &m_ID);
    this->Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    float borderColor[] = { 0.f, 0.f, 0.f, 0.f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glGenerateMipmap(GL_TEXTURE_2D);
}

m4w::Pointer<Texture> Texture::FromPath(const char* path) {
    int width, height;
    unsigned char* data = stbi_load(path, &width, &height, nullptr, 0);
    Texture* texture = new Texture(width, height, data);

    stbi_image_free(data);
    return texture;
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
    shader.Bind();
    this->Bind(slot);
    shader.SetUniform1i("u_Texture", slot);
    //shader.SetUniform1i("u_TextureID", slot);
}

