#pragma once

#include <chrono>

#define M4W_AVERAGE_FPS_TIME 20

namespace m4w {

    class Timer {
    private:
        float m_FPS;
        int64_t m_NSPF;
        unsigned int m_DeltaNs;
        bool m_ShouldSleep;

        // Averaging
        float m_LastFPS[M4W_AVERAGE_FPS_TIME];
        unsigned int m_LastFPSPos;


        std::chrono::system_clock::time_point m_LastTime;
    public:
        Timer (float fps, bool shouldSleep);

        void Update ();

        float GetAverageFPS ();
        float GetDeltaS ();
        unsigned int GetDeltaNs ();
        unsigned int GetDeltaUs ();
    };

}