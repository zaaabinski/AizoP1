#include "Timer.h"

Timer::Timer() : running(false) {}

void Timer::reset() {
    startTime = std::chrono::steady_clock::now();
    endTime = startTime;
    running = false;
}

int Timer::start() {
    if (!running) {
        startTime = std::chrono::steady_clock::now();
        running = true;
    }
    return 0;
}

int Timer::stop() {
    if (running) {
        endTime = std::chrono::steady_clock::now();
        running = false;
    }
    return 0;
}

int Timer::result() {
    if (running) {
        endTime = std::chrono::steady_clock::now();  // Pobranie czasu, jeśli timer jest uruchomiony
    }
    // Przekształcenie różnicy na milisekundy
    std::chrono::duration<int, std::milli> duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    return duration.count();  // Zwrócenie czasu w milisekundach
}

long long Timer::elapsed() const {
    if (running) {
        // Obliczenie upłynionego czasu, jeśli timer jest uruchomiony
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startTime).count();
    }
    // Jeśli timer nie jest uruchomiony, zwróć różnicę między końcowym a początkowym czasem
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}
