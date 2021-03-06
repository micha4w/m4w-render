#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

#include <glm/mat4x4.hpp>

#include "Pointer.h"
#include "Camera.h"

#include "Texture.h"
#include "VertexLayout.h"
#include "VertexArray.h"

namespace m4w {

    class Mesh {
    private:
        friend class GameObject;

        glm::mat4 m_ModelMatrix;
        glm::vec3 m_WorldPosition;

        Pointer<VertexArray> m_VAO;

        Pointer<Texture> m_Texture;
    public:
        std::string Name;

        Mesh ();
        Mesh (const char* gltfPath);

        void SetVertexArray (Pointer<VertexArray> vao);
        void SetTexture (Pointer<Texture> texture);
        
        void Render (Camera& camera);
    };
}