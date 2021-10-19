#pragma once

#include "Component.h"

class GravityComponent : private Component {
private:
    float m_G;
public:
    GravityComponent(float g);
    void Update(unsigned int microSeconds) override; 
};