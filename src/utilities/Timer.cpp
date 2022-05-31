#include "Timer.h"

#include <thread>
#include <iostream>

m4w::Timer::Timer (float fps, bool shouldSleep)
    : m_FPS(fps), m_NSPF(1'000'000'000/fps), m_LastTime(std::chrono::system_clock::now()), m_ShouldSleep(shouldSleep)
{ }

void m4w::Timer::Update () {
    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();

    int64_t sleepTime = m_NSPF - (startTime - m_LastTime).count();


    if ( m_ShouldSleep && sleepTime > 0 ) {
        std::this_thread::sleep_for(std::chrono::nanoseconds(sleepTime));
    }

    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    m_DeltaNs = (endTime - m_LastTime).count();
    // std::cout << "Passed: " << (startTime - m_LastTime).count() * 0.000'001 << " Slept: " << sleepTime * 0.000'001 << " Total: " << m_DeltaNs * 0.000'001 << "\n";
    
    m_LastTime = endTime;
}

float m4w::Timer::GetDeltaS () { return m_DeltaNs / 1000000000.f; }
unsigned int m4w::Timer::GetDeltaUs () { return m_DeltaNs / 1000; }
unsigned int m4w::Timer::GetDeltaNs () { return m_DeltaNs; }
