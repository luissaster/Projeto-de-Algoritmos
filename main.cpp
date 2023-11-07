#include <iostream>
#include <string>
#include <chrono>
#include "interface.hpp"
#include "fileManager.hpp"
#include "algorithms.hpp"

// Run all combinations, this function is just to make my life easier.
// Quick Sort (First) parou de rodar no crescente e decrescente de 100000
// Quick Sort (Average) rodou em todos os casos sem problemas
// Quick Sort (Median of Three) parou de rodar no crescente de 100000
// Quick Sort (Random) rodou em todos os casos sem problemas
void runAllCombinations()
{
    FileManager fileManager;
    Interface userInterface;

    AlgorithmType algorithms[] = {Quick_Sort_First, Quick_Sort_Average, Quick_Sort_Median, Quick_Sort_Random};
    InputType inputTypes[] = {Random, Crescente, Decrescente};
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

int main(void)
{
    Interface userInterface;
    FileManager fileManager;
    Algorithms algorithm;
    AlgorithmType algorithmChoice;
    InputType inputChoice;
    std::string fileAddress;
    std::vector<int> arr;
    int inputSize, aux;

    do
    {
        userInterface.showTitle();
        algorithmChoice = userInterface.chooseAlgorithm();

        if (algorithmChoice == 0) // End application
        {
            return 0;
        }
        else if (algorithmChoice > 0 && algorithmChoice <= includedAlgorithms.size())
        {
            inputChoice = userInterface.chooseInputStyle(algorithmChoice);
            inputSize = userInterface.chooseInputSize(algorithmChoice, inputChoice);
            fileAddress = fileManager.generateFile(algorithmChoice, inputChoice, inputSize);
            arr = fileManager.loadFile(fileAddress);
            userInterface.runAlgorithm(arr, algorithmChoice, inputChoice, inputSize);
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
