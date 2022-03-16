#pragma once

#include "Component.h"

namespace m4w {

    class GravityComponent : private Component {
    private:
        float m_G;
    public:
        GravityComponent(float g);
        void Update(float seconds) override; 
    };
    
}