#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/constants.hpp>

#include "Pointer.h"

#include "FrameBuffer.h"
#include "Window.h"
#include "Shader.h"
#include "Angle.h"
#include "Geometry.h"

namespace m4w {

    enum ProjectionType {
        Perspective = 0,
        Orthographic,
        NoTexture
    };

    class Camera {
    private:
        friend class GameObject;
        friend class Mesh;
        friend class Light;

        bool m_Recalculate;
        glm::mat4 m_VP;
        Rect m_DrawRect;
        Pointer<FrameBuffer> m_FrameBuffer;
        Pointer<Shader> m_Shader;

        glm::mat4 m_Projection;
        ProjectionType m_ProjectionType;
        float m_NearPlane, m_FarPlane;
        union ProjectionUnion {
            Angle FOV;
            struct {
                float Width;
                float Height;
            };

            ProjectionUnion () { Width = 0.f; Height = 0.f; }
        } m_ProjectionVars;

        glm::vec3 m_Position, m_Offset;
        Angle m_Yaw, m_Pitch;

        const glm::vec3 m_WorldUp = { 0.f, 1.f, 0.f };

        void CalculateProjection ();
        void CalculatePerspective ();
        void CalculateOrthographic ();

    public:
        Camera (float near, float far, Pointer<FrameBuffer> frameBuffer, Pointer<Shader> shader = new Shader("PosColor"));
        Camera (unsigned int width, unsigned int height, float near, float far, Pointer<Shader> shader = new Shader("PosColor"));
        ~Camera ();

        void SetPerspectiveProjection (Angle fov);
        void SetOrthographicProjection (float width, float height);

        void SetView (const glm::vec3& position = {0.f, 0.f, 0.f}, const m4w::Angle& yaw = m4w::Angle(), const m4w::Angle& pitch = m4w::Angle());
        void SetDrawRect (Rect drawRect);

        void Rotate (const m4w::Angle& dYaw, const m4w::Angle& dPitch);
        void SetRotation (const m4w::Angle& yaw, const m4w::Angle& pitch);

        void Walk (const glm::vec3& vector);
        void Move (const glm::vec3& vector);
        void Teleport (const glm::vec3& position);

        ProjectionType GetProjectionType () const { return m_ProjectionType; }
        const glm::mat4& GetMatrix () const { return m_VP; }
        const glm::vec3& GetPosition () const { return m_Position; }
        const glm::vec3& GetOffset () const { return m_Offset; }
        glm::vec2 GetRotation () const { return { m_Yaw.GetRadians(), m_Pitch.GetRadians() }; }

        Angle GetFOV () { return m_ProjectionVars.FOV; }
        float GetWidth () { return m_ProjectionVars.Width; }
        float GetHeight () { return m_ProjectionVars.Height; }

        void SetFrameBuffer (Pointer<FrameBuffer> frameBuffer);
        void SetShader (Pointer<Shader> shader);

        Pointer<FrameBuffer> GetFrameBuffer ();
        Pointer<Shader> GetShader ();

        void Use();
    };

}