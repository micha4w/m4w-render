#pragma once

namespace m4w {
    const float m_PI = 3.14159265359;
    
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
        void operator+= (const Angle& other);
        Angle operator- (const Angle& other) const;
        void operator-= (const Angle& other);
        Angle operator* (const float& factor) const;
        void operator*= (const float& factor);
        bool operator== (const Angle& other) const;
        bool operator!= (const Angle& other) const;
        operator bool() const;
    };
};