#pragma once

#include "Angle.h"

#include "Projection.h"

class PerspectiveProjection : public Projection {
private:
    m4w::Angle m_Fov;
    float m_Ratio;

public:
    PerspectiveProjection (m4w::Angle fov, float aspectRatio, float near, float far);
    ~PerspectiveProjection ();

    void Recalculate ();
    void SetFOV (m4w::Angle fov);
};