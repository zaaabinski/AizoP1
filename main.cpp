#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "DataGenerator.h"
#include "FileHandler.h"
#include "Sorter.h"
#include "Timer.h"

// Funkcja zapisująca dane do pliku
void logToFile(const std::string& outputFilePath, const std::string& sortType, const std::string& dataType, int size, double time) {
    std::ofstream outFile(outputFilePath, std::ios::app); // Otwórz plik w trybie dopisywania
    if (outFile.is_open()) {
        outFile << sortType << ";" << dataType << ";" << size << ";" << time << "ms" << std::endl;
        outFile.close();
    } else {
        std::cerr << "Nie udało się otworzyć pliku do zapisu." << std::endl;
    }
}

// Wspólna logika sortowania i zapisywania wyników
template<typename T>
void handleSortAndSave(const std::vector<T>& data, const std::string& algorithm, const std::string& type, const std::string& outputFilePath) {
    Timer timer;
    std::vector<T> sortedData;
    std::string sortName;
    timer.start();
    // Wybór algorytmu sortowania
    if (algorithm == "1") {
        sortedData = Sorter<T>::quickSort(data);
        sortName = "QuickSort";
    } else if (algorithm == "2") {
        sortedData = Sorter<T>::insertionSort(data);
        sortName = "InsertionSort";
    } else if (algorithm == "3") {
        sortedData = Sorter<T>::binaryInsertionSort(data);
        sortName = "BinaryInsertionSort";
    } else if (algorithm == "4") {
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
    logToFile("time_tests.txt", sortName, type, data.size(), timer.result());
}

template<typename T>
void handleTestMode(const std::string& algorithm, const std::string& type, int size, const std::string& outputFilePath) {
    Timer timer;
    std::vector<T> data(size);
    DataGenerator<T> generator;
    generator.generateData(size, data.data());

    if (FileHandler<T>::saveToFile(outputFilePath, data.data(), size)) {
        std::cout << "Dane zapisane do " << outputFilePath << std::endl;
    } else {
        std::cerr << "Nie udało się zapisać danych." << std::endl;
    }

    // Sortowanie i zapisywanie
    handleSortAndSave(data, algorithm, type, "sorted_" + outputFilePath);
}

template<typename T>
void handleFileMode(const std::string& algorithm, const std::string& type, const std::string& inputFile, const std::string& outputFile) {
    Timer timer;
    std::vector<T> data;

    // Wczytanie danych z pliku
    if (FileHandler<T>::loadFromFile(inputFile, data)) {
        std::cout << "Dane wczytane z pliku: " << inputFile << std::endl;
    } else {
        std::cerr << "Nie udało się wczytać danych z pliku." << std::endl;
        return;
    }

    // Sortowanie i zapisywanie
    handleSortAndSave(data, algorithm, type, outputFile);
}

int main(int argc, char* argv[]) {
    if (argc < 6) {
        std::cerr << "Usage: <mode> <algorithm> <type> <size> <outputFile>" << std::endl;
        return 1;
    }

    std::string mode = argv[1];

    if (mode == "--file") {
        std::string algorithm = argv[2];
        std::string type = argv[3];
        std::string inputFile = argv[4];
        std::string outputFile = (argc == 6) ? argv[5] : "sorted_output.txt";

        if (type == "int") {
            handleFileMode<int>(algorithm, type, inputFile, outputFile);
        } else if (type == "float") {
            handleFileMode<float>(algorithm, type, inputFile, outputFile);
        } else if (type == "double") {
            handleFileMode<double>(algorithm, type, inputFile, outputFile);
        } else if (type == "char") {
            handleFileMode<char>(algorithm, type, inputFile, outputFile);
        } else {
            std::cerr << "Unsupported type." << std::endl;
            return 1;
        }
    } else if (mode == "--test") {
        std::string algorithm = argv[2];
        std::string type = argv[3];
        int size = std::stoi(argv[4]);
        std::string outputFilePath = argv[5];

        if (type == "int") {
            handleTestMode<int>(algorithm, type, size, outputFilePath);
        } else if (type == "float") {
            handleTestMode<float>(algorithm, type, size, outputFilePath);
        } else if (type == "double") {
            handleTestMode<double>(algorithm, type, size, outputFilePath);
        } else if (type == "char") {
            handleTestMode<char>(algorithm, type, size, outputFilePath);
        } else {
            std::cerr << "Unsupported type." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Nieznany tryb. Użyj '--file' lub '--test'." << std::endl;
        return 1;
    }

    return 0;
}
