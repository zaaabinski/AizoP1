#include <iostream>
#include <vector>
#include <string>
#include "DataGenerator.h"
#include "FileHandler.h"
#include "Sorter.h"
#include "Timer.h"

template<typename T>
void handleTestMode(int size, const std::string& outputFilePath) {
    std::vector<T> data(size);
    DataGenerator<T> generator;
    generator.generateData(size, data.data());

    if (FileHandler<T>::saveToFile(outputFilePath, data.data(), size)) {
        std::cout << "Data saved to " << outputFilePath << std::endl;
    } else {
        std::cerr << "Failed to save data." << std::endl;
    }

    // Sortowanie danych
    std::vector<T> sortedData = Sorter<T>::bubbleSort(data);

    // Zapis posortowanych danych do nowego pliku
    std::string sortedFilePath = "sorted_" + outputFilePath;
    if (FileHandler<T>::saveToFile(sortedFilePath, sortedData.data(), sortedData.size())) {
        std::cout << "Sorted data saved to " << sortedFilePath << std::endl;
    } else {
        std::cerr << "Failed to save sorted data." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    Timer timer;
    if (argc < 4) {
        std::cerr << "Usage: <mode> <type> <file or size> [outputFile]" << std::endl;
        return 1;
    }

    std::string mode = argv[1];
    std::string type = argv[2];

    if (mode == "test") {
        int size = std::stoi(argv[3]);
        std::string outputFilePath = argv[4];
        
         timer.start(); // Start timer
        if (type == "int") {
            handleTestMode<int>(size, outputFilePath);
        } else if (type == "float") {
            handleTestMode<float>(size, outputFilePath);
        } else if (type == "double") {
            handleTestMode<double>(size, outputFilePath);
        } else if (type == "char") {
            handleTestMode<char>(size, outputFilePath);
        } else {
            std::cerr << "Unsupported type." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Unknown mode. Use 'test' or 'file'." << std::endl;
        return 1;
    }
    timer.stop(); // Stop timer

    std::cout << "Elapsed time: " << timer.result() << " ms" << std::endl;
    return 0;
}
