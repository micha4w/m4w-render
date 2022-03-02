#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexLayout.h"

#include "Base64.h"
#include "HeapArray.h"
#include "JSON.h"
#include "Pointer.h"

namespace m4w {
    struct Vertex {
        float Position[3];
        float Normal[3];
        float TexCoord[2];
        float Color[4];
    };

    enum Types {
        SCALAR = 1,
        VEC2 = 2, VEC3 = 3, VEC4 = 4,
        MAT2 = 4, MAT3 = 9, MAT4 = 16
    };

    struct Accessor {
        int ComponentType;
        unsigned int Count;
        Types Type;
        unsigned int BufferView, ByteOffset;
        bool Normalized;
        float Min[3], Max[3];
    };

    struct BufferView {
        unsigned int Buffer;
        unsigned int Length;
        unsigned int Offset;
    };

    Types TypesFromString(const char* name);
    m4w::Pointer<IndexBuffer> CreateIndexBuffer(const Accessor& indicesAccesor, const BufferView& indicesView, const HeapArray<BinaryData>& buffers);
    m4w::Pointer<VertexBuffer> CreateVertexBuffer(unsigned int vertexSize, std::vector<Accessor*> accessors, const HeapArray<BinaryData>& buffers, const HeapArray<BufferView>& bufferViews, unsigned int vertexCount);
    HeapArray<Accessor> GetAccessors(JSONObject* gltf);
    HeapArray<BufferView> GetBufferViews(JSONObject* gltf);
    HeapArray<BinaryData> GetBuffers(JSONObject* gltf);
}
