#pragma once
#include <fstream>
#include <vector>

template<typename T>
class FileHandler {
public:
    static bool saveToFile(const std::string& filePath, const T* data, int size) {
        std::ofstream file(filePath);
        if (!file.is_open()) return false;
        for (int i = 0; i < size; ++i)
            file << data[i] << "\n";
        return true;
    }

    static bool loadFromFile(const std::string& filePath, std::vector<T>& data) {
        std::ifstream file(filePath);
        if (!file.is_open()) return false;
        T value;
        while (file >> value)
            data.push_back(value);
        return true;
    }
};
