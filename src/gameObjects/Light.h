#pragma once

#include "HeapArray.h"

class Light {
private:
    class GameObject* m_Owner;

    m4w::HeapArray<class Camera> m_Cameras;
public:

    void Render(unsigned int microSeconds);
};