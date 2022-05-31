#pragma once

#include <GL/glew.h>

#include "Shader.h"

#include "Pointer.h"

namespace m4w {

    enum TextureFormat {
        RGBA,
        DEPTH
    };

    class Texture {
    private:
        friend class FrameBuffer;

        unsigned int m_ID;

        unsigned int m_Width, m_Height;
        unsigned short m_Slot;
    public:
        Texture (unsigned int width, unsigned int height, TextureFormat format, unsigned char* data = nullptr);
        Texture (const char* path);
        ~Texture ();

        void Bind (unsigned short slot = 0);
        void Unbind ();

        void Use (Shader& shader, unsigned short slot, const char* name = "u_Texture");
        static void UseEmpty (Shader& shader, const char* name = "u_Texture"); 

        void ReadImage ();
        void FromPNG ();
    };

}