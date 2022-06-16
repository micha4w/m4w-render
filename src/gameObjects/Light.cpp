#include "Light.h"

#include "Context.h"

#include "Camera.h"

m4w::Light::Light (float x, float y, float z, float strength, float r, float g, float b)
    : m_Strength(strength), m_Hue{r, g, b}, m_TexturePos(g_Context.m_LightHandler->GetFreePos()),
      m_Camera(new Camera(0.1f, 100.f, g_Context.m_LightHandler->GetFrameBuffer(), g_Context.m_LightHandler->m_LightShader))
{
    m_Camera->SetOrthographicProjection(40, 40);
    m_Camera->m_Position = {x, y, z};

    int d = g_Context.m_LightHandler->GetDimensions();

    m_Camera->SetDrawRect({
        {
            m_TexturePos / d / (float) d * g_Context.m_LightHandler->GetFrameBuffer()->GetWidth(),
            m_TexturePos % d / (float) d * g_Context.m_LightHandler->GetFrameBuffer()->GetHeight()
        },
        {
            m_Camera->m_FrameBuffer->GetWidth() / d,
            m_Camera->m_FrameBuffer->GetHeight() / d
        }
    });
    
}

m4w::Light::Light (float pos[3], float strength, float hue[3])
    : Light(pos[0], pos[1], pos[2], strength, hue[0], hue[1], hue[2])
{ }

m4w::Light::~Light () {
    g_Context.m_LightHandler->Delete(m_TexturePos);
}

void m4w::Light::SetCamera (m4w::Pointer<Camera> camera) {
    m_Camera = camera;
}

m4w::Camera& m4w::Light::GetCamera () {
    return *m_Camera;
}

int m4w::Light::GetTexturePos () {
    return m_TexturePos;
}
