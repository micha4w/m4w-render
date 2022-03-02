#include "PerspectiveProjection.h"

#include "glm/gtc/matrix_transform.hpp"

PerspectiveProjection::PerspectiveProjection(float fov, float aspectRatio, float near, float far)
    : Projection(near, far), m_Fov(fov), m_Ratio(aspectRatio)
{
    m_Matrix = glm::perspective(fov, aspectRatio, near, far);
}

PerspectiveProjection::~PerspectiveProjection() {
    
}