#pragma once

#include <glm/mat4x4.hpp>

#include "Pointer.h"

#include "FrameBuffer.h"
#include "Window.h"
#include "Shader.h"
#include "Angle.h"

namespace m4w {

    enum ProjectionType {
        Perspective = 0, Orthographic
    };

    class Camera {
    private:
        friend class GameObject;
        friend class Mesh;

        bool m_Recalculate;
        glm::mat4 m_VP;
        Pointer<FrameBuffer> m_FrameBuffer;
        Pointer<Shader> m_Shader;

        glm::mat4 m_Projection;
        ProjectionType m_ProjectionType;
        float m_NearPlane, m_FarPlane;
        Angle m_FOV;

        glm::mat4 m_View;
        glm::vec3 m_Position, m_Offset;
        Angle m_Yaw, m_Pitch;

        const glm::vec3 m_WorldUp = { 0.f, 1.f, 0.f };
        const float piHalf = glm::pi<float>() / 2;

        void CalculateProjection ();
        void CalculatePerspective ();
        void CalculateOrthographic ();

    public:
        Camera(unsigned int width, unsigned int height, float near, float far, Pointer<Shader> shader = new Shader("PosColor"));
        ~Camera();

        void SetPerspectiveProjection (Angle fov);
        void SetOrthographicProjection ();


        void SetView (const glm::vec3& position = {0.f, 0.f, 0.f}, const m4w::Angle& yaw = m4w::Angle(), const m4w::Angle& pitch = m4w::Angle());

        void Rotate(const m4w::Angle& dYaw, const m4w::Angle& dPitch);
        void SetRotation(const m4w::Angle& yaw, const m4w::Angle& pitch);

        void Walk(const glm::vec3& vector);
        void Move(const glm::vec3& vector);
        void Teleport(const glm::vec3& position);

        const glm::vec3& GetPosition() { return m_Position; }
        glm::vec2 GetRotation() { return { m_Yaw.GetRadians(), m_Pitch.GetRadians() }; }


        void SetFrameBuffer (Pointer<FrameBuffer> frameBuffer);
        void SetShader (Pointer<Shader> shader);

        Pointer<FrameBuffer> GetFrameBuffer ();
        Pointer<Shader> GetShader ();

        void Use();
    };

}