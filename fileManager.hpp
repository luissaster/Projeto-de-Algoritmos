#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <fstream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <algorithm>

class FileManager
{
public:
    FileManager();
    ~FileManager();

    std::string generateFile(int algorithm, int inputStyle, int inputSize);
    std::vector<int> loadFile(const std::string &fileName);
    void saveFile(const std::vector<int> &arr, int algorithm, int inputStyle, int inputSize);
    void saveTime(int algorithm, int inputStyle, int inputSize, std::chrono::milliseconds time);

private:
    std::string generateFileName(int algorithm, int inputStyle, int inputSize);
    std::string generateOutputFileName(int algorithm, int inputStyle, int inputSize);
    std::string generateTimeFileName(int algorithm, int inputStyle, int inputSize);
};

FileManager::FileManager() {}
FileManager::~FileManager() {}

std::string FileManager::generateFile(int algorithm, int inputStyle, int inputSize)
{
    std::vector<int> arr;
    std::string fileName = generateFileName(algorithm, inputStyle, inputSize);
    std::ofstream file(fileName);
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> range(-1000000, 1000000);

    if (!file.is_open())
    {
        std::cout << "Error opening the file -> " << fileName << "." << std::endl;
        return "";
    }

    file << inputSize << std::endl;

    switch (inputStyle)
    {
    case 1: // Aleatorio
        for (int i = 0; i < inputSize; i++)
        {
            arr.push_back(range(generator));
        }
        break;
    case 2: // Crescente
        for (int i = 0; i < inputSize; i++)
        {
            arr.push_back(range(generator));
        }
        std::sort(arr.begin(), arr.end());
        break;
    case 3: // Decrescente
        for (int i = 0; i < inputSize; i++)
        {
            arr.push_back(range(generator));
        }
        std::sort(arr.begin(), arr.end(), std::greater<int>());
        break;
    }

    for (int num : arr)
    {
        file << num << std::endl;
    }
    file.close();
    return fileName;
}
std::vector<int> FileManager::loadFile(const std::string &fileName)
{
    std::ifstream file(fileName);
    std::vector<int> arr;
    int size, num;

    if (!file.is_open())
    {
        std::cout << "Error opening the file -> " << fileName << "." << std::endl;
        return arr;
    }

    file >> size;

    for (int i = 0; i < size; i++)
    {
        file >> num;
        arr.push_back(num);
    }

    file.close();
    return arr;
}
void FileManager::saveFile(const std::vector<int> &arr, int algorithm, int inputStyle, int inputSize)
{
    std::string fileName = generateOutputFileName(algorithm, inputStyle, inputSize);
    std::ofstream file(fileName);

    if (!file.is_open())
    {
        std::cout << "Error opening the file for writing." << std::endl;
        return;
    }

    file << inputSize << std::endl;

    for (int num : arr)
    {
        file << num << std::endl;
    }

    file.close();
    std::cout << "File saved successfully -> " << fileName << std::endl;
}
void FileManager::saveTime(int algorithm, int inputStyle, int inputSize, std::chrono::milliseconds time)
{
    std::string fileName = generateTimeFileName(algorithm, inputStyle, inputSize);
    std::ofstream file(fileName);

    if (!file.is_open())
    {
        std::cout << "Error opening the file -> " << fileName << std::endl;
        return;
    }

    file << "Algorithm: ";
    switch (algorithm)
    {
    case 1:
        file << "insertion-sort";
        break;
    case 2:
        break;
    }
    file << std::endl;

    file << "Input: ";
    switch (inputStyle)
    {
    case 1:
        file << inputSize << " random element(s)";
        break;
    case 2:
        file << inputSize << " random element(s) in ascending order";
        break;
    case 3:
        file << inputSize << " random element(s) in descending order";
        break;
    }
    file << std::endl;

    file << "Time spent: " << time.count() << " milliseconds." << std::endl;

    file.close();
    std::cout << "Time saved to -> " << fileName << std::endl;
}
std::string FileManager::generateFileName(int algorithm, int inputStyle, int inputSize)
{
    std::string typeName;
    switch (algorithm)
    {
    case 1: // insertion sort
        switch (inputStyle)
        {
        case 1:
            typeName = "Insertion Sort/Arquivos de Entrada/Random/EntradaRandom" + std::to_string(inputSize) + ".txt";
            break;
        case 2:
            typeName = "Insertion Sort/Arquivos de Entrada/Crescente/EntradaCrescente" + std::to_string(inputSize) + ".txt";
            break;
        case 3:
            typeName = "Insertion Sort/Arquivos de Entrada/Decrescente/EntradeDecrescente" + std::to_string(inputSize) + ".txt";
            break;
        default:
            std::cout << "Invalid input type." << std::endl;
            return "";
        }
        break;
    case 2:
        break;
    default:
        break;
    }
    return typeName;
}
std::string FileManager::generateOutputFileName(int algorithm, int inputStyle, int inputSize)
{
    std::string typeName;
    switch (algorithm)
    {
    case 1: // insertion sort
        switch (inputStyle)
        {
        case 1:
            typeName = "Insertion Sort/Arquivos de Saida/Random/SaidaRandom" + std::to_string(inputSize) + ".txt";
            break;
        case 2:
            typeName = "Insertion Sort/Arquivos de Saida/Crescente/SaidaCrescente" + std::to_string(inputSize) + ".txt";
            break;
        case 3:
            typeName = "Insertion Sort/Arquivos de Saida/Decrescente/SaidaDecrescente" + std::to_string(inputSize) + ".txt";
            break;
        default:
            std::cout << "Invalid input type." << std::endl;
            return "";
        }
        break;
    case 2:
        break;
    default:
        break;
    }
    return typeName;
}
std::string FileManager::generateTimeFileName(int algorithm, int inputStyle, int inputSize)
{
    std::string typeName;
    switch (algorithm)
    {
    case 1: // insertion sort
        switch (inputStyle)
        {
        case 1:
            typeName = "Insertion Sort/Arquivos de Tempo/Random/TempoRandom" + std::to_string(inputSize) + ".txt";
            break;
        case 2:
            typeName = "Insertion Sort/Arquivos de Tempo/Crescente/TempoCrescente" + std::to_string(inputSize) + ".txt";
            break;
        case 3:
            typeName = "Insertion Sort/Arquivos de Tempo/Decrescente/TempoDecrescente" + std::to_string(inputSize) + ".txt";
            break;
        default:
            std::cout << "Invalid input type." << std::endl;
            return "";
        }
        break;
    case 2:
        break;
    default:
        break;
    }
    return typeName;
}
#endif