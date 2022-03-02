#include "GravityComponent.h"

#include "GameObject.h"

GravityComponent::GravityComponent(float g)
    : m_G(g)
{ }

void GravityComponent::Update(unsigned int microSeconds) {
    m_Owner->Accelerate({ 0.f, -microSeconds * m_G, 0.f });
}
