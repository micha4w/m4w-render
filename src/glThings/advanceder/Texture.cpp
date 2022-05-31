#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "FrameBuffer.h"
#include "Shader.h"

m4w::Texture::Texture (unsigned int width, unsigned int height, TextureFormat format, unsigned char* data)
    : m_Width(width), m_Height(height)
{
    glGenTextures(1, &m_ID);
    this->Bind();
    if ( format == RGBA ) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        float borderColor[] = { 0.f, 0.f, 0.f, 0.f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    } else if ( format == DEPTH ) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        float borderColor[] = { 1.f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    }

}

m4w::Texture::Texture (const char* path) {
    int width, height;

    unsigned char* data = stbi_load(path, &width, &height, nullptr, 0);
    Texture(width, height, RGBA, data);
    stbi_image_free(data);
    
    glGenerateMipmap(GL_TEXTURE_2D);
}

m4w::Texture::~Texture () {
    glDeleteTextures(1, &m_ID); 
}

void m4w::Texture::Bind (unsigned short slot) {
    m_Slot = slot;
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void m4w::Texture::Unbind () {
    glActiveTexture(GL_TEXTURE0 + m_Slot);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void m4w::Texture::Use (Shader& shader, unsigned short slot, const char* name) {
    shader.Bind();
    shader.SetUniform1i(name, slot);
    shader.SetUniform1i("u_TextureID", slot);
    Bind(slot);
}

void m4w::Texture::UseEmpty (Shader& shader, const char* name) {
    shader.Bind();
    shader.SetUniform1i(name, 0);
    shader.SetUniform1i("u_TextureID", 0);
}