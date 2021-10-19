#include "View.h"

#include <glm/gtx/string_cast.hpp>

#include "Shader.h"

View::View(const glm::vec3& position, const m4w::Angle& yaw, const m4w::Angle& pitch)
    : m_Position(position), m_Yaw(yaw), m_Pitch(pitch), m_Matrix(1.f)
{
    this->SetRotation(yaw, pitch);
}

View::~View() {
    
}


void View::Use(Shader* shader, const char* name) {
    if ( m_Recalculate ) {
        m_Matrix = glm::lookAt(m_Position, m_Position + m_Offset, m_WorldUp);
        m_Recalculate = false;
    }
    
    shader->SetUniformMat4(name, m_Matrix);
}

void View::Rotate(const m4w::Angle& dYaw, const m4w::Angle& dPitch) {
    if ( dYaw.GetRadians() || dPitch.GetRadians() ) SetRotation(m_Yaw + dYaw, m_Pitch + dPitch);
}

void View::SetRotation(const m4w::Angle& yaw, const m4w::Angle& pitch) {
    m_Yaw = yaw;
    m_Pitch = pitch;

    m_Pitch.ClampDegrees( -89.9, 89.9 );
    float y = m_Pitch.Tan();

    float x = -m_Yaw.Sin();
    float z = -m_Yaw.Cos();

    m_Offset = { x, y, z };
    m_Recalculate = true;
}

void View::Walk(const glm::vec3& vector) {
    glm::vec3 direction = { m_Offset.x, 0.f, m_Offset.z };
    glm::vec3 strafe = glm::normalize(glm::cross(m_WorldUp, direction));

    this->Move( direction * vector.z + strafe * vector.x + m_WorldUp * vector.y );
}

void View::Move(const glm::vec3& vector) {
    if ( vector.x || vector.y || vector.z ) {
        this->Teleport(m_Position + vector);
    }
}

void View::Teleport(const glm::vec3& position) {
    m_Position = position;
    m_Recalculate = true;
}