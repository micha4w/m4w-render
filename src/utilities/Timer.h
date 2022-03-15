#pragma once

#include <chrono>

class Timer {
private:
    float m_FPS;
    int64_t m_NSPF;
    unsigned int m_DeltaNs;

    std::chrono::system_clock::time_point m_LastTime;
public:
    Timer(float fps);
    ~Timer();

    void Wait();
    float GetDeltaS();
    unsigned int GetDeltaNs();
    unsigned int GetDeltaUs();
};