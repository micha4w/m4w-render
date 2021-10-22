#include "Camera.h"

#include "Context.h"
#include "Shader.h"
#include "Projection.h"
#include "View.h"
#include "FrameBuffer.h"

Camera::Camera(Context& context, unsigned int width, unsigned int height, Projection* projection, View* view)
    : m_Context(context), m_Projection(projection), m_View(view), m_FrameBuffer(new FrameBuffer(context, width, height))
{ }

Camera::~Camera() {
    
}

void Camera::SetProjection(m4w::Pointer<Projection> projection) {
    m_Projection = projection;
}

void Camera::SetView(m4w::Pointer<View> view) {
    m_View = view;
}

void Camera::SetFrameBuffer(m4w::Pointer<FrameBuffer> frameBuffer) {
    m_FrameBuffer = frameBuffer;
}

m4w::Pointer<Projection> Camera::GetProjection() { return m_Projection; }
m4w::Pointer<View> Camera::GetView() { return m_View; }
m4w::Pointer<FrameBuffer> Camera::GetFrameBuffer() { return m_FrameBuffer; }

void Camera::Use(class Shader* shader) {
    m_View->Use(shader);
    m_Projection->Use(shader);
}
