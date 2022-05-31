#include "Mesh.h"

#include <iostream>

#include "Context.h"

#include "GLTF.h"
#include "JSON.h"
#include "HeapArray.h"
#include "Base64.h" 

m4w::Mesh::Mesh ()
    : m_ModelMatrix(1.f)
{ }

m4w::Mesh::Mesh (const char* gltfPath)
    : Mesh()
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

    m_VAO = new VertexArray(vbl);

    m4w::Accessor& indicesAccessor = accessors[*primitives->GetObject(0)->GetNumber("indices")];
    m_VAO->SetIndexBuffer( CreateIndexBuffer(indicesAccessor, bufferViews[indicesAccessor.BufferView], buffers) );
    m_VAO->SetVertexBuffer( CreateVertexBuffer(vbl.Size(), effectiveAccessors, buffers, bufferViews, vertexCount) );
}

void m4w::Mesh::SetVertexArray(m4w::Pointer<class VertexArray> vao) {
    m_VAO = vao;
}

void m4w::Mesh::SetTexture (m4w::Pointer<Texture> texture) {
    m_Texture = texture;
}

void m4w::Mesh::Render (Camera& camera) {
    Shader& shader = *camera.GetShader();
    m_VAO->Bind();

    if ( m_Texture )
        m_Texture->Use(shader, 1);

    glm::mat4 mvp = camera.m_VP * m_ModelMatrix;
    shader.SetUniformMat4("u_MVP", mvp);
    shader.SetUniformMat4("u_Model", m_ModelMatrix);

    if ( m_VAO->m_IB->m_ID )
        glDrawElements(GL_TRIANGLES, m_VAO->m_IB->m_IndexCount, m_VAO->m_IB->m_DataType, 0);
    else
        glDrawArrays(m_VAO->m_IB->m_DrawMode, 0, m_VAO->m_IB->m_IndexCount);
//    std::cout << "Rendering " << m_VAO->m_IB->GetIndexCount() << " indices of Type " << m_VAO->m_IB->m_DataType << "\n";
    if ( m_Texture )
        m_Texture->Unbind();
}
