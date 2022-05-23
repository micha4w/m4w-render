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

#include "GameObject.h"
#include "PlayerControllerComponent.h"


int main() {

    std::cout << "Starting..\n";

    m4w::Pointer<m4w::Window> window = new m4w::Window(800, 600, "Geem");
    m4w::g_Context.m_Window = window;

    window->GetFrameBuffer()->SetClearColor(0, 0.043, 0.804);
//    window->GetFrameBuffer()->SetClearColor(0, 0, 0, 0);
    window->GetFrameBuffer()->Clear();
    window->Display();
    m4w::Pointer<m4w::Shader> shader = new m4w::Shader("PosColor");
    m4w::Pointer<m4w::Shader> lightShader = new m4w::Shader("Depth");

    m4w::GameObject head;
    head.CreateMesh("res/models/hed.gltf");

    m4w::GameObject player;
    player.AddComponent((m4w::Component*) new m4w::PlayerControllerComponent(10.f, .002f));
    
    player.CreateCamera(
        window->GetWidth(), window->GetHeight(),
        0.001f, 10000.f,
        shader
    );
    player.GetCamera()->SetFrameBuffer(window->GetFrameBuffer());
    player.GetCamera()->SetPerspectiveProjection(m4w::Angle::Degrees(70.f));

    m4w::GameObject lightCamera({0.f, 0.f, -5.f});
    lightCamera.SetRotation(m4w::Angle::Degrees(180.f), m4w::Angle());
    lightCamera.CreateCamera(
        window->GetWidth(), window->GetHeight(),
        0.001f, 10000.f,
        lightShader
    );
    //lightCamera.GetCamera()->GetFrameBuffer()->AddTexture();
    lightCamera.GetCamera()->GetFrameBuffer()->AddDepthBuffer();
    
    lightCamera.CreateMesh("res/models/icosphere.gltf");
    lightCamera.AddComponent((m4w::Component*) new m4w::PlayerControllerComponent(10.f, 0.f, GLFW_KEY_UP, GLFW_KEY_LEFT, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, GLFW_KEY_PAGE_UP, GLFW_KEY_PAGE_DOWN));


    m4w::GameObject screen;
    m4w::Mesh& screen_mesh = screen.CreateMesh();
    screen_mesh.Name = "SCREEN";
    screen_mesh.SetVertexArray( m4w::VertexArray::Cube(-1.f, -1.f, 4.f, 1.f, 1.f, 5.f, 0.f, 0.f, 0.f, 0.f) );
    screen_mesh.AddTexture(1, lightCamera.GetCamera()->GetFrameBuffer()->GetDepthBuffer());


    m4w::GameObject floor;
    m4w::Mesh& floor_mesh = floor.CreateMesh();
    floor_mesh.Name = "FLOOR";
    floor_mesh.SetVertexArray( m4w::VertexArray::Cube(-10.f, -10.f, -10.f, 10.f, -9.f, 10.f, 0.2f, 0.8f, 0.1f, 1.f) );


    m4w::GameObject sphere({ 8.f, 0.f, 0.f });
    m4w::Mesh& sphere_mesh = sphere.CreateMesh();
    sphere_mesh.Name = "BALLZ";
    sphere_mesh.SetVertexArray( m4w::VertexArray::Sphere(3, 5.f, 0.f, 0.f, 3.f, 0.8f, 0.2f, 0.4f, 1.f, false) );


    m4w::HeapArray<m4w::LightSource> lights(2);
    lights[0] = { 0.f, 100.f, 0.f, 1.f, 1.f, 1.f, 0.f };
    lights[1] = { 0.f, 100.f, 100.f, 1.f, 0.f, 0.f, 1.f };

    std::cout << "Looping..\n";

    //LOOOOOP
    m4w::Timer timer(60.f);
    while ( !window->ShouldClose() ) {

    // Update
        window->PollEvents();

        m4w::g_Context.Update(timer.GetDeltaS());

        //if ( window->GetKeyPressed(GLFW_KEY_C) ) std::cout << glm::to_string(lightCamera.GetPosition()) << " " << lightCamera.GetRotation().first.GetDegrees() << ", " << lightCamera.GetRotation().second.GetDegrees() << "\n";
        if ( window->IsKeyPressed(GLFW_KEY_V) )
            std::cout << glm::to_string(player.GetPosition()) << " " << player.GetRotation().first.GetDegrees() << ", " << player.GetRotation().second.GetDegrees() << "\n";
        if ( window->WasKeyPressed(GLFW_KEY_F) ) {
            std::cout << "Reloading Sahder\n";
            shader->Recompile();
            lightShader->Recompile();
        }

        if ( window->WasKeyPressed(GLFW_KEY_ESCAPE) )
            window->SetMouseGrabbed( !window->IsMouseGrabbed() );
        if ( window->WasKeyPressed(GLFW_KEY_LEFT_ALT) )
            player.GetCamera()->SetPerspectiveProjection(m4w::Angle::Degrees(30.f));
        if ( window->WasKeyReleased(GLFW_KEY_LEFT_ALT) )
            player.GetCamera()->SetPerspectiveProjection(m4w::Angle::Degrees(70.f));

        if ( window->IsMouseGrabbed() )
            window->SetMousePosition(window->GetWidth()/2, window->GetHeight()/2);

    // Render
        //Context::Draw(*player.GetCamera());
        shader->SetUniformLights(lights);

        m4w::g_Context.ClearCameras();
        m4w::g_Context.DrawCameras();

        window->Display();
        timer.Wait();
    }

    std::cout << "Stopping..\n";

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


    //screen.CreateMesh(g_Context, shader, "/media/sf_share/plane.gltf");
    //screen.GetMesh()->AddTexture(1, Texture::FromPath("res/textures/world.png"));
    //head.GetMesh()->AddTexture(1, Texture::FromPath("res/textures/world.png"));