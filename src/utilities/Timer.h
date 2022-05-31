#pragma once

#include <chrono>

namespace m4w {

    class Timer {
    private:
        float m_FPS;
        int64_t m_NSPF;
        unsigned int m_DeltaNs;
        bool m_ShouldSleep;

        std::chrono::system_clock::time_point m_LastTime;
    public:
        Timer (float fps, bool shouldSleep);

        void Update ();
        float GetDeltaS ();
        unsigned int GetDeltaNs ();
        unsigned int GetDeltaUs ();
    };

}