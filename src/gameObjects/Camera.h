#pragma once

#include "Pointer.h"

#include "View.h"
#include "Projection.h"
#include "FrameBuffer.h"
#include "Window.h"

class Camera {
private:
    friend class GameObject;

    m4w::Pointer<View> m_View;
    m4w::Pointer<Projection> m_Projection;
    m4w::Pointer<FrameBuffer> m_FrameBuffer;
public:
    Camera(unsigned int width, unsigned int height, Projection* projection, View* view = new View());
    ~Camera();

    void SetProjection(m4w::Pointer<Projection> projection);
    void SetView(m4w::Pointer<View> view);
    void SetFrameBuffer(m4w::Pointer<FrameBuffer> frameBuffer);

    m4w::Pointer<Projection> GetProjection();
    m4w::Pointer<View> GetView();
    m4w::Pointer<FrameBuffer> GetFrameBuffer();

    void Use(class Shader* shader);
};