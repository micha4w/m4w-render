#pragma once

#include <cstring>
#include <vector>

#include "Light.h"

namespace m4w {

    class LightHandler {
    private:
        friend class Light;

        char* m_UsedPos;
        const int m_Size;
        const int m_Dimensions;

        FrameBuffer m_Buffer;

    public:
        const Pointer<Shader> m_LightShader;
        
        LightHandler (int dimensions, int eachSize)
            : m_Size(eachSize), m_Buffer(eachSize * dimensions, eachSize * dimensions), m_Dimensions(dimensions),
              m_LightShader(new Shader("Light"))
        {
            m_UsedPos = new char[(dimensions * dimensions + 7) / 8]{0};
            m_Buffer.AddDepthBuffer();
        }

        ~LightHandler () {
            delete[] m_UsedPos;
        }

        int GetFreePos () {
            for ( int i = 0 ; i < (m_Dimensions * m_Dimensions + 7) / 8 ; i++ )
                for ( int j = 0 ; j < 8 ; j++ )
                    if ( !(m_UsedPos[i] & (1 << j)) ) {
                        m_UsedPos[i] |= 1 << j;
                        return i*8 + j;
                    }

            return -1;
        }

        void Delete (int pos) {
            m_UsedPos[pos / 8] &= ~(1 << pos%8);
        }

        int GetDimensions () { return m_Dimensions; }
        m4w::Pointer<FrameBuffer> GetFrameBuffer () { return Pointer<FrameBuffer>::Soft(&m_Buffer); }
    };
}
