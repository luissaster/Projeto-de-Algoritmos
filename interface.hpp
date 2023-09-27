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
        std::cout << "|-------------------------------------------|\n"
                  << "|                ALGORITMOS                 |\n"
                  << "|-------------------------------------------|\n";
    }

    void runAlgorithm(std::vector<int> &arr, AlgorithmType algorithm, InputType inputStyle, int inputSize)
    {
        auto timeStart = std::chrono::high_resolution_clock::now();
        auto timeEnd = std::chrono::high_resolution_clock::now();
        auto totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);

        switch (algorithm)
        {
        case Insertion_Sort:
            timeStart = std::chrono::high_resolution_clock::now();
            algorithms.insertionSort(arr);
            break;
        case Bubble_Sort:
            timeStart = std::chrono::high_resolution_clock::now();
            algorithms.bubbleSort(arr);
            break;
        case Selection_Sort:
            timeStart = std::chrono::high_resolution_clock::now();
            algorithms.selectionSort(arr);
            break;
        case Shell_Sort:
            timeStart = std::chrono::high_resolution_clock::now();
            algorithms.shellSort(arr);
            break;
        default:
            std::cout << "Invalid option." << std::endl;
            return;
        }

        timeEnd = std::chrono::high_resolution_clock::now();
        totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);
        saveInfo(arr, algorithm, inputStyle, inputSize, totalDuration);
        // pauseConsole();
    }

    void clearConsole()
    {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
    }

    void pauseConsole()
    {
#ifdef _WIN32
        system("pause");
#else
        system("read -p 'Press Enter to continue...' key");
#endif
    }

    AlgorithmType chooseAlgorithm()
    {
        int algorithmChoice;
        std::cout << std::endl
                  << "Choose an algorithm:" << std::endl
                  << "----------Comparison Algorithms---------" << std::endl
                  << "1 - Insertion sort" << std::endl
                  << "2 - Bubble sort" << std::endl
                  << "3 - Selection sort" << std::endl
                  << "4 - Shell sort" << std::endl
                  << "---------Divide and Conquer Algorithms---------" << std::endl
                  << "5 - Merge sort" << std::endl
                  << "---------Options---------" << std::endl
                  << "99 - Run all combinations" << std::endl
                  << "0 - Quit" << std::endl;
        std::cin >> algorithmChoice;
        clearConsole();
        return (AlgorithmType)algorithmChoice;
    }

    InputType chooseInputStyle()
    {
        int inputChoice;
        std::cout << "Choose the input type:" << std::endl
                  << "1 - Random" << std::endl
                  << "2 - Ascending" << std::endl
                  << "3 - Descending" << std::endl;
        std::cin >> inputChoice;
        clearConsole();
        return (InputType)inputChoice;
    }

    int chooseInputSize()
    {
        int sizeChoice;
        std::cout << "Specify the input size (10, 100, 1000, 10000, 100000, 1000000, ...): " << std::endl;
        std::cin >> sizeChoice;
        clearConsole();
        return sizeChoice;
    }
    void saveInfo(const std::vector<int> &arr, AlgorithmType algorithm, InputType inputStyle, int inputSize, std::chrono::milliseconds totalDuration)
    {
        fm.saveFile(arr, algorithm, inputStyle, inputSize);
        fm.saveTime(algorithm, inputStyle, inputSize, totalDuration);
    }
};

#endif
