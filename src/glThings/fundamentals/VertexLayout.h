#pragma once

#include <vector>

#include "Pointer.h"

class VertexLayout {
private:
    friend class VertexArray;

    struct VertexLayoutElement {
        unsigned short Position;
        unsigned short Count;
        unsigned int Type;
        bool Normalized;
    };

    std::vector<VertexLayoutElement> m_Elements;

    unsigned long m_Size = 0;

public:
    static unsigned int glSizeof(unsigned int type);
    static m4w::Pointer<VertexLayout> Default();

    unsigned int Size() const;
    void AddElement(unsigned short position, unsigned short count, unsigned int type, bool normalized = false);
    void Use(class VertexArray& vao);

    struct DefaultVertex {
        float Pos[3];
        float Normal[3];
        float Color[4];
        float TexCoord[2];
    };
};