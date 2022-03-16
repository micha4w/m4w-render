#pragma once

#include <GL/glew.h>

#include "GraphicBuffer.h"

namespace m4w {
    
    class DepthBuffer : private GraphicBuffer {
    private:
        friend class FrameBuffer;

        unsigned short m_Slot;
    public:
        DepthBuffer (unsigned int width, unsigned int height);
        ~DepthBuffer ();

        void Bind (unsigned short slot = 0);
        void Unbind ();
    };

}