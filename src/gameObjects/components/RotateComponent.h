#pragma once

#include "Angle.h"

#include "Component.h"

namespace m4w {

    class RotateComponent : private Component {
    private:
        m4w::Angle m_YawSpeed;
        m4w::Angle m_PitchSpeed;
    public:
        RotateComponent(m4w::Angle yawSpeed, m4w::Angle pitchSpeed);
        void Update(float seconds) override; 
    };
    
}