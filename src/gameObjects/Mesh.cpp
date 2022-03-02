#include "Mesh.h"

#include <iostream>

#include "Context.h"

#include "GLTF.h"
#include "JSON.h"
#include "HeapArray.h"
#include "Base64.h" 

Mesh::Mesh(m4w::Pointer<Shader> shader)
    : m_Shader(shader), m_ModelMatrix(1.f)
{ }

Mesh::Mesh(m4w::Pointer<Shader> shader, const char* gltfPath)
    : Mesh(shader)
{
    m4w::Pointer<m4w::JSONObject> gltf = m4w::ReadFile(gltfPath);

    m4w::Pointer<m4w::JSONObject> jsonMesh = gltf->GetArray("meshes")->GetObject(0);
    if ( !jsonMesh ) {
        std::cout << "No mesh found in " << gltfPath << " :( ?!\n";
    }

    this->Name = *jsonMesh->GetString("name");

    m4w::HeapArray<m4w::Accessor> accessors = m4w::GetAccessors(gltf);
    m4w::HeapArray<m4w::BufferView> bufferViews = m4w::GetBufferViews(gltf);
    m4w::HeapArray<m4w::BinaryData> buffers = m4w::GetBuffers(gltf);

    m4w::Pointer<m4w::JSONArray> primitives = jsonMesh->GetArray("primitives");
    m4w::Pointer<m4w::JSONObject> attributes = primitives->GetObject(0)->GetObject("attributes");

    //TODO Material
 
    const char* options[] = { "POSITION", "NORMAL", "COLOR_0", "TEXCOORD_0" };
    std::vector<m4w::Accessor*> effectiveAccessors;
    
    
    VertexLayout vbl;
    unsigned int vertexCount = 0; 
    for ( int i = 0 ; i < 4 ; i++ ) {
        if ( attributes->Contains( options[i] ) ) {
            m4w::Pointer<m4w::JSONNumber> accesorIndex = attributes->GetNumber( options[i] );

            m4w::Accessor& accessor = accessors[*accesorIndex];
            effectiveAccessors.push_back(&accessor);
            vbl.AddElement(i, accessor.Type, accessor.ComponentType, accessor.Normalized );

            if ( vertexCount == 0 ) vertexCount = accessor.Count;
            else if ( vertexCount != accessor.Count ) std::cout << "[WARNING] Vertex data dont have the same Count!\n";
        }
    }

    m_VAO = new VertexArray();

    m4w::Accessor& indicesAccessor = accessors[*primitives->GetObject(0)->GetNumber("indices")];
    m_VAO->SetIndexBuffer( CreateIndexBuffer(indicesAccessor, bufferViews[indicesAccessor.BufferView], buffers) );
    m_VAO->SetVertexBuffer( CreateVertexBuffer(vbl.Size(), effectiveAccessors, buffers, bufferViews, vertexCount) );

    vbl.Use(*m_VAO);
}

void Mesh::AddTexture(unsigned int position, m4w::Pointer<Texture> texture) {
    if ( position == 0 ) std::cout << "[WARNING] Overriding Texture Slot 0!\n";
    m_Textures.emplace(position, texture);
}


void Mesh::Render() {
    m_VAO->Bind();

    for ( auto& [slot, texture] : m_Textures ) {
        if ( !texture ) {
            m_Textures.erase(slot);
            continue;
        }


        texture->Use(*m_Shader, slot);
    }


    m_Shader->SetUniformMat4("u_Model", m_ModelMatrix);

    if ( m_VAO->m_IB->m_ID )
        glDrawElements(GL_TRIANGLES, m_VAO->m_IB->m_IndexCount, m_VAO->m_IB->m_DataType, 0);
    else
        glDrawArrays(m_VAO->m_IB->m_DrawMode, 0, m_VAO->m_IB->m_IndexCount);
//    std::cout << "Rendering " << m_VAO->m_IB->GetIndexCount() << " indices of Type " << m_VAO->m_IB->m_DataType << "\n";

//    m_Context.m_Window->Display();

    g_Context.m_BlankTexture->Use(*m_Shader, 0);
}

Shader* Mesh::GetShader() { return m_Shader; }
