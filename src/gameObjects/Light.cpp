#include "Light.h"



Light::Light (m4w::Pointer<class Camera> camera,  LightSource&& lightSource)
    : m_Camera(camera), m_LightSource(lightSource)
{ }

Light::Light (m4w::Pointer<class Camera> camera, float x, float y, float z, float strength, float r, float g, float b)
    : Light(camera, { x, y, z, strength, r, g, b })
{ }


void Light::Render() {
    return;
}


void Light::SetCamera (m4w::Pointer<class Camera> camera) {
    m_Camera = camera;
}

m4w::Pointer<class Camera> Light::GetCamera () {
    return m_Camera;
}