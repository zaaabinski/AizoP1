#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "DataGenerator.h"
#include "FileHandler.h"
#include "Sorter.h"
#include "Timer.h"

// Funkcja zapisująca dane do pliku
void logToFile(const std::string& outputFilePath, const std::string& sortType, const std::string& dataType, int size, double time, const std::string& dataOrder) {
    std::ofstream outFile(outputFilePath, std::ios::app); // Otwórz plik w trybie dopisywania
    if (outFile.is_open()) {
        outFile << sortType << ";" << dataType << ";" << size << ";" << time << "ms;" << dataOrder << std::endl;
        outFile.close();
    } else {
        std::cerr << "Nie udało się otworzyć pliku do zapisu." << std::endl;
    }
}


template<typename T>
std::vector<T> prepareData(int size, const std::string& dataOrder = "random") {
    std::vector<T> data(size); // Tworzymy pusty wektor o odpowiednim rozmiarze
    DataGenerator<T> generator;
    generator.generateData(size, data.data());


    if (dataOrder == "ascending") {
        std::sort(data.begin(), data.end());
    } 
    else if (dataOrder == "descending") {
        std::sort(data.begin(), data.end(), std::greater<T>());
    }
    else if (dataOrder == "partial33") {
        int partialSize = size * 0.33;
        std::sort(data.begin(), data.begin() + partialSize);
    }
    else if (dataOrder == "partial66") {
        int partialSize = size * 0.66;
        std::sort(data.begin(), data.begin() + partialSize);
    }
    // jeśli "random" lub nieznane -> nic nie zmieniamy
    return data;
}

// Wspólna logika sortowania i zapisywania wyników
template<typename T>
void handleSortAndSave(const std::vector<T>& data, const std::string& algorithm, const std::string& type, const std::string& outputFilePath,const std::string& dataOrder) {
    Timer timer;
    std::vector<T> sortedData;
    std::string sortName;

    timer.start();
    // Wybór algorytmu sortowania
    if (algorithm == "Quick") {
        sortedData = Sorter<T>::quickSort(data);
        sortName = "QuickSort";
    } else if (algorithm == "Insert") {
        sortedData = Sorter<T>::insertionSort(data);
        sortName = "InsertionSort";
    } else if (algorithm == "3") {
        sortedData = Sorter<T>::binaryInsertionSort(data);
        sortName = "BinaryInsert";
    } else if (algorithm == "Heap") {
        sortedData = Sorter<T>::heapSort(data);
        sortName = "HeapSort";
    } else {
        std::cerr << "Niepoprawny numer algorytmu!" << std::endl;
        return;
    }
    timer.stop(); // Zatrzymanie timera

    // Zapis posortowanych danych do pliku
    if (FileHandler<T>::saveToFile(outputFilePath, sortedData.data(), sortedData.size())) {
        std::cout << "Posortowane dane zapisane do " << outputFilePath << std::endl;
    } else {
        std::cerr << "Nie udało się zapisać posortowanych danych." << std::endl;
    }

    // Logowanie wyniku do pliku
    logToFile("time_tests.txt", sortName, type, data.size(), timer.result(),dataOrder);

}

template<typename T>
void handleFileMode(const std::string& inputFile, const std::string& outputFile, const std::string& algorithm) {
    std::vector<T> data;
    if (!FileHandler<T>::loadFromFile(inputFile, data)) {
        std::cerr << "Nie udało się wczytać danych z pliku: " << inputFile << std::endl;
        return;
    }
    handleSortAndSave(data, algorithm, typeid(T).name(), outputFile,"FileType");
}

template<typename T>
void handleTestMode(int size, const std::string& outputFilePath, const std::string& algorithm, const std::string& dataOrder = "random") {
    std::vector<T> data = prepareData<T>(size, dataOrder);
    handleSortAndSave(data, algorithm, typeid(T).name(), outputFilePath, dataOrder);
}

int main(int argc, char* argv[]) {
    if (argc < 6) {
        std::cerr << "Usage:\n"
                  << "--file <algorithm> <type> <inputFile> <outputFile>\n"
                  << "--test <algorithm> <type> <size> <outputFile> [dataOrder]\n";
        return 1;
    }

    std::string mode = argv[1];
    std::string algorithm = argv[2];
    std::string type = argv[3];

    if (mode == "--file") {
        std::string inputFile = argv[4];
        std::string outputFile = argv[5];

        if (type == "int") {
            handleFileMode<int>(inputFile, outputFile, algorithm);
        } else if (type == "float") {
            handleFileMode<float>(inputFile, outputFile, algorithm);
        } else if (type == "double") {
            handleFileMode<double>(inputFile, outputFile, algorithm);
        } else if (type == "char") {
            handleFileMode<char>(inputFile, outputFile, algorithm);
        } else {
            std::cerr << "Unsupported type: " << type << std::endl;
            return 1;
        }
    } 
    else if (mode == "--test") {
        int size = std::stoi(argv[4]);
        std::string outputFilePath = argv[5];
        std::string dataOrder = "random";
        if (argc > 6) {
            dataOrder = argv[6];
        }

        if (type == "int") {
            handleTestMode<int>(size, outputFilePath, algorithm, dataOrder);
        } else if (type == "float") {
            handleTestMode<float>(size, outputFilePath, algorithm, dataOrder);
        } else if (type == "double") {
            handleTestMode<double>(size, outputFilePath, algorithm, dataOrder);
        } else if (type == "char") {
            handleTestMode<char>(size, outputFilePath, algorithm, dataOrder);
        } else {
            std::cerr << "Unsupported type: " << type << std::endl;
            return 1;
        }
    } 
    else {
        std::cerr << "Unknown mode: " << mode << ". Use '--file' or '--test'." << std::endl;
        return 1;
    }

    return 0;
}
