#pragma once

#include "Pointer.h"

#include "View.h"
#include "Projection.h"
#include "FrameBuffer.h"
#include "Window.h"
#include "Shader.h"

class Camera {
private:
    friend class GameObject;

    m4w::Pointer<View> m_View;
    m4w::Pointer<Projection> m_Projection;
    m4w::Pointer<FrameBuffer> m_FrameBuffer;
    m4w::Pointer<Shader> m_Shader;
public:
    Camera(unsigned int width, unsigned int height, Projection* projection, m4w::Pointer<Shader> shader = new Shader("PosColor"), View* view = new View());
    ~Camera();

    void SetProjection (m4w::Pointer<Projection> projection);
    void SetView (m4w::Pointer<View> view);
    void SetFrameBuffer (m4w::Pointer<FrameBuffer> frameBuffer);
    void SetShader (m4w::Pointer<Shader> shader);

    m4w::Pointer<Projection> GetProjection ();
    m4w::Pointer<View> GetView ();
    m4w::Pointer<FrameBuffer> GetFrameBuffer ();
    m4w::Pointer<Shader> GetShader ();

    void Use();
};