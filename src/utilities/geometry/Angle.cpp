#include "Angle.h"

#include <glm/gtc/matrix_transform.hpp>


m4w::Angle::Angle()
    : m_Degrees(0), m_Radians(0)
{ }


m4w::Angle m4w::Angle::Radians(float value) {
    m4w::Angle angle;

    angle.m_Radians = std::fmod(value, 2*m4w::m_PI);
    angle.m_Degrees = glm::degrees<float>(angle.m_Radians);

    return angle;
}

m4w::Angle m4w::Angle::Degrees(float value) {
    m4w::Angle angle;

    angle.m_Degrees = std::fmod(value, 360.f);
    angle.m_Radians = glm::radians<float>(angle.m_Degrees);

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
    return Angle::Radians(m_Radians + other.m_Radians);
}

void m4w::Angle::operator+= (const Angle& other) {
    m_Radians = std::fmod(m_Radians + other.m_Radians, 2*m4w::m_PI);
    m_Degrees = glm::degrees<float>(m_Radians);
}

m4w::Angle m4w::Angle::operator- (const Angle& other) const {
    return Angle::Radians(m_Radians - other.m_Radians);
}

void m4w::Angle::operator-= (const Angle& other) {
    m_Radians = std::fmod(m_Radians - other.m_Radians, 2*m4w::m_PI);
    m_Degrees = glm::degrees<float>(m_Radians);
}

m4w::Angle m4w::Angle::operator* (const float& factor) const {
    return Angle::Radians(m_Radians * factor);
}

void m4w::Angle::operator*= (const float& factor) {
    m_Radians = std::fmod(m_Radians * factor, 2*m4w::m_PI);
    m_Degrees = glm::degrees<float>(m_Radians);
}

bool m4w::Angle::operator== (const m4w::Angle& other) const {
    return m_Radians == other.m_Radians;
}

bool m4w::Angle::operator!= (const m4w::Angle& other) const {
    return m_Radians != other.m_Radians;
}
m4w::Angle::operator bool() const {
    return m_Radians;
}
