#pragma once

#include <tuple>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "FrameBuffer.h"

class Window : public FrameBuffer {
private:
    GLFWwindow* m_Instance;

    void AddColorBuffer() = delete;
    void AddDepthBuffer() = delete;
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
};