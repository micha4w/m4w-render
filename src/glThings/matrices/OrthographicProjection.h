#pragma once

#include "Projection.h"

namespace m4w {

    class OrthographicProjection : public Projection {
    private:
        float m_Width, m_Height;

    public:
        OrthographicProjection(float width, float height, float near, float far);
        ~OrthographicProjection();
    };

}