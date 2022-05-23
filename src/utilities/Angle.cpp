#include "Angle.h"

m4w::Angle::Angle()
    : m_Degrees(0), m_Radians(0)
{ }


m4w::Angle m4w::Angle::Radians(float value) {
    m4w::Angle angle;
    
    float pi = glm::pi<float>();
    value = std::fmod(value, 2*pi);
    // if ( value < 0 )
    //     value = 2*pi - value;

    angle.m_Radians = value;
    angle.m_Degrees = glm::degrees<float>(value);

    return angle;
}

m4w::Angle m4w::Angle::Degrees(float value) {
    m4w::Angle angle;
    
    value = std::fmod(value, 360.f);
    // if ( value < 0 )
    //     value = 360.f - value;

    angle.m_Degrees = value;
    angle.m_Radians = glm::radians<float>(value);

    return angle;
}

float m4w::Angle::GetDegrees() const { return m_Degrees; }
float m4w::Angle::GetRadians() const { return m_Radians; }

float m4w::Angle::Sin() const { return glm::sin(m_Radians); }
float m4w::Angle::Cos() const { return glm::cos(m_Radians); }
float m4w::Angle::Tan() const { return glm::tan(m_Radians); }

void m4w::Angle::ClampRadians(float lower, float upper) {
    m_Radians = glm::max(lower, glm::min(upper, m_Radians));
    m_Degrees = glm::degrees<float>(m_Radians);
}
void m4w::Angle::ClampDegrees(float lower, float upper) {
    m_Degrees = glm::max(lower, glm::min(upper, m_Degrees));
    m_Radians = glm::radians<float>(m_Degrees);
}

m4w::Angle m4w::Angle::operator+ (const Angle& other) const {
    return Angle::Radians(this->m_Radians + other.m_Radians);
}

m4w::Angle m4w::Angle::operator* (const float& factor) const {
    return Angle::Radians(this->m_Radians * factor);
}

bool m4w::Angle::operator== (const m4w::Angle& other) const {
    return this->m_Radians == other.m_Radians;
}

bool m4w::Angle::operator!= (const m4w::Angle& other) const {
    return this->m_Radians != other.m_Radians;
}