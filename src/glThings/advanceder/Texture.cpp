#include "Texture.h"

#include "FrameBuffer.h"
#include "Shader.h"

Texture::Texture(unsigned int width, unsigned int height)
    : m_Width(width), m_Height(height)
{
    glGenTextures(1, &m_ID);
    this->Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = { 0.f, 0.f, 0.f, 0.f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
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


void Texture::Use(class Shader* shader, unsigned short slot) {
    this->Bind(slot);
    shader->Bind();
    shader->SetUniform1i("u_Texture", slot);
    shader->SetUniform1i("u_TextureID", slot);
}
