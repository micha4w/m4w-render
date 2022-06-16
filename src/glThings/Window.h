#pragma once

#include <tuple>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "FrameBuffer.h"

#include "Pointer.h"
#include "Keys.h"

#define m4w_KEY_COUNT 350


namespace m4w {

    class Window {
    private:
        GLFWwindow* m_Instance;
        m4w::Pointer<FrameBuffer> m_FrameBuffer;
        bool m_GrabMouse;
        KeyState m_LastKeysPressed[m4w_KEY_COUNT];
        KeyState m_KeysPressed[m4w_KEY_COUNT];

        static void KeyCallback (GLFWwindow* glWindow, int key, int scancode, int action, int mods);

        void AddColorBuffer () = delete;
        void AddDepthBuffer () = delete;
    public:
        Window (unsigned int width, unsigned int height, const char* name);
        ~Window ();

        void Display ();
        bool ShouldClose ();
        void PollEvents ();

        std::tuple<float, float> GetMousePosition ();
        void SetMousePosition (float x, float y);

        KeyState GetKeyState (m4w::Key key);
        bool WasKeyPressed (m4w::Key key);
        bool WasKeyReleased (m4w::Key key);

        m4w::Pointer<FrameBuffer> GetFrameBuffer ();
        unsigned int GetWidth ();
        unsigned int GetHeight ();

        bool IsFocused ();
        bool IsMouseGrabbed ();
        void SetMouseGrabbed (bool grab);
    };

}
