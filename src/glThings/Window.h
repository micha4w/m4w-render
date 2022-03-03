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
    bool m_MouseGrabbed;
    
    uint16_t m_LastKeysPressed[350];
    uint16_t m_CurrentKeysPressed[350];

    void AddColorBuffer() = delete;
    void AddDepthBuffer() = delete;

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        std::cout << key << " " << (scancode ? "PRESS" : "RELEASE") << std::endl;
    }
public:
    Window(unsigned int width, unsigned int height, const char* name);
    ~Window();

    void Display();
    bool ShouldClose();

    std::tuple<float, float> GetMousePosition() {
        double xpos, ypos;
        glfwGetCursorPos(m_Instance, &xpos, &ypos);
        return {xpos, ypos};
    }

    void SetMousePosition(float x, float y) {
        glfwSetCursorPos(m_Instance, x, y);
    }

    bool GetKeyPressed(int key) {
        return glfwGetKey(m_Instance, key);
    }

    bool GetMousePressed(int button) {
        return glfwGetMouseButton(m_Instance, button);
    }

    m4w::Pointer<FrameBuffer> GetFrameBuffer() {
        return m_FrameBuffer;
    }

    unsigned int GetWidth() {
        return m_FrameBuffer->GetWidth();
    }

    unsigned int GetHeight() {
        return m_FrameBuffer->GetHeight();
    }

    bool IsFocused () {
        return glfwGetWindowAttrib(m_Instance, GLFW_FOCUSED);
    }

    bool IsMouseGrabbed () {
        return m_MouseGrabbed;
    }

    void SetMouseGrabbed (bool grab) {
        m_MouseGrabbed = grab;
            glfwSetInputMode(m_Instance, GLFW_CURSOR, grab ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
};