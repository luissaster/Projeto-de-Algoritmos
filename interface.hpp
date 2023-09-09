#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <chrono>
#include "fileManager.hpp"
#include "algorithms.hpp"

class Interface
{
public:
    Interface();
    ~Interface();
    void showTitle();
    void runAlgorithm(std::vector<int> &arr, int algorithm, int inputStyle, int inputSize);
    int chooseAlgorithm();
    int chooseInputStyle();
    int chooseInputSize();

private:
};

Interface::Interface() {}
Interface::~Interface() {}

void Interface::showTitle()
{
    system("cls");
    std::cout << "|-------------------------------------------|" << std::endl
              << "|                ALGORITMOS                 |" << std::endl
              << "|-------------------------------------------|" << std::endl;
}
void Interface::runAlgorithm(std::vector<int> &arr, int algorithm, int inputStyle, int inputSize)
{
    auto timeStart = std::chrono::high_resolution_clock::now();
    auto timeEnd = std::chrono::high_resolution_clock::now();
    auto totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);
    Algorithms algorithms;
    FileManager fm;
    switch (algorithm)
    {
    case 1: // insertion sort
        timeStart = std::chrono::high_resolution_clock::now();
        algorithms.insertionSort(arr);
        timeEnd = std::chrono::high_resolution_clock::now();
        totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart);
        fm.saveFile(arr, algorithm, inputStyle, inputSize);
        fm.saveTime(algorithm, inputStyle, inputSize, totalDuration);
        break;
    case 2:
        break;

    default:
        std::cout << "Opcao invalida." << std::endl;
        break;
    }
}
int Interface::chooseAlgorithm()
{
    int algorithmChoice;
    std::cout << std::endl
              << "Escolha o algoritmo:" << std::endl
              << "1 - Insertion sort" << std::endl
              << "0 - Encerrar" << std::endl;
    std::cin >> algorithmChoice;
    system("cls");
    return algorithmChoice;
}
int Interface::chooseInputStyle()
{
    int inputChoice;
    std::cout
        << "Escolha o tipo de entrada:" << std::endl
        << "1 - Aleatoria" << std::endl
        << "2 - Crescente" << std::endl
        << "3 - Decrescente" << std::endl;
    std::cin >> inputChoice;
    system("cls");
    return inputChoice;
}
int Interface::chooseInputSize()
{
    int sizeChoice;
    std::cout << "Especifique o tamanho da entrada (10, 100, 1000, 10000, 100000, 1000000, ...):" << std::endl;
    std::cin >> sizeChoice;
    system("cls");
    return sizeChoice;
}

#endif