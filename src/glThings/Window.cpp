#include "Window.h"

#include <iostream>

//#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <X11/Xos.h>
//#define GLFW_EXPOSE_NATIVE_X11

#include <GLFW/glfw3native.h>

#include "Context.h"

#ifdef GLFW_EXPOSE_NATIVE_X11
static void xwin_changeatom(GLFWwindow* window, const char* atom, const char* new_value, int prop_mode) {
    Window x11_window = glfwGetX11Window(window);
    Display* x11_display = glfwGetX11Display();
    Atom wtype = XInternAtom(x11_display, atom, false);
    Atom desk = XInternAtom(x11_display, new_value, false);
    XChangeProperty(x11_display, x11_window, wtype, 4, 32, prop_mode, (const unsigned char*) new_value, 1);
}

/* Set window types defined by the EWMH standard, possible values:
   -> "desktop", "dock", "toolbar", "menu", "utility", "splash", "dialog", "normal" */
void xwin_settype(GLFWwindow* window, const char* _net_wm_window_type) {
        xwin_changeatom(window, "_NET_WM_WINDOW_TYPE", _net_wm_window_type, PropModeReplace);
}
#endif

Window::Window (unsigned int width, unsigned int height, const char* name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_Instance = glfwCreateWindow(width, height, name, NULL, NULL);
    if (m_Instance == nullptr) {
            std::cout << "[ERROR] Failed to create GLFW window..\n";
            glfwTerminate();
            return;
    }

#ifdef GLFW_EXPOSE_NATIVE_X11
    //X11 Stuff only on linux!
    xwin_settype(m_Instance, "_NET_WM_WINDOW_TYPE_DESKTOP");
#endif

    glfwMakeContextCurrent(m_Instance);

//    glViewport(0, 0, 800, 600);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(m_Instance, Window::KeyCallback);

#ifdef RELEASE
    glfwSetInputMode(m_Instance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
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
    
    m_GrabMouse = true;
}

Window::~Window () {
    glfwTerminate();
}

void Window::Display () {
    glfwSwapBuffers(m_Instance);
}

bool Window::ShouldClose () {
    return glfwWindowShouldClose(m_Instance);
}

void Window::PollEvents () {
    for ( int i = 0 ; i < 350 ; i++ ) {
        m_LastKeysPressed[i] = m_KeysPressed[i];
    }

    glfwPollEvents();
}

std::tuple<float, float> Window::GetMousePosition () {
    double xpos, ypos;
    glfwGetCursorPos(m_Instance, &xpos, &ypos);
    return {xpos, ypos};
}

void Window::SetMousePosition (float x, float y) {
    glfwSetCursorPos(m_Instance, x, y);
}

bool Window::IsKeyPressed (int key) {
    return m_KeysPressed[key];
}

bool Window::WasKeyPressed (int key) {
    return m_KeysPressed[key] && !m_LastKeysPressed[key];
}

bool Window::WasKeyReleased (int key) {
    return m_KeysPressed[key] && !m_LastKeysPressed[key];
}

m4w::Pointer<FrameBuffer> Window::GetFrameBuffer () {
    return m_FrameBuffer;
}

unsigned int Window::GetWidth () {
    return m_FrameBuffer->GetWidth();
}

unsigned int Window::GetHeight () {
    return m_FrameBuffer->GetHeight();
}

bool Window::IsFocused () {
    return glfwGetWindowAttrib(m_Instance, GLFW_FOCUSED);
}

bool Window::IsMouseGrabbed () {
    return m_GrabMouse;
}

void Window::SetMouseGrabbed (bool grab) {
    m_GrabMouse = grab;
#ifdef RELEASE
    glfwSetInputMode(m_Instance, GLFW_CURSOR, m_GrabMouse ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
#endif
}

void Window::KeyCallback (GLFWwindow* glWindow, int key, int scancode, int action, int mods) {
    g_Context.m_Window->m_KeysPressed[key] = action;
}