#include "Window.h"

#include <iostream>

#include "Context.h"

Window::Window(Context& context, unsigned int width, unsigned int height, const char* name)
    : m_Context(context)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_Instance = glfwCreateWindow(width, height, name, NULL, NULL);
    if (m_Instance == NULL) {
            std::cout << "[ERROR] Failed to create GLFW window..\n";
            glfwTerminate();
            return;
    }
    glfwMakeContextCurrent(m_Instance);

//    glViewport(0, 0, 800, 600);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetInputMode(m_Instance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

    // GLEW
    if ( glewInit() != GLEW_OK ) {
        std::cout << "[ERROR] Failed to load GLEW...\n";
        glfwTerminate();
        return;
    }

    m_FrameBuffer = new FrameBuffer(m_Context, width, height, 0);
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
