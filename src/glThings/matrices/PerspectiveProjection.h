#pragma once

#include "Projection.h"

class PerspectiveProjection : public Projection {
private:
    float m_Fov, m_Ratio;

public:
    PerspectiveProjection(float fov, float aspectRatio, float near, float far);
    ~PerspectiveProjection();
};