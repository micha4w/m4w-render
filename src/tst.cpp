#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Timer.h"

#include "Context.h"
#include "Window.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexLayout.h"

#include "Shader.h"
#include "PerspectiveProjection.h"
#include "OrthographicProjection.h"
#include "View.h"

#include "GameObject.h"
#include "PlayerControllerComponent.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
//    glViewport(0, 0, width, height);
}

m4w::Pointer<Context> Context::m_Context = new Context();
int main() {
    std::cout << "Starting..\n";
    
    m4w::Pointer<Window> window = new Window(720, 540, "Geem");
    Context::Get()->m_Window = window;

    window->SetClearColor(0, 0.043, 0.804);
    window->Clear();
    window->Display();
    m4w::Pointer<Shader> shader(new Shader("PosColor"));
    
    Context::Get()->m_BlankTexture = new Texture(0, 0);
    Context::Get()->m_BlankTexture->Bind(0);

    GameObject head;
    head.CreateMesh(shader, "/media/sf_share/hed.gltf");


    GameObject player;
    player.AddComponent((Component*) new PlayerControllerComponent(3.f, 0.001f));
    
    player.CreateCamera(
        window->GetWidth(), window->GetHeight(),
        new PerspectiveProjection(90.f, window->GetWidth() / window->GetHeight(), 0.001f, 10000.f)
    );
    player.GetCamera()->SetFrameBuffer(window);

    GameObject camera({0.f, 0.f, -5.f});
    camera.SetRotation(m4w::Angle::Degrees(180.f), m4w::Angle());
    camera.SetScale(0.25f);
    camera.CreateCamera(
        window->GetWidth(), window->GetHeight(),
        new PerspectiveProjection(90.f, window->GetWidth() / window->GetHeight(), 0.001f, 10000.f)
    );
    camera.GetCamera()->GetFrameBuffer()->AddTexture();
    camera.GetCamera()->GetFrameBuffer()->SetClearColor(0.f, 0.f, 0.f, 1.f);
    
    camera.CreateMesh(shader, "/media/sf_share/camera.gltf");
    camera.AddComponent((Component*) new PlayerControllerComponent(3.f, 0.f, GLFW_KEY_UP, GLFW_KEY_LEFT, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, 0, 0));



    GameObject screen;
    screen.CreateMesh(shader);
    VertexLayout* vbl = new VertexLayout();
    vbl->AddElement(0, 3, GL_FLOAT); // Position
    vbl->AddElement(1, 3, GL_FLOAT); // Normal
    vbl->AddElement(2, 4, GL_FLOAT); // Color
    vbl->AddElement(3, 2, GL_FLOAT); // TexCoord
    
    float verts[] = {
        -1.f, -1.f, 5.f,   0.f, 0.f, -1.f,   1.f, 0.f, 0.f, 1.f,   0.f, 0.f,
         1.f, -1.f, 5.f,   0.f, 0.f, -1.f,   1.f, 0.f, 0.f, 1.f,   1.f, 0.f,
        -1.f,  1.f, 5.f,   0.f, 0.f, -1.f,   1.f, 0.f, 0.f, 1.f,   0.f, 1.f,
         1.f,  1.f, 5.f,   0.f, 0.f, -1.f,   1.f, 0.f, 0.f, 1.f,   1.f, 1.f
    };
    unsigned int indis[] = {
        0,1,2, 1,2,3
    };
    VertexArray* vao = new VertexArray();
    vao->SetIndexBuffer(new IndexBuffer(sizeof(indis), indis, GL_UNSIGNED_INT));
    vao->SetVertexBuffer(new VertexBuffer(sizeof(verts), verts));
    screen.GetMesh()->SetVertexArray(vao);
    screen.GetMesh()->SetVertexLayout(vbl);
    screen.GetMesh()->AddTexture(1, camera.GetCamera()->GetFrameBuffer()->GetTexture());
    head.GetMesh()->AddTexture(1, camera.GetCamera()->GetFrameBuffer()->GetTexture());

    //LOOOOOP
    Timer timer(60.f);
    while(!window->ShouldClose()) {
        // Update
        glfwPollEvents();

        Context::Update(timer.GetDeltaUs());

        if ( window->GetKeyPressed(GLFW_KEY_C) ) std::cout << glm::to_string(camera.GetPosition()) << " " << camera.GetRotation().first.GetDegrees() << ", " << camera.GetRotation().second.GetDegrees() << "\n";
        if ( window->GetKeyPressed(GLFW_KEY_V) ) std::cout << glm::to_string(player.GetPosition()) << " " << player.GetRotation().first.GetDegrees() << ", " << player.GetRotation().second.GetDegrees() << "\n";
        if ( window->GetKeyPressed(GLFW_KEY_F) ) {
            std::cout << "Reloading Sahder\n";
            shader->Recompile();
        }

        window->SetMousePosition(window->GetWidth()/2, window->GetHeight()/2);

// Render
        window->Clear();
        camera.GetCamera()->GetFrameBuffer()->Clear();

        //Context::Draw(*player.GetCamera());
        Context::DrawCameras();

        window->Display();
        timer.Wait();
    }

    std::cout << "Stopping..\n";

    window.Delete();

    return 0;
}


/*
    Mesh* mesh = new Mesh(shader);
    VertexArray* vao = new VertexArray();

    float vertices[] = {
        -0.5f, -0.5f, 1.0f, // left  
         0.5f, -0.5f, 1.0f, // right 
         0.0f,  0.5f, 1.0f  // top   
    };
    VertexBuffer* vb = new VertexBuffer(sizeof(vertices), vertices);
    vao->SetVertexBuffer(vb);

    unsigned char indices[] = { 0, 1, 2 };
    vao->SetIndexBuffer(new IndexBuffer(sizeof(indices), indices, GL_UNSIGNED_BYTE));

    VertexLayout* vbl = new VertexLayout();
    vbl->AddElement(0, 3, GL_FLOAT);

    vbl->Use(*vao);
    mesh->SetVertexArray(vao);
    mesh->SetVertexLayout(vbl);
    head.SetMesh(mesh);
*/