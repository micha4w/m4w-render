#include "RotateComponent.h"

#include "GameObject.h"

m4w::RotateComponent::RotateComponent (m4w::Angle yawSpeed, m4w::Angle pitchSpeed)
    : m_YawSpeed(yawSpeed), m_PitchSpeed(pitchSpeed)
{ }

void m4w::RotateComponent::Update (float seconds) {
    m_Owner->Rotate(m_YawSpeed * seconds, m_PitchSpeed * seconds);
}
