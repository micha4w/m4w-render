#include "Projection.h"

#include "Shader.h"

m4w::Projection::Projection (float near, float far)
    : m_Near(near), m_Far(far), m_Matrix(1.f)
{ }

m4w::Projection::~Projection () { }

void m4w::Projection::Use (Shader* shader, const char* name) {
    shader->SetUniformMat4(name, m_Matrix);
}