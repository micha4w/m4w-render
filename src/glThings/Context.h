#pragma once

#include "UUIDMap.h"
#include "Pointer.h"

#include "Mesh.h"
#include "Camera.h"
#include "Light.h"

class Context {
private:
    static m4w::Pointer<Context> m_Context;

public:
    class m4w::Pointer<class Window> m_Window;
    class VertexArray* m_VAO;
    class FrameBuffer* m_FBO;

    m4w::UUIDMap<Mesh> m_Meshes;
    m4w::UUIDMap<Camera> m_Cameras;
    m4w::UUIDMap<Light> m_Lights;
    m4w::UUIDMap<class GameObject*> m_Objects;

    static Context* Get() {
        return m_Context;
    }

    static void Update(unsigned int microSeconds);

    static void Draw(FrameBuffer& frameBuffer);
    static void Draw(Camera& camera);
    static void DrawCameras();

    static void CheckGLError(const char* info = "");
};
