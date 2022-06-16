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
#include "Light.h"

#include "GameObject.h"
#include "PlayerControllerComponent.h"


int main() {

    std::cout << "Starting..\n";

    m4w::Pointer<m4w::Window> window = new m4w::Window(800, 600, "Geem");
    m4w::g_Context.m_Window = window;
    m4w::g_Context.m_LightHandler = m4w::Pointer<m4w::LightHandler>().Create(8, 1024);

    window->GetFrameBuffer()->SetClearColor(37.f/256, 37.f/256, 38.f/256);
//    window->GetFrameBuffer()->SetClearColor(0, 0, 0, 0);
    window->GetFrameBuffer()->Clear();
    window->Display();
    m4w::Pointer<m4w::Shader> shader = new m4w::Shader("PosColor");


    m4w::GameObject head;
    head.CreateMesh("res/models/hed.gltf");

    m4w::GameObject player;
    player.AddComponent((m4w::Component*) new m4w::PlayerControllerComponent(10.f, .002f, m4w::Key::W, m4w::Key::A, m4w::Key::S, m4w::Key::D, m4w::Key::Space, m4w::Key::CapsLock));
    
    player.CreateCamera(
        window->GetWidth(), window->GetHeight(),
        0.001f, 10000.f,
        shader
    );
    player.GetCamera()->SetFrameBuffer(window->GetFrameBuffer());
    player.GetCamera()->SetPerspectiveProjection(m4w::Angle::Degrees(70.f));

    m4w::GameObject lightCamera({0.f, 0.f, -5.f});
    lightCamera.SetRotation(m4w::Angle::Degrees(180.f), m4w::Angle());
    lightCamera.CreateLight(0.f, 0.f, -5.f, .5f, 1.f, 1.f, 1.f);
    lightCamera.CreateMesh("res/models/icosphere.gltf");
    lightCamera.AddComponent((m4w::Component*) new m4w::PlayerControllerComponent(10.f, 0.f, m4w::Key::Up, m4w::Key::Left, m4w::Key::Down, m4w::Key::Right, m4w::Key::PageUp, m4w::Key::PageDown));


    m4w::GameObject screen;
    m4w::Mesh& screen_mesh = screen.CreateMesh();
    screen_mesh.Name = "SCREEN";
    screen_mesh.SetVertexArray( m4w::VertexArray::Cube(-1.f, -1.f, 4.f, 1.f, 1.f, 4.1f, 0.f, 0.f, 0.f, 0.f) );
    screen_mesh.SetTexture(
        lightCamera.GetLight()->GetCamera().GetFrameBuffer()->GetDepthBuffer()
    );
    // m4w::Pointer<m4w::Texture> test = new m4w::Texture("res/textures/world.png");
    // screen_mesh.SetTexture(test);


    m4w::GameObject floor;
    m4w::Mesh& floor_mesh = floor.CreateMesh();
    floor_mesh.Name = "FLOOR";
    floor_mesh.SetVertexArray( m4w::VertexArray::Cube(-10.f, -10.f, -10.f, 10.f, -9.f, 10.f, 0.2f, 0.8f, 0.1f, 1.f) );
    floor.Rotate(m4w::Angle(), m4w::Angle::Degrees(90));
    floor.Move({ 0, 0, 20 });


    m4w::GameObject sphere({ 8.f, 0.f, 0.f });
    m4w::Mesh& sphere_mesh = sphere.CreateMesh();
    sphere_mesh.Name = "BALLZ";
    sphere_mesh.SetVertexArray( m4w::VertexArray::Sphere(3, 3.f, 0.8f, 0.2f, 0.4f, 1.f, false) );

    std::cout << "Looping..\n";


    //LOOOOOP
    m4w::Timer timer(60.f, false);
    while ( !window->ShouldClose() ) {

    // Update
        window->PollEvents();

        m4w::g_Context.Update(timer.GetDeltaS());

        if ( window->WasKeyPressed(m4w::Key::C) )
            std::cout << glm::to_string(lightCamera.GetPosition()) << " " << lightCamera.GetRotation().first.GetDegrees() << ", " << lightCamera.GetRotation().second.GetDegrees() << "\n";
        if ( window->WasKeyPressed(m4w::Key::V) )
            std::cout << glm::to_string(player.GetPosition()) << " " << player.GetRotation().first.GetDegrees() << ", " << player.GetRotation().second.GetDegrees() << "\n";
        if ( window->WasKeyPressed(m4w::Key::F) ) {
            std::cout << "Reloading Sahder\n";
            shader->Recompile();
            m4w::g_Context.m_LightHandler->m_LightShader->Recompile();
        }

        if ( window->WasKeyPressed(m4w::Key::F2) )
            const char* x = "Breakpoint location";
        if ( window->WasKeyPressed(m4w::Key::Escape) )
            window->SetMouseGrabbed( !window->IsMouseGrabbed() );
        if ( window->WasKeyPressed(m4w::Key::LeftAlt) )
            player.GetCamera()->SetPerspectiveProjection(m4w::Angle::Degrees(30.f));
        else if ( window->WasKeyReleased(m4w::Key::LeftAlt) )
            player.GetCamera()->SetPerspectiveProjection(m4w::Angle::Degrees(70.f));

        if ( window->WasKeyPressed(m4w::Key::Q) )
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        else if ( window->WasKeyReleased(m4w::Key::Q) )
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        if ( window->IsMouseGrabbed() )
            window->SetMousePosition(window->GetWidth()/2, window->GetHeight()/2);

    // Render
        shader->SetUniform1i("u_Toggle", window->GetKeyState(m4w::Key::Z)); // This is Y key for QWERTZ

        m4w::g_Context.RedrawLights();
        m4w::g_Context.RedrawCameras();

        window->Display();
        timer.Update();
        // std::cout << timer.GetAverageFPS() << "\n";
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