#include "Timer.h"

#include <thread>

using namespace std::chrono;

Timer::Timer(float fps)
    : m_FPS(fps), m_NSPF(1'000'000'000/fps), m_LastTime(system_clock::now())
{ }

Timer::~Timer() {
    
}

void Timer::Wait() {
    system_clock::time_point startTime = system_clock::now();

    int64_t sleepTime = m_NSPF - (startTime - m_LastTime).count();
//    std::cout << deltaTime * 0.000'001 << " " << sleepTime * 0.000'001 << "\n";
    if ( sleepTime > 0 ) {
        std::this_thread::sleep_for(nanoseconds(sleepTime));
    }

    system_clock::time_point tempTime = system_clock::now();
//    std::cout << (tempTime - m_LastTime).count() * 0.000'001 << "\n";


    system_clock::time_point endTime = system_clock::now();
    m_DeltaNs = (endTime - m_LastTime).count();
    m_LastTime = endTime;
}

float Timer::GetDeltaS() { return m_DeltaNs / 1000000000.f; }
unsigned int Timer::GetDeltaUs() { return m_DeltaNs / 1000; }
unsigned int Timer::GetDeltaNs() { return m_DeltaNs; }
