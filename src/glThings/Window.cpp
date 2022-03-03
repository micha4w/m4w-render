#include "Window.h"

#include <iostream>

#include "Context.h"

Window::Window(unsigned int width, unsigned int height, const char* name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_Instance = glfwCreateWindow(width, height, name, NULL, NULL);
    if (m_Instance == nullptr) {
            std::cout << "[ERROR] Failed to create GLFW window..\n";
            glfwTerminate();
            return;
    }
    glfwMakeContextCurrent(m_Instance);

//    glViewport(0, 0, 800, 600);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(m_Instance, Window::KeyCallback);
    glfwSetInputMode(m_Instance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // GLEW
    if ( glewInit() != GLEW_OK ) {
        std::cout << "[ERROR] Failed to load GLEW...\n";
        glfwTerminate();
        return;
    }

    m_FrameBuffer = new FrameBuffer(width, height, 0);

    g_Context.m_BlankTexture = new Texture(0, 0);
    g_Context.m_BlankTexture->Bind(0);
//    Context::Get()->m_Window = this;
}

Window::~Window() {
    glfwTerminate();
}

void Window::Display() {
    glfwSwapBuffers(m_Instance);
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(m_Instance);
}
