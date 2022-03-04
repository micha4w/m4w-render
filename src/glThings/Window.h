#pragma once

#include <tuple>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "FrameBuffer.h"

#include "Pointer.h"

class Window {
private:
    GLFWwindow* m_Instance;
    m4w::Pointer<FrameBuffer> m_FrameBuffer;
    bool m_GrabMouse;
    bool m_LastKeysPressed[350];
    bool m_KeysPressed[350];

    static void KeyCallback (GLFWwindow* glWindow, int key, int scancode, int action, int mods);

    void AddColorBuffer () = delete;
    void AddDepthBuffer () = delete;
public:
    Window (unsigned int width, unsigned int height, const char* name);
    ~Window ();

    void Display ();
    bool ShouldClose ();

    void PollEvents () {
        for ( int i = 0 ; i < 350 ; i++ ) {
            m_LastKeysPressed[i] = m_KeysPressed[i];
        }

        glfwPollEvents();
    }

    std::tuple<float, float> GetMousePosition () {
        double xpos, ypos;
        glfwGetCursorPos(m_Instance, &xpos, &ypos);
        return {xpos, ypos};
    }

    void SetMousePosition (float x, float y) {
        glfwSetCursorPos(m_Instance, x, y);
    }

    bool IsKeyPressed (int key) {
        return m_KeysPressed[key];
    }

    bool IsKeyJustPressed (int key) {
        return m_KeysPressed[key] && !m_LastKeysPressed[key];
    }

    bool IsKeyJustReleased (int key) {
        return m_KeysPressed[key] && !m_LastKeysPressed[key];
    }

    m4w::Pointer<FrameBuffer> GetFrameBuffer () {
        return m_FrameBuffer;
    }

    unsigned int GetWidth () {
        return m_FrameBuffer->GetWidth();
    }

    unsigned int GetHeight () {
        return m_FrameBuffer->GetHeight();
    }

    bool IsFocused () {
        return glfwGetWindowAttrib(m_Instance, GLFW_FOCUSED);
    }

    bool IsMouseGrabbed () {
        return m_GrabMouse;
    }

    void SetMouseGrabbed (bool grab) {
        m_GrabMouse = grab;
        glfwSetInputMode(m_Instance, GLFW_CURSOR, m_GrabMouse ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
};