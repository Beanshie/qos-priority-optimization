#pragma once
#include <chrono>

class Timer
{
private:
    // Prywatne zmienne trzymające moment włączenia i wyłączenia stopera
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time;

public:
    // Odpalenie stopera
    void start()
    {
        start_time = std::chrono::high_resolution_clock::now();
    }

    // Zatrzymanie stopera
    void stop()
    {
        end_time = std::chrono::high_resolution_clock::now();
    }

    // Zwraca wynik w mikrosekundach
    long long elapsedMicroseconds() const
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
};