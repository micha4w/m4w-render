#include "PerspectiveProjection.h"

#include "glm/gtc/matrix_transform.hpp"

PerspectiveProjection::PerspectiveProjection (m4w::Angle fov, float aspectRatio, float near, float far)
    : Projection(near, far), m_Fov(fov), m_Ratio(aspectRatio)
{
    Recalculate();
}

PerspectiveProjection::~PerspectiveProjection () {
    
}

void PerspectiveProjection::Recalculate () {
    m_Matrix = glm::perspective(m_Fov.GetRadians(), m_Ratio, m_Near, m_Far);
}

void PerspectiveProjection::SetFOV (m4w::Angle fov) {
    m_Fov = fov;
    Recalculate();
}