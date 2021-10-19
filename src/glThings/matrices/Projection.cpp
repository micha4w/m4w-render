#include "Projection.h"

#include "Shader.h"

Projection::Projection(float near, float far)
    : m_Near(near), m_Far(far), m_Matrix(1.f)
{ }

Projection::~Projection() { }

void Projection::Use(Shader* shader, const char* name) {
    shader->SetUniformMat4(name, m_Matrix);
}