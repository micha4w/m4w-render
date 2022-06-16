#pragma once

#include "Pointer.h"
#include "Camera.h"

namespace m4w {

    class Light {
    private:
        friend class Shader;
        friend class GameObject;
        
        m4w::Pointer<Camera> m_Camera;

        float m_Strength;
        float m_Hue[3];
        int m_TexturePos;
    public:
        Light (float x, float y, float z, float strength, float r, float g, float b);
        Light (float pos[3], float strength, float hue[3]);
        ~Light ();

        void SetCamera (m4w::Pointer<Camera> camera);
        Camera& GetCamera ();
        int GetTexturePos ();
    };

}