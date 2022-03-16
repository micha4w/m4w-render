#pragma once

#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
#include "Window.h"

#include "UUIDMap.h"
#include "Pointer.h"

namespace m4w {

    class Context {
    public:
        Pointer<Window> m_Window;
        VertexArray* m_VAO;
        FrameBuffer* m_FBO;

        UUIDMap<Mesh> m_Meshes;
        UUIDMap<Camera> m_Cameras;
        UUIDMap<Light> m_Lights;
        UUIDMap<class GameObject*> m_Objects;

        Texture* m_BlankTexture;
        VertexLayout DefaultVertexLayout;

        Context ();

        void Update (float seconds);

    //    void Draw (FrameBuffer& frameBuffer);
        void Draw (Camera& camera);
        void ClearCameras ();
        void DrawCameras ();

        void CheckGLError (const char* info = "");
    };

    extern Context g_Context;

}