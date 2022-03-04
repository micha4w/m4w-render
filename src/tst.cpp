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

int main() {

    std::cout << "Starting..\n";

    m4w::Pointer<Window> window = new Window(720, 540, "Geem");
    g_Context.m_Window = window;

    window->GetFrameBuffer()->SetClearColor(0, 0.043, 0.804);
    window->GetFrameBuffer()->Clear();
    window->Display();
    m4w::Pointer<Shader> shader(new Shader("PosColor"));

    GameObject head;
    head.CreateMesh(shader, "res/models/hed.gltf");

    GameObject player;
    player.AddComponent((Component*) new PlayerControllerComponent(10.f, 0.001f));
    
    player.CreateCamera(
        window->GetWidth(), window->GetHeight(),
        new PerspectiveProjection(m4w::Angle::Degrees(70.f).GetRadians(), window->GetWidth() / window->GetHeight(), 0.001f, 10000.f)
    );
    player.GetCamera()->SetFrameBuffer(window->GetFrameBuffer());

    GameObject camera({0.f, 0.f, -5.f});
    camera.SetRotation(m4w::Angle::Degrees(180.f), m4w::Angle());
    camera.SetScale(0.25f);
    camera.CreateCamera(
        window->GetWidth(), window->GetHeight(),
        new PerspectiveProjection(m4w::Angle::Degrees(70.f).GetRadians(), window->GetWidth() / window->GetHeight(), 0.001f, 10000.f)
    );
    camera.GetCamera()->GetFrameBuffer()->AddTexture();
    camera.GetCamera()->GetFrameBuffer()->AddDepthBuffer();
    camera.GetCamera()->GetFrameBuffer()->SetClearColor(0.f, 0.f, 0.f, 1.f);
    
    camera.CreateMesh(shader, "res/models/icosphere.gltf");
    camera.AddComponent((Component*) new PlayerControllerComponent(3.f, 0.f, GLFW_KEY_UP, GLFW_KEY_LEFT, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, GLFW_KEY_PAGE_UP, GLFW_KEY_PAGE_DOWN));


    GameObject screen;
    Mesh& screen_mesh = screen.CreateMesh(shader);
    screen_mesh.Name = "SCREEN";
    screen_mesh.SetVertexArray( VertexArray::Cube(-1.f, -1.f, 4.f, 1.f, 1.f, 5.f, 0.f, 0.f, 0.f, 0.f) );
    screen_mesh.AddTexture(1, camera.GetCamera()->GetFrameBuffer()->GetTexture());


    GameObject floor;
    Mesh& floor_mesh = floor.CreateMesh(shader);
    floor_mesh.Name = "FLOOR";
    floor_mesh.SetVertexArray( VertexArray::Cube(-10.f, -10.f, -10.f, 10.f, -9.f, 10.f, 0.2f, 0.8f, 0.1f, 1.f) );


    GameObject sphere({ 8.f, 0.f, 0.f });
    Mesh& sphere_mesh = sphere.CreateMesh(shader);
    sphere_mesh.Name = "BALLZ";
    sphere_mesh.SetVertexArray( VertexArray::Sphere(10, 5.f, 0.f, 0.f, 3.f, 0.8f, 0.2f, 0.4f, 1.f) );


    m4w::HeapArray<LightSource> lights(1);
    lights[0] = { 0.f, 100.f, 0.f, 1.f, 0.f, 0.f, 0.f };
    //lights[1] = { 0.f, 100.f, 100.f, 1.f, 0.f, 0.f, 0.f };

    //LOOOOOP
    Timer timer(60.f);
    while(!window->ShouldClose()) {
        // Update
        window->PollEvents();

        g_Context.Update(timer.GetDeltaUs());

        //if ( window->GetKeyPressed(GLFW_KEY_C) ) std::cout << glm::to_string(camera.GetPosition()) << " " << camera.GetRotation().first.GetDegrees() << ", " << camera.GetRotation().second.GetDegrees() << "\n";
        if ( window->IsKeyPressed(GLFW_KEY_V) ) std::cout << glm::to_string(player.GetPosition()) << " " << player.GetRotation().first.GetDegrees() << ", " << player.GetRotation().second.GetDegrees() << "\n";
        if ( window->WasKeyJustPressed(GLFW_KEY_F) ) {
            std::cout << "Reloading Sahder\n";
            shader->Recompile();
        }

        if ( window->WasKeyJustPressed(GLFW_KEY_ESCAPE) ) {
            window->SetMouseGrabbed( !window->IsMouseGrabbed() );
        }

        if ( window->IsMouseGrabbed() )
            window->SetMousePosition(window->GetWidth()/2, window->GetHeight()/2);

// Render
        //Context::Draw(*player.GetCamera());
        shader->SetUniformLights(lights);

        g_Context.ClearCameras();
        g_Context.DrawCameras();

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