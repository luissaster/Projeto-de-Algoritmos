//
// Projeto desenvolvido durante a disciplina SIN213 - PROJETO DE ALGORITMOS
// na Universidade Federal de Viçosa - Campus Rio Paranaíba
// por Luís Fernando Almeida - luis.almeida1@ufv.br
// https://github.com/luissaster/projeto-de-algoritmos
//

#include <iostream>
#include <string>
#include <chrono>
#include "interface.hpp"
#include "fileManager.hpp"
#include "algorithms.hpp"

FileManager fileManager;
Interface userInterface;
Algorithms algorithm;
AlgorithmType algorithmChoice;
InputType inputChoice;
std::vector<int> testArr = {7, 8, 12, 2, 1, 5, 10, 3, 6, 4};

// QUICK SORT
// Quick Sort (First) parou de rodar no crescente e decrescente de 100000
// Rodou no Code::Blocks, aumentando o tamanho da pilha
// settings > compiler > linker settings > other linker options >  -Wl,--stack=268435456
// Quick Sort (Average), (Median of Three), (Random) rodaram em todos os casos sem problemas
//

// Run all combinations, this function is just to make my life easier.
void runAllCombinations()
{
    AlgorithmType algorithms[] = {Heap_Sort};
    InputType inputTypes[] = {Crescente, Decrescente, Random};
    int inputSizes[] = {10, 100, 1000, 10000, 100000, 1000000};

    for (AlgorithmType algorithm : algorithms)
    {
        for (InputType inputType : inputTypes)
        {
            for (int inputSize : inputSizes)
            {
                std::string inputFile = fileManager.generateFile(algorithm, inputType, inputSize);
                std::vector<int> input = fileManager.loadFile(inputFile);
                userInterface.runAlgorithm(input, algorithm, inputType, inputSize);
            }
        }
    }
}

void printVector(std::vector<int> &arr)
{
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
int main(void)
{
    std::string fileAddress;
    std::vector<int> arr;
    int inputSize, aux, heapMin;

    do
    {
        userInterface.showTitle();
        algorithmChoice = userInterface.chooseAlgorithm();

        if (algorithmChoice == 0) // End application
        {
            return 0;
        }
        else if (algorithmChoice > 0 && algorithmChoice < includedAlgorithms.size())
        {
            inputChoice = userInterface.chooseInputStyle(algorithmChoice);
            inputSize = userInterface.chooseInputSize(algorithmChoice, inputChoice);
            fileAddress = fileManager.generateFile(algorithmChoice, inputChoice, inputSize);
            arr = fileManager.loadFile(fileAddress);
            userInterface.runAlgorithm(arr, algorithmChoice, inputChoice, inputSize);
        }
        else if (algorithmChoice > 10 && algorithmChoice < 15)
        { // Heap Sort extras
            switch (algorithmChoice)
            {
            case 11: // Heap minimum
                std::cout << "+-------------------------------+" << std::endl
                          << "|     Heap antes da ordenacao   |" << std::endl
                          << "+-------------------------------+" << std::endl;
                printVector(testArr);
                algorithm.buildMinHeap(testArr);
                heapMin = algorithm.heapMinimum(testArr);
                std::cout << "+-------------------------------+" << std::endl
                          << "|     Heap depois da ordenacao  |" << std::endl
                          << "+-------------------------------+" << std::endl;
                printVector(testArr);
                std::cout << "+-------------------------------+" << std::endl
                          << "|         Elemento minimo       |" << std::endl
                          << "+-------------------------------+" << std::endl
                          << heapMin << std::endl;
                userInterface.pauseConsole();
                break;
            case 12: // Heap extract min
                std::cout << "+-------------------------------+" << std::endl
                          << "|     Heap antes da ordenacao   |" << std::endl
                          << "+-------------------------------+" << std::endl;
                printVector(testArr);
                algorithm.buildMinHeap(testArr);
                heapMin = algorithm.heapExtractMin(testArr);
                std::cout << "+-------------------------------+" << std::endl
                          << "|     Heap depois da ordenacao  |" << std::endl
                          << "+-------------------------------+" << std::endl;
                printVector(testArr);
                std::cout << "+-------------------------------+" << std::endl
                          << "|         Elemento minimo       |" << std::endl
                          << "+-------------------------------+" << std::endl
                          << heapMin << std::endl;
                userInterface.pauseConsole();
                break;
            case 13: // Heap increase key
                std::cout << "+-------------------------------+" << std::endl
                          << "|     Heap antes da ordenacao   |" << std::endl
                          << "+-------------------------------+" << std::endl;
                printVector(testArr);
                algorithm.buildMinHeap(testArr);
                algorithm.heapIncreaseKey(testArr, 2, 8);
                std::cout << "+-------------------------------+" << std::endl
                          << "|     Heap depois da ordenacao  |" << std::endl
                          << "+-------------------------------+" << std::endl;
                printVector(testArr);
                userInterface.pauseConsole();
                break;
            case 14: // Heap insert
                std::cout << "+-------------------------------+" << std::endl
                          << "|     Heap antes da ordenacao   |" << std::endl
                          << "+-------------------------------+" << std::endl;
                printVector(testArr);
                algorithm.buildMinHeap(testArr);
                algorithm.heapInsert(testArr, 10);
                std::cout << "+-------------------------------+" << std::endl
                          << "|     Heap depois da ordenacao  |" << std::endl
                          << "+-------------------------------+" << std::endl;
                printVector(testArr);
                userInterface.pauseConsole();
                break;
            }
        }
        else if (algorithmChoice == 99)
        {
            std::cout << "Running all combinations... Are you sure? 1 - Yes, 0 - No" << std::endl;
            std::cin >> aux;
            if (aux == 1)
            {
                runAllCombinations();
            }
            else
            {
                std::cout << "Exiting..." << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid choice." << std::endl;
        }
    } while (algorithmChoice != 0);

    return 0;
}
