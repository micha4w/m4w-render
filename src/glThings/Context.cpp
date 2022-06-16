#include "Context.h"

#include "FrameBuffer.h"
#include "GameObject.h"

m4w::Context m4w::g_Context;

m4w::Context::Context () {
    DefaultVertexLayout.AddElement(0, 3, GL_FLOAT); // Position
    DefaultVertexLayout.AddElement(1, 3, GL_FLOAT); // Normal
    DefaultVertexLayout.AddElement(2, 4, GL_FLOAT); // Color
    DefaultVertexLayout.AddElement(3, 2, GL_FLOAT); // TexCoord
}

m4w::Context::~Context() { }

void m4w::Context::Update (float seconds) {
    for ( auto [id, object] : m_Objects ) {
        object->Update(seconds);
    }
}

void m4w::Context::DrawLight (Light& light) {
    light.GetCamera().Use();
    
    int d = g_Context.m_LightHandler->GetDimensions();

    for ( auto& [id, mesh] : m_Meshes ) {
        mesh.Render(light.GetCamera());
    }
}

void m4w::Context::ClearLights () {
    m_LightHandler->GetFrameBuffer()->Clear();
}

void m4w::Context::RedrawLights () {
    ClearLights();

    for ( auto& [id, light] : m_Lights ) {
        DrawLight(light);
    }
}

void m4w::Context::DrawCamera (Camera& camera) {
    camera.Use();

    camera.GetShader()->SetUniformLights();

    for ( auto& [id, mesh] : m_Meshes ) {        
        mesh.Render(camera);
    }
}

void m4w::Context::ClearCameras () {
    for ( auto& [id, camera] : m_Cameras ) {
        camera.GetFrameBuffer()->Clear();
    }
}

void m4w::Context::RedrawCameras () {
    ClearCameras();

    for ( auto& [id, camera] : m_Cameras ) {
        DrawCamera(camera);
    }
}

void m4w::Context::CheckGLError (const char* info) {
    
    std::cerr << info;

    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
        std::cerr <<  "[GL_ERROR]:";
        do
        {
            std::string errorStr = "Unknown Error";
            switch(error)
            {
            case GL_INVALID_ENUM:
                errorStr = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                errorStr = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                errorStr = "GL_INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                errorStr = "GL_STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                errorStr = "GL_STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                errorStr = "GL_OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case GL_CONTEXT_LOST:
                errorStr = "GL_CONTEXT_LOST";
                break;
            }
            std::cerr << " " << errorStr;
        } while((error = glGetError()) != GL_NO_ERROR);
    }
    std::cerr << "\n";
}

    

