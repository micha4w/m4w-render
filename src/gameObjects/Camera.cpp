#include "Camera.h"

#include "Context.h"
#include "Shader.h"
#include "Projection.h"
#include "View.h"
#include "FrameBuffer.h"

Camera::Camera (unsigned int width, unsigned int height, Projection* projection, m4w::Pointer<Shader> shader, View* view)
    : m_Shader(shader), m_Projection(projection), m_View(view), m_FrameBuffer(new FrameBuffer(width, height))
{ }

Camera::~Camera () {
    
}

void Camera::SetProjection (m4w::Pointer<Projection> projection) {
    m_Projection = projection;
}

void Camera::SetView (m4w::Pointer<View> view) {
    m_View = view;
}

void Camera::SetFrameBuffer (m4w::Pointer<FrameBuffer> frameBuffer) {
    m_FrameBuffer = frameBuffer;
}

void Camera::SetShader (m4w::Pointer<Shader> shader) {
    m_Shader = shader;
}

m4w::Pointer<Projection> Camera::GetProjection () { return m_Projection; }
m4w::Pointer<View> Camera::GetView () { return m_View; }
m4w::Pointer<FrameBuffer> Camera::GetFrameBuffer () { return m_FrameBuffer; }
m4w::Pointer<Shader> Camera::GetShader () { return m_Shader; }

void Camera::Use () {
    m_FrameBuffer->Bind();
    
    m_View->Use(m_Shader);
    m_Projection->Use(m_Shader);
}
