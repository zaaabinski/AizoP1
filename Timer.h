#pragma once
#include <chrono>

class Timer
{
public:
    Timer(); // Inicjalizacja i przygotowanie do uruchomienia.
    void reset(); // Resetowanie timera.
    int start(); // Uruchomienie timera.
    int stop(); // Zatrzymanie timera.
    int result(); // Zwrócenie czasu [ms].

private:
    std::chrono::steady_clock::time_point startTime;  // Czas początkowy.
    std::chrono::steady_clock::time_point endTime;    // Czas końcowy.
    bool running; // Flaga sprawdzająca, czy timer jest uruchomiony.
    
    long long elapsed() const; // Funkcja prywatna
};
