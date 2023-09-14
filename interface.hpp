#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <chrono>
#include "fileManager.hpp"
#include "algorithms.hpp"

Algorithms algorithms;
FileManager fm;

class Interface
{
public:
    Interface() {}
    ~Interface() {}

    void showTitle()
    {
        clearConsole();
        std::cout << "|-------------------------------------------|" << std::endl
                  << "|                ALGORITMOS                 |" << std::endl
                  << "|-------------------------------------------|" << std::endl;
    }

    void runAlgorithm(std::vector<int> &arr, int algorithm, int inputStyle, int inputSize)
    {
        auto timeStart = std::chrono::high_resolution_clock::now();
        auto timeEnd = std::chrono::high_resolution_clock::now();
        auto totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);

        switch (algorithm)
        {
        case 1: // Insertion sort
            timeStart = std::chrono::high_resolution_clock::now();
            algorithms.insertionSort(arr);
            timeEnd = std::chrono::high_resolution_clock::now();
            totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);
            saveInfo(arr, algorithm, inputStyle, inputSize, totalDuration);
            pauseConsole();
            break;
        case 2:
            break;
        default:
            std::cout << "Opcao invalida." << std::endl;
            break;
        }
    }

    void clearConsole()
    {
#if defined(_WIN32) || defined(_WIN64)
        // Windows operating system
        system("cls");
#else
        // Assuming a Unix-like operating system (Linux, macOS, etc.)
        system("clear");
#endif
    }

    void pauseConsole()
    {
#if defined(_WIN32) || defined(_WIN64)
        // Windows operating system
        system("pause");
#else
        // Assuming a Unix-like operating system (Linux, macOS, etc.)
        system("read -p 'Press Enter to continue...' key");
#endif
    }

    int chooseAlgorithm()
    {
        int algorithmChoice;
        std::cout << std::endl
                  << "Escolha o algoritmo:" << std::endl
                  << "1 - Insertion sort" << std::endl
                  << "2 - Bubble sort" << std::endl
                  << "3 - Selection sort" << std::endl
                  << "0 - Encerrar" << std::endl;
        std::cin >> algorithmChoice;
        clearConsole();
        return algorithmChoice;
    }

    int chooseInputStyle()
    {
        int inputChoice;
        std::cout << "Escolha o tipo de entrada:" << std::endl
                  << "1 - Aleatoria" << std::endl
                  << "2 - Crescente" << std::endl
                  << "3 - Decrescente" << std::endl;
        std::cin >> inputChoice;
        clearConsole();
        return inputChoice;
    }

    int chooseInputSize()
    {
        int sizeChoice;
        std::cout << "Especifique o tamanho da entrada (10, 100, 1000, 10000, 100000, 1000000, ...):" << std::endl;
        std::cin >> sizeChoice;
        clearConsole();
        return sizeChoice;
    }
    void saveInfo(const std::vector<int> &arr, int algorithm, int inputStyle, int inputSize, std::chrono::milliseconds totalDuration)
    {
        fm.saveFile(arr, algorithm, inputStyle, inputSize);
        fm.saveTime(algorithm, inputStyle, inputSize, totalDuration);
    }
};

#endif
