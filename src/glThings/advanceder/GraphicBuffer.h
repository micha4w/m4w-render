#pragma once

class GraphicBuffer {
public:
    unsigned int m_ID;

    unsigned int m_Width, m_Height;

    GraphicBuffer (unsigned int width, unsigned int height);

    virtual void Bind () { }
};