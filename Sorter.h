#pragma once
#include <vector>
#include <algorithm>

template<typename T>
class Sorter {
public:
    static std::vector<T> insertionSort(const std::vector<T>& data) {
        std::vector<T> sorted = data;
        for (size_t i = 1; i < sorted.size(); ++i) {
            T key = sorted[i];
            int j = i - 1;
            while (j >= 0 && sorted[j] > key) {
                sorted[j + 1] = sorted[j];
                j--;
            }
            sorted[j + 1] = key;
        }
        return sorted;
    }

    static std::vector<T> binaryInsertionSort(const std::vector<T>& data) {
        std::vector<T> sorted = data;
        for (size_t i = 1; i < sorted.size(); ++i) {
            T key = sorted[i];
            int left = 0;
            int right = i - 1;
            // Binary search to find position
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (sorted[mid] > key)
                    right = mid - 1;
                else
                    left = mid + 1;
            }
            for (int j = i - 1; j >= left; --j) {
                sorted[j + 1] = sorted[j];
            }
            sorted[left] = key;
        }
        return sorted;
    }

    static std::vector<T> heapSort(const std::vector<T>& data) {
        std::vector<T> sorted = data;

        auto heapify = [&](std::vector<T>& arr, int n, int i, auto&& heapify_ref) -> void {
            int largest = i;
            int l = 2 * i + 1;
            int r = 2 * i + 2;

            if (l < n && arr[l] > arr[largest])
                largest = l;
            if (r < n && arr[r] > arr[largest])
                largest = r;
            if (largest != i) {
                std::swap(arr[i], arr[largest]);
                heapify_ref(arr, n, largest, heapify_ref);
            }
        };

        int n = sorted.size();

        // Build heap
        for (int i = n / 2 - 1; i >= 0; --i)
            heapify(sorted, n, i, heapify);

        // Extract elements
        for (int i = n - 1; i >= 0; --i) {
            std::swap(sorted[0], sorted[i]);
            heapify(sorted, i, 0, heapify);
        }

        return sorted;
    }

    static std::vector<T> quickSort(const std::vector<T>& data) {
        std::vector<T> sorted = data;

        auto quickSortHelper = [&](auto&& self, int low, int high) -> void {
            if (low < high) {
                int pivot = sorted[high];
                int i = low - 1;

                for (int j = low; j < high; ++j) {
                    if (sorted[j] < pivot) {
                        i++;
                        std::swap(sorted[i], sorted[j]);
                    }
                }
                std::swap(sorted[i + 1], sorted[high]);
                int pi = i + 1;

                self(self, low, pi - 1);
                self(self, pi + 1, high);
            }
        };

        quickSortHelper(quickSortHelper, 0, sorted.size() - 1);
        return sorted;
    }
};
