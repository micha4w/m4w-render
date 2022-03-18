#include "OrthographicProjection.h"

#include "glm/gtc/matrix_transform.hpp"

m4w::OrthographicProjection::OrthographicProjection (float width, float height, float near, float far)
    : Projection(near, far), m_Width(width), m_Height(height)
{
    m_Matrix = glm::ortho(-width/2, width/2, -height/2, height/2, near, far);
}

m4w::OrthographicProjection::~OrthographicProjection () {
    
}
