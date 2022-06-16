#pragma once

#include <inttypes.h>

#include "Component.h"

#include "Keys.h"

namespace m4w {
    
    class PlayerControllerComponent : private Component {
    private:
        float m_Speed, m_Sensitivity;

        Key m_MoveUp,
            m_MoveDown,
            m_MoveLeft,
            m_MoveRight,
            m_MoveForward,
            m_MoveBack;
    public:
        PlayerControllerComponent(float speed, float sensitvity, Key moveForward, Key moveLeft, Key moveBack, Key moveRight, Key moveUp, Key moveDown);
        void Update(float seconds) override; 
    };

}