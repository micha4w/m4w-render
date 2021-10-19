#pragma once

#include <vector>

class VertexLayout {
private:
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

    unsigned int Size() const;
    void OverrideSize(unsigned int size);
    void AddElement(unsigned short position, unsigned short count, unsigned int type, bool normalized = false);
    void Use(class VertexArray& vao);
};