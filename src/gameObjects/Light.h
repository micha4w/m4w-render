#pragma once

#include "Pointer.h"

struct LightSource {
    float Pos[3];
    float Strength;
    float Hue[3];
};

class Light {
private:
    class GameObject* m_Owner;
    LightSource m_LightSource;

    m4w::Pointer<class Camera> m_Camera;
public:
    Light (m4w::Pointer<class Camera> camera, LightSource&& lightSource);
    Light (m4w::Pointer<class Camera> camera, float x, float y, float z, float strength, float r, float g, float b);

    void Render ();

    void SetCamera (m4w::Pointer<class Camera> camera);
    m4w::Pointer<class Camera> GetCamera ();
};