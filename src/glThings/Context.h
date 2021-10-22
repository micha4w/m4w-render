#pragma once

#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
#include "Window.h"

#include "UUIDMap.h"
#include "Pointer.h"

class Context {
private:
    static m4w::Pointer<Context> m_Context;

public:
    m4w::Pointer<Window> m_Window;
    VertexArray* m_VAO;
    FrameBuffer* m_FBO;

    m4w::UUIDMap<Mesh> m_Meshes;
    m4w::UUIDMap<Camera> m_Cameras;
    m4w::UUIDMap<Light> m_Lights;
    m4w::UUIDMap<class GameObject*> m_Objects;

    Texture* m_BlankTexture;

    Context() {}

    static Context* Get() {
        return m_Context;
    }

    static void Update(unsigned int microSeconds);

    static void Draw(FrameBuffer& frameBuffer);
    static void Draw(Camera& camera);
    static void DrawCameras();

    static void CheckGLError(const char* info = "");
};
