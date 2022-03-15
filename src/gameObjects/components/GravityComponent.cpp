#include "GravityComponent.h"

#include "GameObject.h"

GravityComponent::GravityComponent(float g)
    : m_G(g)
{ }

void GravityComponent::Update(float seconds) {
    m_Owner->Accelerate({ 0.f, -seconds * m_G, 0.f });
}
