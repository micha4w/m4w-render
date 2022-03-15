#pragma once

#include <inttypes.h>

#include "Component.h"

class PlayerControllerComponent : private Component {
private:
    float m_Speed, m_Sensitivity;

    uint16_t m_MoveUp,
             m_MoveDown,
             m_MoveLeft,
             m_MoveRight,
             m_MoveForward,
             m_MoveBack;
public:
    PlayerControllerComponent(float speed, float sensitvity, uint16_t moveForward = 87, uint16_t moveLeft = 65, uint16_t moveBack = 83, uint16_t moveRight = 68, uint16_t moveUp = 32, uint16_t moveDown = 340);
    void Update(float seconds) override; 
};