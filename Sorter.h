#pragma once
#include <vector>
#include <algorithm>

template<typename T>
class Sorter {
public:
    // Funkcja sortująca dane za pomocą Bubble Sort
    static std::vector<T> bubbleSort(const std::vector<T>& data) {
        std::vector<T> sortedData = data;  // Tworzymy kopię danych, by nie zmieniać oryginału
        int n = sortedData.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - 1 - i; ++j) {
                if (sortedData[j] > sortedData[j + 1]) {
                    std::swap(sortedData[j], sortedData[j + 1]);
                }
            }
        }
        return sortedData;  // Zwracamy posortowane dane
    }
};
