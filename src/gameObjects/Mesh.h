#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

#include <glm/mat4x4.hpp>

#include "Pointer.h"
#include "Shader.h"

#include "Texture.h"
#include "VertexLayout.h"
#include "VertexArray.h"

class Mesh {
private:
    friend class GameObject;

    class Context& m_Context;
    glm::mat4 m_ModelMatrix;

    m4w::Pointer<VertexArray> m_VAO;
    m4w::Pointer<Shader> m_Shader;

    std::unordered_map<unsigned int, m4w::Pointer<Texture>> m_Textures;
public:
    std::string Name;

    Mesh(class Context& context, m4w::Pointer<Shader> shader);
    Mesh(class Context& context, m4w::Pointer<Shader> shader, const char* gltfPath);

    void SetVertexArray(m4w::Pointer<class VertexArray> vao) {
        m_VAO = vao;
    }

    void AddTexture(unsigned int position, m4w::Pointer<Texture> texture);

    void Render();
    Shader* GetShader();
};
