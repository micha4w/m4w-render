#include "Window.h"

#include <iostream>

#ifdef M4W_DESKTOP

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#define GLFW_EXPOSE_NATIVE_X11

#endif // M4W_DESKTOP

#include <GLFW/glfw3native.h>

#include "Context.h"

#ifdef M4W_DESKTOP

static void XChangeAtom (Display* xDisplay, Window xWindow, const char* atom_name, const char* new_value, int prop_mode) {
    Atom atom = XInternAtom(xDisplay, atom_name, false);
    Atom atom_value = XInternAtom(xDisplay, new_value, false);
    XChangeProperty(xDisplay, xWindow, atom, 4, 32, prop_mode, (const unsigned char*) &atom_value, 1);
}

static void xwin_settype (Display* xDisplay, Window xWindow, const char* _net_wm_window_type) {
}

static void ApplyXSettings (GLFWwindow* window) {
    XChangeAtom(glfwGetX11Display(), glfwGetX11Window(window), "_NET_WM_WINDOW_TYPE", "_NET_WM_WINDOW_TYPE_DESKTOP", PropModeReplace);
    XLowerWindow(glfwGetX11Display(), glfwGetX11Window(window));
    
    //XSizeHints size_hints = { .flags = PPosition | PWinGravity, .x = 0, .y = 0, .win_gravity = StaticGravity };
    //XSetWMNormalHints(glfwGetX11Display(), glfwGetX11Window(window), &size_hints);
//
    //Atom desktops = XInternAtom(glfwGetX11Display(), "_NET_WM_DESKTOP", false);
    //const uint32_t ALL_DESKTOPS = 0xFFFFFFFF;
    //XChangeProperty(glfwGetX11Display(), glfwGetX11Window(window), desktops, 6, 32, PropModeReplace, (unsigned char*) &ALL_DESKTOPS, 1);
}
#endif // M4W_DESKTOP


m4w::Window::Window (unsigned int width, unsigned int height, const char* name)
{
    if (!glfwInit()) {
        std::cout << "[ERROR] Failed to initialize glfw..\n";
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#ifdef M4W_DESKTOP
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
#endif // M4W_DESKTOP

    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_Instance = glfwCreateWindow(width, height, name, NULL, NULL);
    if (m_Instance == nullptr) {
            std::cout << "[ERROR] Failed to create GLFW window..\n";
            glfwTerminate();
            return;
    }

#ifdef M4W_DESKTOP

    //X11 Stuff only on linux!
    ApplyXSettings(m_Instance);
#endif // M4W_DESKTOP

    glfwSetWindowPos(m_Instance, 0, 0);
    glfwShowWindow(m_Instance);
    // glfwHideWindow(m_Instance);
    glfwMakeContextCurrent(m_Instance);

//    glViewport(0, 0, 800, 600);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(m_Instance, Window::KeyCallback);

#ifdef M4W_RELEASE
    glfwSetInputMode(m_Instance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif // M4W_RELEASE

    // GLEW
    if ( glewInit() != GLEW_OK ) {
        std::cout << "[ERROR] Failed to load GLEW...\n";
        glfwTerminate();
        return;
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );


    m_FrameBuffer = new FrameBuffer(width, height, 0);

    g_Context.m_BlankTexture = new Texture(0, 0);
    g_Context.m_BlankTexture->Bind(0);
    
    m_GrabMouse = true;
}

m4w::Window::~Window () {
    glfwTerminate();
}

void m4w::Window::Display () {
    glfwSwapBuffers(m_Instance);
}

bool m4w::Window::ShouldClose () {
    return glfwWindowShouldClose(m_Instance);
}

void m4w::Window::PollEvents () {
    for ( int i = 0 ; i < 350 ; i++ ) {
        m_LastKeysPressed[i] = m_KeysPressed[i];
    }

    glfwPollEvents();
}

std::tuple<float, float> m4w::Window::GetMousePosition () {
    double xpos, ypos;
    glfwGetCursorPos(m_Instance, &xpos, &ypos);
    return {xpos, ypos};
}

void m4w::Window::SetMousePosition (float x, float y) {
    glfwSetCursorPos(m_Instance, x, y);
}

bool m4w::Window::IsKeyPressed (int key) {
    return m_KeysPressed[key];
}

bool m4w::Window::WasKeyPressed (int key) {
    return m_KeysPressed[key] && !m_LastKeysPressed[key];
}

bool m4w::Window::WasKeyReleased (int key) {
    return m_KeysPressed[key] && !m_LastKeysPressed[key];
}

m4w::Pointer<m4w::FrameBuffer> m4w::Window::GetFrameBuffer () {
    return m_FrameBuffer;
}

unsigned int m4w::Window::GetWidth () {
    return m_FrameBuffer->GetWidth();
}

unsigned int m4w::Window::GetHeight () {
    return m_FrameBuffer->GetHeight();
}

bool m4w::Window::IsFocused () {
    return glfwGetWindowAttrib(m_Instance, GLFW_FOCUSED);
}

bool m4w::Window::IsMouseGrabbed () {
    return m_GrabMouse;
}

void m4w::Window::SetMouseGrabbed (bool grab) {
    m_GrabMouse = grab;
#ifdef M4W_RELEASE
    glfwSetInputMode(m_Instance, GLFW_CURSOR, m_GrabMouse ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
#endif // M4W_RELEASE
}

void m4w::Window::KeyCallback (GLFWwindow* glWindow, int key, int scancode, int action, int mods) {
    g_Context.m_Window->m_KeysPressed[key] = action;
}