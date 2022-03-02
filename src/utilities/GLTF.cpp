#include "GLTF.h"

#include <iostream>
#include <string.h>

#include "JSON.h"
#include "HeapArray.h"
#include "Base64.h"
#include "GLTF.h"

namespace m4w {
    Types TypesFromString(const char* name) {
        if ( strcmp( name, "VEC2") == 0 ) return VEC2;
        if ( strcmp( name, "VEC3") == 0 ) return VEC3;
        if ( strcmp( name, "VEC4") == 0 ) return VEC4;
        if ( strcmp( name, "MAT2") == 0 ) return MAT2;
        if ( strcmp( name, "MAT3") == 0 ) return MAT3;
        if ( strcmp( name, "MAT4") == 0 ) return MAT4;
        return SCALAR;
    }

    m4w::Pointer<IndexBuffer> CreateIndexBuffer(const Accessor& indicesAccesor, const BufferView& indicesView, const HeapArray<BinaryData>& buffers) {
        if ( indicesView.Length + indicesView.Offset > buffers[indicesView.Buffer].Size ) {
            std::cout << "[ERROR] Buffer " << indicesView.Buffer << " too small for BufferView " << indicesAccesor.BufferView << "!\n";
            return nullptr;
        }

        m4w::Pointer<IndexBuffer> ib( new IndexBuffer(indicesView.Length, &buffers[indicesView.Buffer].DataPointer[indicesView.Offset], indicesAccesor.ComponentType) );

        return ib;
    }


    m4w::Pointer<VertexBuffer> CreateVertexBuffer(unsigned int vertexSize, std::vector<Accessor*> accessors, const HeapArray<BinaryData>& buffers, const HeapArray<BufferView>& bufferViews, unsigned int vertexCount) {

        char* vertexData = new char[vertexSize * vertexCount];

        unsigned int offset = 0;
        for ( Accessor* accessor : accessors ) {
            const BufferView& bufferView = bufferViews[accessor->BufferView];
            const BinaryData& buffer = buffers[bufferView.Buffer];

            char* data = &buffer.DataPointer[bufferView.Offset];
            unsigned int size = accessor->Type * VertexLayout::glSizeof(accessor->ComponentType);
            for ( int i = 0 ; i < vertexCount ; i++ ) {
                std::copy(&data[ i * size ], &data[ (i + 1) * size ], &vertexData[ i * vertexSize + offset ]);
            }

            offset += size;
        }

        m4w::Pointer<VertexBuffer> vb( new VertexBuffer(vertexSize * vertexCount, vertexData) );

        delete[] vertexData;
        return vb;
    }

    HeapArray<Accessor> GetAccessors(JSONObject* gltf) {

        JSONArray* jsonAccessors = gltf->GetArray("accessors");
        HeapArray<Accessor> accessors( jsonAccessors->m_Values.size() );

        for ( int i = 0 ; i < accessors.GetSize() ; i++ ) {
            JSONObject* jsonAccessor = (JSONObject*) jsonAccessors->GetObject(i);

            accessors[i] = Accessor();
            accessors[i].BufferView = *jsonAccessor->GetNumber("bufferView");
            if ( jsonAccessor->Contains("byteOffset") )
                accessors[i].ByteOffset = *jsonAccessor->GetNumber("byteOffset");
    //        else accessors[i].ByteOffset = 0;

            if ( jsonAccessor->Contains("normalized") ) 
                accessors[i].Normalized = *jsonAccessor->GetBoolean("normalized");
    //        else accessors[i].Normalized = false;
            
            accessors[i].ComponentType = *jsonAccessor->GetNumber("componentType");
            accessors[i].Count = *jsonAccessor->GetNumber("count");

            if ( jsonAccessor->Contains("max") ) {
                JSONArray* max = jsonAccessor->GetArray("max");
                for ( int j = 0 ; j < 3 ; j++ ) {
                    accessors[i].Max[j] = *max->GetNumber(j);
                }
            }
            if ( jsonAccessor->Contains("max") ) {
                JSONArray* min = jsonAccessor->GetArray("min");
                for ( int j = 0 ; j < 3 ; j++ ) {
                    accessors[i].Min[j] = *min->GetNumber(j);
                }
            }

            accessors[i].Type = TypesFromString(jsonAccessor->GetString("type")->m_Value.c_str());
        }

        return accessors;
    }

    HeapArray<BufferView> GetBufferViews(JSONObject* gltf) {
        
        JSONArray* jsonBufferViews = gltf->GetArray("bufferViews");
        HeapArray<BufferView> bufferViews( jsonBufferViews->m_Values.size() );

        for ( int i = 0 ; i < bufferViews.GetSize() ; i++ ) {
            JSONObject* jsonBufferView = (JSONObject*) jsonBufferViews->GetObject(i);

            bufferViews[i] = BufferView();

            bufferViews[i].Buffer = *jsonBufferView->GetNumber("buffer");
            bufferViews[i].Length = *jsonBufferView->GetNumber("byteLength");
            bufferViews[i].Offset = *jsonBufferView->GetNumber("byteOffset");
        }

        return bufferViews;
    }

    HeapArray<BinaryData> GetBuffers(JSONObject* gltf) {
        
        JSONArray* jsonBuffers = gltf->GetArray("buffers");
        HeapArray<BinaryData> buffers( jsonBuffers->m_Values.size() );

        for ( unsigned int i = 0 ; i < buffers.GetSize() ; i++ ) {
            JSONObject* jsonBuffer = (JSONObject*) jsonBuffers->GetObject(i);

            std::string data = *jsonBuffer->GetString("uri");
            unsigned int j = 0;
            for ( ; j < data.size() ; j++ ) {
                if ( data[j] == ',' ) break;
            }

            buffers[i] = DecodeB64(&data.c_str()[j+1]);
        }

        return buffers;
    }
}
