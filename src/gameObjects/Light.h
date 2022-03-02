#pragma once

#include "HeapArray.h"

struct LightSource {
    float Pos[3];
    float Strength;
    float Hue[3];
};

class Light {
private:
    class GameObject* m_Owner;

    m4w::HeapArray<class Camera> m_Cameras;
public:

    void Render(unsigned int microSeconds);
};