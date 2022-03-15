#pragma once

#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
#include "Window.h"

#include "UUIDMap.h"
#include "Pointer.h"

class Context {
public:
    m4w::Pointer<Window> m_Window;
    VertexArray* m_VAO;
    FrameBuffer* m_FBO;

    m4w::UUIDMap<Mesh> m_Meshes;
    m4w::UUIDMap<Camera> m_Cameras;
    m4w::UUIDMap<Light> m_Lights;
    m4w::UUIDMap<class GameObject*> m_Objects;

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