#include "Camera.h"

#include "Context.h"
#include "Shader.h"
#include "Projection.h"
#include "View.h"
#include "FrameBuffer.h"

m4w::Camera::Camera (unsigned int width, unsigned int height, Projection* projection, m4w::Pointer<Shader> shader, View* view)
    : m_Shader(shader), m_Projection(projection), m_View(view), m_FrameBuffer(new FrameBuffer(width, height))
{ }

m4w::Camera::~Camera () {
    
}

void m4w::Camera::SetProjection (m4w::Pointer<Projection> projection) {
    m_Projection = projection;
}

void m4w::Camera::SetView (m4w::Pointer<View> view) {
    m_View = view;
}

void m4w::Camera::SetFrameBuffer (m4w::Pointer<FrameBuffer> frameBuffer) {
    m_FrameBuffer = frameBuffer;
}

void m4w::Camera::SetShader (m4w::Pointer<Shader> shader) {
    m_Shader = shader;
}

m4w::Pointer<m4w::Projection>   m4w::Camera::GetProjection  () { return m_Projection; }
m4w::Pointer<m4w::View>         m4w::Camera::GetView        () { return m_View; }
m4w::Pointer<m4w::FrameBuffer>  m4w::Camera::GetFrameBuffer () { return m_FrameBuffer; }
m4w::Pointer<m4w::Shader>       m4w::Camera::GetShader      () { return m_Shader; }

void m4w::Camera::Use () {
    m_FrameBuffer->Bind();
    
    m_View->Use(m_Shader);
    m_Projection->Use(m_Shader);
}
