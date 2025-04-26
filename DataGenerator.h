#pragma once
#include <cstdlib>
#include <ctime>
#include <climits>   // Dla INT_MIN i INT_MAX
#include <cfloat>    // Dla FLT_MIN, FLT_MAX, DBL_MIN, DBL_MAX
#include <limits>    // Dla std::numeric_limits

template<typename T>
class DataGenerator {
public:
    void generateData(int size, T* data);
};

// Specjalizacje

// Dla typu int
template<>
inline void DataGenerator<int>::generateData(int size, int* data) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < size; ++i) {
        // Generowanie liczb w pełnym zakresie int, zarówno dodatnich, jak i ujemnych
        // Zamiast używać INT_MAX + 1, będziemy generować liczby w zakresie od INT_MIN do INT_MAX
        data[i] = std::rand(); // Generujemy liczbę losową z zakresu 0 do RAND_MAX

        // Przekształcamy losową liczbę do zakresu [-INT_MAX, INT_MAX]
        if (data[i] > (RAND_MAX / 2)) {
            data[i] = data[i] % (INT_MAX);   // Liczba w zakresie dodatnim
        } else {
            data[i] = -(data[i] % (INT_MAX)); // Liczba w zakresie ujemnym
        }
    }
}

// Dla typu float
template<>
inline void DataGenerator<float>::generateData(int size, float* data) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < size; ++i) {
        data[i] = static_cast<float>(std::rand()) / RAND_MAX * (std::numeric_limits<float>::max() - std::numeric_limits<float>::min()) + std::numeric_limits<float>::min();
    }
}

// Dla typu double
template<>
inline void DataGenerator<double>::generateData(int size, double* data) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < size; ++i) {
        data[i] = static_cast<double>(std::rand()) / RAND_MAX * (std::numeric_limits<double>::max() - std::numeric_limits<double>::min()) + std::numeric_limits<double>::min();
    }
}

// Dla typu char
template<>
inline void DataGenerator<char>::generateData(int size, char* data) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < size; ++i) {
        data[i] = static_cast<char>(std::rand() % (CHAR_MAX - CHAR_MIN + 1) + CHAR_MIN);  // Generowanie w pełnym zakresie char
    }
}
