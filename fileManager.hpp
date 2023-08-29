#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<int> loadInputFile(int option)
{
    std::ifstream inputFile;
    std::string fileName;

    switch (option)
    {
    case 1:
        fileName = "entrada/10.txt";
        break;
    case 2:
        fileName = "entrada/100.txt";
        break;
    case 3:
        fileName = "entrada/1000.txt";
        break;
    case 4:
        fileName = "entrada/10000.txt";
        break;
    case 5:
        fileName = "entrada/100000.txt";
        break;
    case 6:
        fileName = "entrada/1000000.txt";
        break;
    default:
        std::cout << "Erro: valor invalido para carregar arquivo." << std::endl;
        break;
    }

    inputFile.open(fileName);
    if (!inputFile.is_open())
    {
        std::cout << "Erro ao carregar o arquivo." << std::endl;
        std::vector<int> vazio = {};
        return vazio;
    }

    int vectorSize, num;
    std::vector<int> loadedVector;
    inputFile >> vectorSize;
    for (int i = 0; i < vectorSize; i++)
    {
        inputFile >> num;
        loadedVector.push_back(num);
    }
    inputFile.close();
    return loadedVector;
}

int saveToFile(std::vector<int> &arr, std::string outputName)
{
    std::ofstream outputFile(outputName);
    if (!outputFile.is_open())
    {
        std::cout << "Erro ao abrir o arquivo " << outputName << "." << std::endl;
        return 1;
    }

    for (int num : arr)
    {
        outputFile << num << std::endl;
    }

    outputFile.close();
    std::cout << "Arquivo " << outputName << " salvo com sucesso." << std::endl;
    return 0;
}

#endif