#include "GravityComponent.h"

#include "GameObject.h"

m4w::GravityComponent::GravityComponent (float g)
    : m_G(g)
{ }

void m4w::GravityComponent::Update (float seconds) {
    m_Owner->Accelerate({ 0.f, -seconds * m_G, 0.f });
}
