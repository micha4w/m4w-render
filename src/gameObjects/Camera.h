#pragma once

#include "Pointer.h"

#include "View.h"
#include "Projection.h"
#include "FrameBuffer.h"
#include "Window.h"
#include "Shader.h"

namespace m4w {

    class Camera {
    private:
        friend class GameObject;

        Pointer<View> m_View;
        Pointer<Projection> m_Projection;
        Pointer<FrameBuffer> m_FrameBuffer;
        Pointer<Shader> m_Shader;
    public:
        Camera(unsigned int width, unsigned int height, Projection* projection, Pointer<Shader> shader = new Shader("PosColor"), View* view = new View());
        ~Camera();

        void SetProjection (Pointer<Projection> projection);
        void SetView (Pointer<View> view);
        void SetFrameBuffer (Pointer<FrameBuffer> frameBuffer);
        void SetShader (Pointer<Shader> shader);

        Pointer<Projection> GetProjection ();
        Pointer<View> GetView ();
        Pointer<FrameBuffer> GetFrameBuffer ();
        Pointer<Shader> GetShader ();

        void Use();
    };

}