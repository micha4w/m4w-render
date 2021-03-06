#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Context.h"
#include "Shader.h"
#include "FrameBuffer.h"

m4w::Camera::Camera (float near, float far, Pointer<FrameBuffer> frameBuffer, m4w::Pointer<Shader> shader)
    : m_Shader(shader), m_NearPlane(near), m_FarPlane(far),
      m_FrameBuffer(frameBuffer), m_ProjectionType(Orthographic),
      m_Position({0.f}), m_Yaw(m4w::Angle()), m_Pitch(m4w::Angle()), m_Recalculate(true),
      m_DrawRect{{0.f, 0.f}, {frameBuffer->m_Width, frameBuffer->m_Height}}
{ }

m4w::Camera::Camera (unsigned int width, unsigned int height, float near, float far, m4w::Pointer<Shader> shader)
    : Camera(near, far, new FrameBuffer(width, height), shader)
{ }

m4w::Camera::~Camera () { }

void m4w::Camera::SetPerspectiveProjection (m4w::Angle fov) {
    if ( m_ProjectionType != Perspective || m_ProjectionVars.FOV != fov ) {
        m_ProjectionType = Perspective;
        m_ProjectionVars.FOV = fov;
        
        m_Recalculate = true;
    }
}


void m4w::Camera::SetOrthographicProjection (float width, float height) {
    if ( m_ProjectionType != Orthographic || m_ProjectionVars.Width != width ||m_ProjectionVars.Height == height ) {
        m_ProjectionType = Orthographic;
        m_ProjectionVars.Width = width;
        m_ProjectionVars.Height = height;

        m_Recalculate = true;
    }
}

void m4w::Camera::SetView (const glm::vec3& position, const m4w::Angle& yaw, const m4w::Angle& pitch) {
    SetRotation(yaw, pitch);
}

void m4w::Camera::SetDrawRect (Rect drawRect) {
    m_DrawRect = drawRect;
}

void m4w::Camera::Rotate (const m4w::Angle& dYaw, const m4w::Angle& dPitch) {
    if ( dYaw.GetRadians() || dPitch.GetRadians() )
        SetRotation(m_Yaw + dYaw, m_Pitch + dPitch);
}

void m4w::Camera::SetRotation (const m4w::Angle& yaw, const m4w::Angle& pitch) {
    m_Yaw = yaw;
    m_Pitch = pitch;

    m_Pitch.ClampDegrees( -89.9, 89.9 );
    float y = m_Pitch.Tan();
    
    float x = -m_Yaw.Sin();
    float z = -m_Yaw.Cos();

    m_Offset = { x, y, z };
    m_Recalculate = true;
}

void m4w::Camera::Walk (const glm::vec3& vector) {
    glm::vec3 direction = { m_Offset.x, 0.f, m_Offset.z };
    glm::vec3 strafe = glm::normalize(glm::cross(m_WorldUp, direction));

    Move( direction * vector.z + strafe * vector.x + m_WorldUp * vector.y );
}

void m4w::Camera::Move (const glm::vec3& vector) {
    if ( vector.x || vector.y || vector.z )
        Teleport(m_Position + vector);
}

void m4w::Camera::Teleport (const glm::vec3& position) {
    m_Position = position;
    m_Recalculate = true;
}

void m4w::Camera::SetFrameBuffer (m4w::Pointer<FrameBuffer> frameBuffer) {
    m_FrameBuffer = frameBuffer;
}

void m4w::Camera::SetShader (m4w::Pointer<Shader> shader) {
    m_Shader = shader;
}

m4w::Pointer<m4w::FrameBuffer> m4w::Camera::GetFrameBuffer () {
    return m_FrameBuffer; 
}

m4w::Pointer<m4w::Shader> m4w::Camera::GetShader () {
    return m_Shader;
}

void m4w::Camera::Use () {
    m_Shader->Bind();
    m_FrameBuffer->Bind();
    glViewport(m_DrawRect.corner.x, m_DrawRect.corner.y, m_DrawRect.size.x, m_DrawRect.size.y);

    if ( m_Recalculate ) {
        CalculateProjection();
        m_VP = m_Projection * glm::lookAt(m_Position, m_Position + m_Offset, m_WorldUp);

        m_Recalculate = false;
    }
}

void m4w::Camera::CalculateProjection () {
    if ( m_ProjectionType == Perspective )
        CalculatePerspective();
    else
        CalculateOrthographic();
}

void m4w::Camera::CalculatePerspective () {
    m_Projection = glm::perspective(
        m_ProjectionVars.FOV.GetRadians(),
        (float) m_FrameBuffer->m_Width / m_FrameBuffer->m_Height,
        m_NearPlane, m_FarPlane
    );
}

void m4w::Camera::CalculateOrthographic () {
    float w_d2 = m_ProjectionVars.Width / 2.f;
    float h_d2 = m_ProjectionVars.Height / 2.f;
    m_Projection = glm::ortho(-w_d2, w_d2, -h_d2, h_d2, m_NearPlane, m_FarPlane);
}