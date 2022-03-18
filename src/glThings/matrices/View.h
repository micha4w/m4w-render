#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Angle.h"

namespace m4w {

    class View {
    private:
        friend class GameObject;
        friend class Camera;

        glm::mat4 m_Matrix;
        glm::vec3 m_Position, m_Offset;
        glm::vec3 m_WorldUp = { 0.f, 1.f, 0.f };

        m4w::Angle m_Yaw, m_Pitch;

        bool m_Recalculate = false;

        const float piHalf = glm::pi<float>() / 2;
    public:
        View(const glm::vec3& position = {0.f, 0.f, 0.f}, const m4w::Angle& yaw = m4w::Angle(), const m4w::Angle& pitch = m4w::Angle());
        ~View();

        static void UseDirectly(const glm::vec3& position, const m4w::Angle& yaw, const m4w::Angle& pitch, class Shader* shader, const char* name = "u_View");
        void Use(class Shader* shader, const char* name = "u_View");
        void Rotate(const m4w::Angle& dYaw, const m4w::Angle& dPitch);
        void SetRotation(const m4w::Angle& yaw, const m4w::Angle& pitch);

        void Walk(const glm::vec3& vector);
        void Move(const glm::vec3& vector);
        void Teleport(const glm::vec3& position);

        const glm::vec3& GetPosition() { return m_Position; }
        glm::vec2 GetRotation() { return { m_Yaw.GetRadians(), m_Pitch.GetRadians() }; }
    };

}