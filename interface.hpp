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
        std::cout << "+-------------------------------------------+\n"
                  << "|                ALGORITHMS                 |\n"
                  << "+-------------------------------------------+\n";
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
        case Merge_Sort:
            timeStart = std::chrono::high_resolution_clock::now();
            algorithms.mergeSort(arr, 0, arr.size() - 1);
            break;
        case Quick_Sort_First:
            timeStart = std::chrono::high_resolution_clock::now();
            algorithms.quickSort(arr, 0, arr.size() - 1, PivotType::First);
            break;
        case Quick_Sort_Average:
            timeStart = std::chrono::high_resolution_clock::now();
            algorithms.quickSort(arr, 0, arr.size() - 1, PivotType::Average);
            break;
        case Quick_Sort_Median:
            timeStart = std::chrono::high_resolution_clock::now();
            algorithms.quickSort(arr, 0, arr.size() - 1, PivotType::MedianOfThree);
            break;
        case Quick_Sort_Random:
            timeStart = std::chrono::high_resolution_clock::now();
            algorithms.quickSort(arr, 0, arr.size() - 1, PivotType::RandomPivot);
            break;
        case Heap_Sort:
            std::cout << "Heap antes da ordenacao." << std::endl;
            for (int num : arr)
            {
                std::cout << num << " ";
            }

            timeStart = std::chrono::high_resolution_clock::now();
            algorithms.heapSort(arr);

            std::cout << std::endl
                      << "Heap depois da ordenacao." << std::endl;
            for (int num : arr)
            {
                std::cout << num << " ";
            }
            std::cout << std::endl;
            break;
        default:
            std::cout << "Invalid option." << std::endl;
            return;
        }

        timeEnd = std::chrono::high_resolution_clock::now();
        totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);
        saveInfo(arr, algorithm, inputStyle, inputSize, totalDuration);
        pauseConsole();
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
                  << "+----------Comparison Algorithms---------+" << std::endl
                  << "|1 - Insertion sort                      |" << std::endl
                  << "|2 - Bubble sort                         |" << std::endl
                  << "|3 - Selection sort                      |" << std::endl
                  << "|4 - Shell sort                          |" << std::endl
                  << "+----------------------------------------+" << std::endl
                  << std::endl
                  << "+-----Divide and Conquer Algorithms------+" << std::endl
                  << "|5 - Merge sort                          |" << std::endl
                  << "|6 - Quick sort(First element as pivot)  |" << std::endl
                  << "|7 - Quick sort(Average element as pivot)|" << std::endl
                  << "|8 - Quick sort(Median of three as pivot)|" << std::endl
                  << "|9 - Quick sort(Random element as pivot) |" << std::endl
                  << "|10 - Heap sort(min heap)                |" << std::endl
                  << "+----------------------------------------+" << std::endl
                  << std::endl
                  << "+-------Extras(Heap Sort related)--------+" << std::endl
                  << "|11 - Heap minimum (returns heap's root) |" << std::endl
                  << "|12 - Heap extract min (removes root)    |" << std::endl
                  << "|13 - Heap increase key                  |" << std::endl
                  << "|14 - Heap insert                        |" << std::endl
                  << "+----------------------------------------+" << std::endl
                  << std::endl
                  << "+----------------Options-----------------+" << std::endl
                  << "|99 - Run all combinations               |" << std::endl
                  << "|0 - Quit                                |" << std::endl
                  << "+----------------------------------------+" << std::endl
                  << std::endl
                  << "Choose an option -> ";
        std::cin >> algorithmChoice;
        clearConsole();
        return (AlgorithmType)algorithmChoice;
    }

    InputType chooseInputStyle(AlgorithmType algorithmChoice)
    {
        int inputChoice;
        std::cout << "+---------------------------------------------+\n"
                  << "|                 INPUT STYLE                 |\n"
                  << "+---------------------------------------------+\n"
                  << "Selected algorithm: " << includedAlgorithms[algorithmChoice] << "." << std::endl
                  << std::endl;
        std::cout << "+-----------------Input styles----------------+" << std::endl
                  << "|1 - Random                                   |" << std::endl
                  << "|2 - Ascending                                |" << std::endl
                  << "|3 - Descending                               |" << std::endl
                  << "+---------------------------------------------+" << std::endl
                  << std::endl
                  << "Choose an option -> ";
        std::cin >> inputChoice;
        clearConsole();
        return (InputType)inputChoice;
    }

    int chooseInputSize(AlgorithmType algorithmChoice, InputType inputStyle)
    {
        int sizeChoice;
        std::cout << "+---------------------------------------------+\n"
                  << "|                  INPUT SIZE                 |\n"
                  << "+---------------------------------------------+\n"
                  << "Selected algorithm: " << includedAlgorithms[algorithmChoice] << "." << std::endl
                  << "Selected input style: " << includedInputStyles[inputStyle] << "." << std::endl
                  << std::endl;
        std::cout << "Specify the input size -> ";
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
