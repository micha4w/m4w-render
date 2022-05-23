#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace m4w {
    class Angle {
    private:
        float m_Radians, m_Degrees;

    public:
        Angle ();

        static Angle Radians(float value);
        static Angle Degrees(float value);

        float GetDegrees() const;
        float GetRadians() const;

        float Sin() const;
        float Cos() const;
        float Tan() const;

        void ClampRadians(float lower, float upper);
        void ClampDegrees(float lower, float upper);
    
        Angle operator+ (const Angle& other) const;
        Angle operator* (const float& factor) const;
        bool operator== (const Angle& other) const;
        bool operator!= (const Angle& other) const;
    };
};