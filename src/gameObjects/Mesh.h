#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

#include <glm/mat4x4.hpp>

#include "Pointer.h"

#include "Texture.h"
#include "VertexLayout.h"
#include "VertexArray.h"

class Mesh {
private:
    friend class GameObject;

    glm::mat4 m_ModelMatrix;

    m4w::Pointer<class VertexArray> m_VAO;
    m4w::Pointer<class VertexLayout> m_VBL;
    m4w::Pointer<class Shader> m_Shader;

    std::string m_Name;
    std::unordered_map<unsigned int, m4w::Pointer<Texture>> m_Textures;
public:
    Mesh(m4w::Pointer<class Shader> shader);
    Mesh(m4w::Pointer<class Shader> shader, const char* gltfPath);

    void SetVertexArray(m4w::Pointer<class VertexArray> vao) { m_VAO = vao; }    
    void SetVertexLayout(m4w::Pointer<class VertexLayout> vbl) {
        m_VBL = vbl;
        if ( m_VAO ) {
            m_VBL->Use(*m_VAO);
        } else {
            std::cout << "[ERROR] VertexArray needs to be added before VertexLayout in Mesh\n";
        }        
    }    

    void AddTexture(unsigned int position, m4w::Pointer<Texture> texture);

    void Render();
    Shader* GetShader();
};
