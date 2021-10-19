#pragma once

#include <glm/glm.hpp>

class Projection {
private:
    friend class PerspectiveProjection;
    friend class OrthographicProjection;

    glm::mat4 m_Matrix;
    
    float m_Near, m_Far;
public:
  
    Projection(float near, float far);
    ~Projection();

    void Use(class Shader* shader, const char* name = "u_Projection");
};