#include "Light.h"

m4w::Light::Light (m4w::Pointer<class Camera> camera,  LightSource&& lightSource)
    : m_Camera(camera), m_LightSource(lightSource)
{ }

m4w::Light::Light (m4w::Pointer<class Camera> camera, float x, float y, float z, float strength, float r, float g, float b)
    : Light(camera, { x, y, z, strength, r, g, b })
{ }


void m4w::Light::Render () {
    return;
}


void m4w::Light::SetCamera (m4w::Pointer<class Camera> camera) {
    m_Camera = camera;
}

m4w::Pointer<class m4w::Camera> m4w::Light::GetCamera () {
    return m_Camera;
}